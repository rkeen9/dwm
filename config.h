/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 15;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=16" }; 
static const char dmenufont[]       = "Source Code Pro:size=16";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_gray5[]       = "#282828";
static const char col_gray6[]       = "#616673";
static const char col_cyan[]        = "#005577";
static const char col_aqua[]        = "#427b58";
static const char col_blue[]        = "#458588";
static const char col_purple[]      = "#EE82EE";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#9e170e";
static const char col_yellow[]      = "#ffff00";
static const char col_pink[]        = "#934b52";
static const char col_white[]       = "#ffffff";
static const char col_green[]       = "#77a347";
static const char col_border[]      = "#cc241d";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
    /*               text       bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_black },
	[SchemeSel]  = { col_gray4, col_pink,  col_border },
	[SchemeRed]  = { col_red,   col_gray1, col_black },
	[SchemeGreen]= { col_green, col_gray1, col_black }, 
    [SchemeBlue] = { col_blue,  col_gray1, col_black }, 
};

static const unsigned int alphas[][3]      = {
	/*                fg      bg    border     */
	[SchemeNorm]  = { OPAQUE, 0xD0, OPAQUE },
	[SchemeSel]   = { OPAQUE, 0xD0, OPAQUE },
    [SchemeRed]   = { OPAQUE, 0xD0, OPAQUE },
    [SchemeGreen] = { OPAQUE, 0xD0, OPAQUE },
    [SchemeBlue]  = { OPAQUE, 0xD0, OPAQUE },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered     isfloating   monitor */
//	{ "Gimp",     NULL,       NULL,       0,            0,             1,           -1 },
	{ "Spotify",  NULL,       NULL,       1 << 8,       0,             0,           -1 },


};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      gaps },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster }, 
	{ "|||",      col },
    { "[G]=",     tile },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *browsercmd[] = { "brave", NULL};
static const char *spotifycmd[] = {"spotify", NULL};
static const char *volumeup[]  = { "/home/robert/scripts/volume_up.sh", NULL };
static const char *volumedown[]  = { "/home/robert/scripts/volume_down.sh", NULL };
static const char *screenshot[] = { "flameshot", "gui", "-p", "/home/robert/images/screenshots", NULL };
static const char *bluetooth[] = { "blueman-applet", "&", "blueman-manager", NULL };
static const char *brightnessup[] = { "sudo", "/home/robert/scripts/brightness_up.sh", NULL };
static const char *brightnessdown[] = { "sudo", "/home/robert/scripts/brightness_down.sh", NULL };
static const char *bluetoothmenu[] = { "st", "-e", "bluetoothctl", NULL };
static const char *updatekeyboard[] = { "setxkbmap", "-option", "caps:swapescape", NULL };
static const char *shutdown[] = { "sudo", "shutdown", "-P", "now", NULL };
static const char *mount[] = { "sudo", "mount", "/dev/sdc1", "/media/usb", NULL};
static const char *umount[] = { "sudo", "umount", "/media/usb", NULL};
static const char *files[] = { "thunar", NULL };
static const char *audio[] = { "/home/robert/scripts/audio.sh", NULL };
static const char *reboot[] = { "sudo", "reboot", NULL };
static const char *anki[] = { "anki", NULL };
static const char *ranger[] = { "st", "-e", "ranger", NULL };
static const char *zoomConference[] = { "zoom", NULL };
static const char *weather[] = { "st", "-e", "/home/robert/scripts/weather.sh", NULL };
static const char *python[] = { "st", "-e", "python", NULL };
static const char *newsboat[] = { "st", "-e", "newsboat", NULL };
static const char *kanji[] = { "/home/robert/scripts/rtk_keyboard.sh", NULL };
static const char *recordDesktop[] = { "st", "-e", "/home/robert/scripts/record_desktop.sh", NULL };

static Key keys[] = {
	/* modifier                     key                      function        argument */
	{ MODKEY,                       XK_p,                    spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		        XK_b,                    spawn,          {.v = browsercmd } },
    { MODKEY,                       XK_s,                    spawn,          {.v = spotifycmd} },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = volumeup } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = volumedown } },
    { 0,                            XK_Print,                spawn,          {.v = screenshot } },
    { 0,                            XF86XK_MonBrightnessUp,  spawn,          {.v = brightnessup} },
    { 0,                            XF86XK_MonBrightnessDown,spawn,          {.v = brightnessdown} },
    { MODKEY|ControlMask|ShiftMask, XK_q,                    quit,           {1} }, 
	{ ControlMask|ShiftMask,        XK_H,                    setcfact,       {.f = +0.25} },
	{ ControlMask|ShiftMask,        XK_L,                    setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,                    setcfact,       {.f =  0.00} }, 
	{ MODKEY,                       XK_u,                    setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,                    setlayout,      {.v = &layouts[4]} }, 
	{ MODKEY|ShiftMask,             XK_v,                    setlayout,      {.v = &layouts[5]} },
    { MODKEY|ControlMask,           XK_k,                    spawn,          {.v = updatekeyboard } }, 
    { MODKEY|ControlMask,           XK_b,                    spawn,          {.v = bluetoothmenu } },
    { MODKEY|ControlMask|ShiftMask, XK_p,                    spawn,          {.v = shutdown } },
    { MODKEY|ControlMask,           XK_m,                    spawn,          {.v = mount } },
    { MODKEY|ControlMask|ShiftMask, XK_m,                    spawn,          {.v = umount} },
    { MODKEY,                       XK_e,                    spawn,          {.v = files} },
    { MODKEY,                       XK_r,                    spawn,          {.v = ranger} },
    { MODKEY,                       XK_a,                    spawn,          {.v = audio} },
    { MODKEY|ControlMask|ShiftMask, XK_r,                    spawn,          {.v = reboot} },
    { MODKEY|ShiftMask,             XK_a,                    spawn,          {.v = anki} },
    { MODKEY,                       XK_w,                    spawn,          {.v = weather} },
    { MODKEY,                       XK_z,                    spawn,          {.v = zoomConference} },
    { MODKEY|ShiftMask,             XK_p,                    spawn,          {.v = python} },
//  { MODKEY,                       XK_n,                    spawn,          {.v = newsboat} },
    { MODKEY|ShiftMask,             XK_n,                    spawn,          {.v = kanji} },
    { MODKEY|ShiftMask,             XK_r,                    spawn,          {.v = recordDesktop} },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,               zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                    killclient,     {0} },
	{ MODKEY,                       XK_t,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                    setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_g,                    setlayout,      {.v = &layouts[6]} },
//	{ MODKEY,                       XK_space,                setlayout,      {0} },
	{ MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_h,                    focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,                    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                focusmontagmon, {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               focusmontagmon, {.i = +1 } },
	{ MODKEY,                       XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,               tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                    0)
	TAGKEYS(                        XK_2,                                    1)
	TAGKEYS(                        XK_3,                                    2)
	TAGKEYS(                        XK_4,                                    3)
	TAGKEYS(                        XK_5,                                    4)
	TAGKEYS(                        XK_6,                                    5)
	TAGKEYS(                        XK_7,                                    6)
	TAGKEYS(                        XK_8,                                    7)
	TAGKEYS(                        XK_9,                                    8)
	{ MODKEY|ShiftMask,             XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

