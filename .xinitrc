#!/bin/bash

export BAT_WARNING_SENT=false

script_name=${BASH_SOURCE[0]}
for pid in $(pidof -x $script_name); do
    if [ $pid != $$ ]; then
        kill -9 $pid
    fi
done

#hsetroot -solid "#020E13" &
feh --bg-fill ~/Pictures/bg &

dwmblocks &
picom -b &
dunst &

#setup xob
mkfifo /tmp/xobpipe
chown aydin /tmp/xobpipe
tail -f /tmp/xobpipe | xob &

exec dwm
