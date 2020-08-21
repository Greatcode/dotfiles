#!/bin/bash

# You can call this script like this:
# $./backlight.sh up
# $./backlight.sh down

ID=9001

function send {
	BLIGHT=$(sudo light | cut -d. -f 1)	
	#dunstify "Backlight" "$BLIGHT%" -u LOW --replace $ID
	echo "$BLIGHT" > /tmp/xobpipe
}

case $1 in
    up)
	sudo light -A 10
	send
	;;
    down)
	sudo light -U 10
	send
	;;
esac
