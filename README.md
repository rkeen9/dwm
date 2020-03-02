# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
In order to build dwm you need the Xlib header files.


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
<pre>
    make clean install
</pre>

## Running dwm
Add the following line to your .xinitrc to start dwm using startx:
<pre>
    exec dwm
</pre>
In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:
<pre>
    DISPLAY=foo.bar:1 exec dwm
</pre>
(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:
<pre>
    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
    	sleep 1
    done &
    exec dwm
</pre>

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Installed Patches
- [colored status text](https://dwm.suckless.org/patches/statuscolors/)
- [tilegap](https://dwm.suckless.org/patches/tilegap/)
- [fake fullscreen](https://dwm.suckless.org/patches/fakefullscreen/)
- [nomonocleborders](https://gist.github.com/SebastianJarsve/497b2014774c849df0132d7118cbab65)
- [noborder](https://dwm.suckless.org/patches/noborder/)
- [columns](https://dwm.suckless.org/patches/columns/)
- [alpha](https://dwm.suckless.org/patches/alpha/)
- [restartsig](https://dwm.suckless.org/patches/restartsig/)
- [centered master](https://dwm.suckless.org/patches/centeredmaster/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [cfacts](https://dwm.suckless.org/patches/cfacts/)
