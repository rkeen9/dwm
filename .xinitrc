#!/bin/sh
xrandr --newmode "1920x1080"  173.00  1920 2048 2248 2576  1080 1083 1088 1120 -hsync +vsync
xrandr --addmode Virtual1 "1920x1080"
xrandr --output Virtual1 --mode 1920x1080
feh --bg-scale ~/Desktop/wallpaper.jpg 
xcompmgr &
while true ; do
    xsetroot -name "$(date +%c)"
    sleep 1s
done &
exec dwm
