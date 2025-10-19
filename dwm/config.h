/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx 	= 2; 		/* border pixel of windows */
static const unsigned int gappx 	= 15; 		/* gaps between windows */
static const unsigned int snap 		= 32; 		/* snap pixel */
static const int swallowfloating 	= 0; 		/* 1 means swallow floating windows by default */
static const int swterminheritfs 	= 0; 		/* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static const int showbar 		= 1; 		/* 0 means no bar */
static const int topbar 		= 1; 		/* 0 means bottom bar */
static const int user_bh 		= 22; 		/* 2 is the default spacing around the bar's font */
static const char col_black[] 		= "#000000";
static const char col_dgray[] 		= "#868686";
static const char col_white[] 		= "#c3c3c3";
static const unsigned int baralpha 	= 0xcc;
static const unsigned int borderalpha 	= 0xcc;
static const char *fonts[] 		= {
	"monospace:style=Bold:size=9",
	"RobotoMono Nerd Font Propo:style=Bold:size=9",
	"Font Awesome 6 Free:style=Solid:size=9",
	"Noto Color Emoji:size=9",
	};

static const char *colors[][3] 		= {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_dgray, col_black, col_black },
	[SchemeSel]  = { col_white, col_black, col_white },
};
static const unsigned int alphas[][3] 	= {
	/*               fg      bg        border*/
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] 	= {
	"/home/tch/.local/scripts/dwm-randombg", NULL,
	"/home/tch/.local/scripts/dwm-micmust", NULL,
	"dwmblocks", NULL,
	"ibus-daemon", "-dRx", NULL,
	"unclutter", NULL,
	"picom", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "a", "ă", "â", "b", "c", "d", "đ", "e", "ê" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class 		instance 	title 		tags mask 	isfloating 	isterminal 	noswallow 	monitor */
	{ "Firefox", 		NULL, 		NULL, 		1 << 8, 	0, 		0, 		-1, 		-1 },
	{ "firefox-esr",	NULL, 		NULL, 		1 << 8, 	0, 		0, 		-1, 		-1 },
	{ "librewolf", 		NULL, 		NULL, 		1 << 8, 	0, 		0, 		-1, 		-1 },
	{ "Alacritty", 		NULL, 		NULL, 		0, 		0, 		1, 		0, 		-1 },
	{ "St", 		NULL, 		NULL, 		0, 		0, 		1, 		0, 		-1 },
	{ "Nestopia", 		NULL, 		NULL, 		0, 		1, 		0, 		0, 		-1 },
	{ NULL, 		NULL, 		"Event Tester", 0, 		0, 		0, 		1, 		-1 }, /* xev */
};

