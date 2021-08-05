/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 6;       /* vertical padding of bar */
static const int sidepad            = 6;       /* horizontal padding of bar */
static const char *fonts[]          = { "JetBrainsMonoMedium Nerd Font:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#1B1D1E";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#F8F8F2";
static const char col_gray4[]       = "#F8F8F2";
static const char col_cyan[]        = "#56ADBC";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        0  },
	//{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1,        0  },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd1[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd2[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd3[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd4[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd5[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd6[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd7[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd8[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd9[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd10[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd11[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *scratchpadcmd12[] = {"s", "st", "-t", "scratchpad", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,     togglescratch,  {.v = scratchpadcmd1 } },
	{ MODKEY,                       XK_F2,     togglescratch,  {.v = scratchpadcmd2 } },
	{ MODKEY,                       XK_F3,     togglescratch,  {.v = scratchpadcmd3 } },
	{ MODKEY,                       XK_F4,     togglescratch,  {.v = scratchpadcmd4 } },
	{ MODKEY,                       XK_F5,     togglescratch,  {.v = scratchpadcmd5 } },
	{ MODKEY,                       XK_F6,     togglescratch,  {.v = scratchpadcmd6 } },
	{ MODKEY,                       XK_F7,     togglescratch,  {.v = scratchpadcmd7 } },
	{ MODKEY,                       XK_F8,     togglescratch,  {.v = scratchpadcmd8 } },
	{ MODKEY,                       XK_F9,     togglescratch,  {.v = scratchpadcmd9 } },
	{ MODKEY,                       XK_F10,    togglescratch,  {.v = scratchpadcmd10 } },
	{ MODKEY,                       XK_F11,    togglescratch,  {.v = scratchpadcmd11 } },
	{ MODKEY,                       XK_F12,    togglescratch,  {.v = scratchpadcmd12 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_0,      setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ Mod1Mask,                     XK_minus,  setborderpx,    {.i = -1 } },
	{ Mod1Mask,                     XK_plus,   setborderpx,    {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_0,      setborderpx,    {.i = 0 } },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

