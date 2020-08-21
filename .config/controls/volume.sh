#!/bin/bash

# You can call this script like this:
# $./volume.sh up
# $./volume.sh down
# $./volume.sh mute

ID=9000

function get_volume {
	awk -F"[][]" '/dB/ { print $2 }' <(amixer sget Master)
}

function get_mute {
    pacmd list-sinks | awk '/muted/ { print $2 }'
}

function send {
	VOL=$(awk -F"[][]" '/dB/ { print $2 }' <(amixer sget Master) | tr -d "%")
	#dunstify "Volume" "$VOL%" -u LOW --replace $ID
	echo "$VOL" > /tmp/xobpipe
}

case $1 in
    up)
	pactl set-sink-mute 0 0
	pactl set-sink-volume 0 +5%
	send
	;;
    down)
	pactl set-sink-mute 0 0
	pactl set-sink-volume 0 -5%
	send
	;;
    mute)
	pactl set-sink-mute 0 toggle
	if [[ get_mute == "yes" ]]; then
	    dunstify "Volume muted" --replace $ID
	else
	    send
	fi
	;;
esac
