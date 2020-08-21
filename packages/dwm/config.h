#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 12;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

//////// custom!

static const unsigned int c_tag_margin = 0;
static const unsigned int c_tag_padding = 5;
static const unsigned int c_bar_h_margin = gappx;
static const unsigned int c_bar_v_margin = gappx;
static const unsigned int c_bar_width_add = 10;
static const unsigned int c_tag_underline_width = 3;
static const unsigned int c_bar_border_width = 0;

////////////

//static const char *fonts[]          = { "Neep:size=13", "FontAwesome:size=10" };
static const char *fonts[]          = { "Neep:size=13", "Iosevka Nerd Font" };
static const char dmenufont[]       = "Neep:size=13";

static const char col_dark[]		= "#020E13";
static const char col_pink[]		= "#EF476F";
static const char col_violet[]		= "#806991";
static const char col_cyan[]		= "#118AB2";
static const char col_blue[]		= "#0A546C";
static const char col_yellow[]		= "#FFD166";
static const char col_green[]		= "#06D6A0";
static const char col_white[]		= "#FEFCFB";

static const char *colors[][3]      = {
	/*             					fg         bg         border   */
	[SchemeNorm] 				= { col_white, col_dark, col_blue },
	[SchemeSel]  				= { col_white, col_blue, col_cyan },
	//[SchemeSel]  				= { col_white, col_blue, col_white },
	[SchemeTitle]  				= { col_white, col_dark, col_cyan },
	[SchemeTagUnderlineNorm]  	= { col_dark, col_dark, col_cyan },
	[SchemeTagUnderlineSel]  	= { col_yellow, col_dark, col_dark },
	[SchemeBarBorder]  			= { col_white, col_dark, col_dark },
	[SchemeTagPaddingNorm]		= { col_dark, col_white, col_blue },
	[SchemeTagPaddingSel]		= { col_blue, col_white, col_blue },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/*{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },*/
	{ NULL,		NULL,	NULL,	0,	0,	-1}
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T",      tile },    /* first entry is default */
	{ "F",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-c", "-fn", dmenufont, "-nb", col_dark, "-nf", col_white, "-sb", col_cyan, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", NULL };
/*
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
*/

static const char *upvol[]   = { "/usr/bin/volume", "up",     NULL };
static const char *downvol[] = { "/usr/bin/volume", "down",   NULL };
static const char *mutevol[] = { "/usr/bin/volume", "mute",   NULL };

static const char *uplight[]   = { "/usr/bin/backlight", "up",     NULL };
static const char *downlight[] = { "/usr/bin/backlight", "down",   NULL };

//static const char *cmdtakess[]  = { "/usr/bin/scrot", "~/Pictures/screenshot-%Y-%m-%d-%T.png", NULL };
static const char *browsercmd[] = { "/usr/bin/firefox", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
    { MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
    { MODKEY|ShiftMask,             XK_h,      inplacerotate,  {.i = +2} },
    { MODKEY|ShiftMask,             XK_l,      inplacerotate,  {.i = -2} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,						XK_w,	   spawn,		   {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,			            XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask, 			XK_r,      quit,           {1} }, 
	{ ControlMask|ShiftMask, 		XK_space,  spawn,          SHCMD("keyb_layout") },
	
	//volume control
    { 0,                            XF86XK_AudioLowerVolume,
												spawn,			{.v = downvol } },
    { 0,                            XF86XK_AudioMute,
												spawn,			{.v = mutevol } },
    { 0,                            XF86XK_AudioRaiseVolume,
												spawn,			{.v = upvol   } },

	//backlight control
	{ 0,                            XF86XK_MonBrightnessUp,
												spawn,			{.v = uplight } },
	{ 0,                            XF86XK_MonBrightnessDown,
												spawn,			{.v = downlight   } },

	//screenshot

	{ 0,							XK_Print,	spawn,			SHCMD("/usr/bin/scrot ~/Pictures/Screenshots/screenshot-%Y-%m-%d-%T.png") },
	{ ShiftMask,					XK_Print,	spawn,			SHCMD("/usr/bin/scrot -u ~/Pictures/Screenshots/screenshot-%Y-%m-%d-%T.png") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("keyb_layout") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

