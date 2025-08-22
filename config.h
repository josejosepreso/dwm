#include <X11/XF86keysym.h>

#define TERMINAL "alacritty"

static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:style=Bold:size=9" ,"0xProto Nerd Font Mono:size=12" };
static const char dmenufont[]       = "Iosevka:style=Bold:size=9";

static const char col_gray1[]       = "#000000";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
// static const char col_cyan[]        = "#986c5b";
static const char col_cyan[]        = "#6f493a";
//static const char col_cyan[]        = "#005577";
// static const char col_cyan[]        = "#9e7600";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "󰈙", "", "", "", "", "", "" };

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int gappx = 5;

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
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
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    	/* class     	 instance    title        tags mask   isfloating  isterminal  noswallow  monitor */
	{ "qutebrowser", NULL,       NULL,        1 << 8,     0,          0,	      0,   	 -1 },
	{ "LibreWolf",   NULL,       NULL,        1 << 8,     0,          0,   	      0,     	 -1 },
	{ "mpv",  	 NULL,       NULL,        1 << 7,     0,          0,          0,	 -1 },
	{ "urxvt",  	 NULL,       NULL,        0,	      0,          1,   	      0,	 -1 },
	// { "st",  	 NULL,       NULL,        0,	      0,          1,   	      0,	 -1 },
	{ "URxvt",  	 NULL,       NULL,        0,	      0,          1,   	      0,	 -1 },
	{ "Alacritty",   NULL,       NULL,        0,	      0,          1,   	      0,	 -1 },
	{ "floating",    NULL,       NULL,        0,	      1,          0,   	      1,	 -1 },
};

static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL , NULL };

static const char *ncmpcpp[] = { TERMINAL, "-e", "tmux", "a", "-t", "ncmpcpp", NULL };

static const Key keys[] = {
	/* modifier                     key        			function        argument */
	{ MODKEY,                       XK_n,    			spawn,		SHCMD("st -c \"floating\" -g=\"120x30+500+500\" -e mplay") },
	// { MODKEY,                       XK_n,    			spawn,		SHCMD("mplay") },
	// { MODKEY,                       XK_n,    			spawn,		SHCMD("alacritty --class \"floating\" -o 'window.dimensions = { columns = 120, lines = 30 }' -e mplay") },
	{ MODKEY,                       XK_bracketright,    		nextoccupied,	{ .i = +1 } },
	{ MODKEY,                       XK_bracketleft,    		nextoccupied,	{ .i = -1 } },
	{ MODKEY|ShiftMask,             XK_m,     			zoom,           {0} },
	{ MODKEY,             		XK_v,     			musictag 	},
	{ MODKEY,             		XK_c,     			spawn, 	   	SHCMD(TERMINAL " -e ranger") },
	{ MODKEY,                       XK_e,     			spawn, 	   	SHCMD("emacs") },
	{ 0,				XK_Print, 			spawn, 	   	SHCMD("flameshot gui") },
	// { 0,				XF86XK_AudioLowerVolume,   	spawn, 		SHCMD("mpc volume -5") },
	// { 0,				XF86XK_AudioRaiseVolume,   	spawn, 		SHCMD("mpc volume +5") },
	{ 0,				XF86XK_AudioMute,   	spawn, 		SHCMD("amixer set PCM toggle") },
	{ 0,				XF86XK_AudioLowerVolume,   	spawn, 		SHCMD("amixer set PCM 5%-") },
	{ 0,				XF86XK_AudioRaiseVolume,   	spawn, 		SHCMD("amixer set PCM 5%+") },
	{ 0,				XF86XK_AudioPlay, 		spawn,   	SHCMD("mpc toggle") },
	{ 0, 				XF86XK_AudioNext, 		spawn,   	SHCMD("mpc next") },
	{ 0, 				XF86XK_AudioPrev, 		spawn,   	SHCMD("mpc prev") },
	{ 0, 				XF86XK_MonBrightnessUp,    	spawn, 		SHCMD("/usr/bin/brightnessctl set +3%") },
	{ 0, 				XF86XK_MonBrightnessDown,  	spawn, 		SHCMD("/usr/bin/brightnessctl set 3%-") },
	{ MODKEY|ShiftMask,             XK_d,      			spawn,	   	SHCMD("bookmarks") },
	{ MODKEY,                       XK_p,      			spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, 			spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      			incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      			incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, 			zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    			view,           {0} },
	{ MODKEY,			XK_w,      			killclient,     {0} },
	{ MODKEY,                       XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      			setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  			setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  			togglefloating, {0} },
	{ MODKEY,                       XK_0,      			view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      			tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_Tab,    			tagswapmon	},
	{ MODKEY|ShiftMask,             XK_comma,  			tagmon,         {.i = -1 } },
  	{ MODKEY|ShiftMask,             XK_period, 			tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,      			                0)
	TAGKEYS(                        XK_2,      			                1)
	TAGKEYS(                        XK_3,      			                2)
	TAGKEYS(                        XK_4,      			                3)
	TAGKEYS(                        XK_5,      			                4)
	TAGKEYS(                        XK_6,      			                5)
	TAGKEYS(                        XK_7,      			                6)
	TAGKEYS(                        XK_8,      			                7)
	TAGKEYS(                        XK_9,      			                8)
	{ MODKEY|ShiftMask,             XK_q,      			quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
};