/* layout(s) */
static const float mfact 	= 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster 	= 1; 	/* number of clients in master area */
static const int resizehints 	= 1; 	/* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */
static const int attachbelow 	= 1; 	/* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

static const Env envs[] = {
	/* variable 			value */
	{ "GTK_IM_MODULE",		"ibus" },
	{ "QT_IM_MODULE",		"ibus" },
	{ "XMODIFIERS",			"@im=ibus" },
	{ "QT_QPA_PLATFORMTHEME", 	"qt6ct" },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY, 			KEY, 		view, 		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask, 		KEY, 		toggleview, 	{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask, 		KEY, 		tag, 		{.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, 		toggletag, 	{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMCMD(cmd) { .v = (const char*[]){ "alacritty", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", "Open: ", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const Key keys[] = {
	/* modifier 		key 		function 	argument */
	{ MODKEY|ShiftMask, 	XK_Return, 	spawn, 		{.v = dmenucmd } },
	{ MODKEY, 		XK_Return, 	spawn, 		{.v = termcmd } },
	{ 0, XF86XK_AudioMute, 			spawn, 		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle") },
	{ 0, XF86XK_AudioLowerVolume, 		spawn, 		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 1%-") },
	{ 0, XF86XK_AudioRaiseVolume, 		spawn, 		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 1%+ -l 1") },
	{ 0, XF86XK_AudioMicMute, 		spawn, 		SHCMD("~/.local/scripts/dwm-micmust 1") },
	{ 0, XF86XK_MonBrightnessDown, 		spawn, 		SHCMD("light -U 0.5") },
	{ 0, XF86XK_MonBrightnessUp, 		spawn, 		SHCMD("light -A 0.5") },
	{ MODKEY|ShiftMask, 	XK_l, 		spawn, 		SHCMD("~/.local/scripts/dwm-scrlocker") },
	{ MODKEY, 		XK_Print, 	spawn, 		SHCMD("~/.local/scripts/dwm-scrshoter full") },
	{ MODKEY|ShiftMask, 	XK_Print, 	spawn, 		SHCMD("~/.local/scripts/dwm-scrshoter window") },
	{ MODKEY|Mod1Mask, 	XK_Print, 	spawn, 		SHCMD("~/.local/scripts/dwm-scrshoter selected") },
	{ MODKEY|ShiftMask, 	XK_k,	 	spawn, 		SHCMD("~/.local/scripts/screenkey_toggle") },
	{ MODKEY|ShiftMask, 	XK_m,	 	spawn, 		SHCMD("~/.local/scripts/dmanopen") },
	{ MODKEY, 		XK_r, 		spawn, 		SHCMD("~/.local/scripts/dwm-randombg") },
	{ MODKEY|ShiftMask, 	XK_x,	 	spawn, 		SHCMD("xkill") },
	{ ControlMask|Mod1Mask,	XK_Delete, 	spawn, 		TERMCMD("htop") },
	{ MODKEY,	 	XK_e,	 	spawn, 		TERMCMD("yazi") },
	{ MODKEY,	 	XK_n,	 	spawn, 		TERMCMD("nmtui") },
	{ MODKEY,	 	XK_m,	 	spawn, 		TERMCMD("ncmpcpp") },
	{ MODKEY, 		XK_b, 		togglebar, 	{0} },
	{ MODKEY,               XK_Tab, 	focusstack, 	{.i = +1 } },
	{ MODKEY|ShiftMask, 	XK_Tab, 	focusstack, 	{.i = -1 } },
	{ MODKEY|ShiftMask, 	XK_i, 		incnmaster, 	{.i = +1 } },
	{ MODKEY|ShiftMask, 	XK_d, 		incnmaster, 	{.i = -1 } },
	{ MODKEY, 		XK_h, 		setmfact, 	{.f = -0.02} },
	{ MODKEY, 		XK_l, 		setmfact, 	{.f = +0.02} },
	{ MODKEY, 		XK_space, 	zoom, 		{0} },
	{ MODKEY, 		XK_x, 		killclient, 	{0} },
	{ MODKEY|ShiftMask,     XK_t, 		togglefloating, {0} },
	{ MODKEY,               XK_t, 		setlayout, 	{.v = &layouts[0]} },
	{ MODKEY,               XK_0, 		view, 		{0} },
	{ MODKEY|ShiftMask,     XK_0, 		tag, 		{.ui = ~0 } },
	{ MODKEY,               XK_comma, 	focusmon, 	{.i = -1 } },
	{ MODKEY,               XK_period, 	focusmon, 	{.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma, 	tagmon, 	{.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period, 	tagmon, 	{.i = +1 } },
	{ MODKEY,               XK_minus, 	setgaps, 	{.i = -1 } },
	{ MODKEY,               XK_equal, 	setgaps, 	{.i = +1 } },
	{ MODKEY|ShiftMask,     XK_equal, 	setgaps, 	{.i = 0  } },
	TAGKEYS( 		XK_1, 		0)
	TAGKEYS( 		XK_2, 		1)
	TAGKEYS( 		XK_3, 		2)
	TAGKEYS( 		XK_4, 		3)
	TAGKEYS( 		XK_5, 		4)
	TAGKEYS( 		XK_6, 		5)
	TAGKEYS( 		XK_7, 		6)
	TAGKEYS( 		XK_8, 		7)
	TAGKEYS( 		XK_9, 		8)
	{ MODKEY|ShiftMask,     XK_q, 		quit, 		{0} },
	{ MODKEY|ShiftMask,     XK_r, 		quit, 		{1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click 		event mask 	button 		function 	argument */
	{ ClkLtSymbol, 		0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol, 		0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle, 		0,              Button2,        zoom,           {0} },
	{ ClkStatusText, 	0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

