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
	[SchemeNorm]      = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]       = { col_gray1, col_gray3,  col_cyan  },
	[SchemeStatus]    = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { col_gray1, col_gray3,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]   = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
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
//	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1,        0  },
	{ NULL,       NULL,   "scratchpad1",   0,            1,           -1,       'a' },
	{ NULL,       NULL,   "scratchpad2",   0,            1,           -1,       'b' },
	{ NULL,       NULL,   "scratchpad3",   0,            1,           -1,       'c' },
	{ NULL,       NULL,   "scratchpad4",   0,            1,           -1,       'd' },
	{ NULL,       NULL,   "scratchpad5",   0,            1,           -1,       'e' },
	{ NULL,       NULL,   "scratchpad6",   0,            1,           -1,       'f' },
	{ NULL,       NULL,   "scratchpad7",   0,            1,           -1,       'g' },
	{ NULL,       NULL,   "scratchpad8",   0,            1,           -1,       'h' },
	{ NULL,       NULL,   "scratchpad9",   0,            1,           -1,       'i' },
	{ NULL,       NULL,   "scratchpad10",   0,            1,           -1,       'j' },
	{ NULL,       NULL,   "scratchpad11",   0,            1,           -1,       'k' },
	{ NULL,       NULL,   "scratchpad12",   0,            1,           -1,       'l' },
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
#define ALTKEY Mod1Mask
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
static const char *scratchpadcmd1[]  = {"a", "st", "-t", "scratchpad1", NULL};
static const char *scratchpadcmd2[]  = {"b", "st", "-t", "scratchpad2", NULL};
static const char *scratchpadcmd3[]  = {"c", "st", "-t", "scratchpad3", NULL};
static const char *scratchpadcmd4[]  = {"d", "st", "-t", "scratchpad4", NULL};
static const char *scratchpadcmd5[]  = {"e", "st", "-t", "scratchpad5", NULL};
static const char *scratchpadcmd6[]  = {"f", "st", "-t", "scratchpad6", NULL};
static const char *scratchpadcmd7[]  = {"g", "st", "-t", "scratchpad7", NULL};
static const char *scratchpadcmd8[]  = {"h", "st", "-t", "scratchpad8", NULL};
static const char *scratchpadcmd9[]  = {"i", "st", "-t", "scratchpad9", NULL};
static const char *scratchpadcmd10[] = {"j", "st", "-t", "scratchpad10", NULL};
static const char *scratchpadcmd11[] = {"k", "st", "-t", "scratchpad11", NULL};
static const char *scratchpadcmd12[] = {"l", "st", "-t", "scratchpad12", NULL};


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F1,  togglescratch,     {.v = scratchpadcmd1 } },
	{ MODKEY,                       XK_F2,  togglescratch,     {.v = scratchpadcmd2 } },
	{ MODKEY,                       XK_F3,  togglescratch,     {.v = scratchpadcmd3 } },
	{ MODKEY,                       XK_F4,  togglescratch,     {.v = scratchpadcmd4 } },
	{ MODKEY,                       XK_F5,  togglescratch,     {.v = scratchpadcmd5 } },
	{ MODKEY,                       XK_F6,  togglescratch,     {.v = scratchpadcmd6 } },
	{ MODKEY,                       XK_F7,  togglescratch,     {.v = scratchpadcmd7 } },
	{ MODKEY,                       XK_F8,  togglescratch,     {.v = scratchpadcmd8 } },
	{ MODKEY,                       XK_F9,  togglescratch,     {.v = scratchpadcmd9 } },
	{ MODKEY,                       XK_F10,  togglescratch,    {.v = scratchpadcmd10 } },
	{ MODKEY,                       XK_F11,  togglescratch,    {.v = scratchpadcmd11 } },
	{ MODKEY,                       XK_F12,  togglescratch,    {.v = scratchpadcmd12 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_g,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_0,      setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ Mod1Mask,                     XK_minus,  setborderpx,    {.i = -1 } },
	{ Mod1Mask,                     XK_plus,   setborderpx,    {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_0,      setborderpx,    {.i = 0 } },
	{ Mod1Mask,                     XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ Mod1Mask,                     XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ Mod1Mask,                     XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ Mod1Mask,                     XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ Mod1Mask|ShiftMask,           XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ Mod1Mask|ShiftMask,           XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ Mod1Mask|ShiftMask,           XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ Mod1Mask|ShiftMask,           XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ Mod1Mask|ControlMask,         XK_k,      moveresizeedge, {.v = "t"} },
	{ Mod1Mask|ControlMask,         XK_j,      moveresizeedge, {.v = "b"} },
	{ Mod1Mask|ControlMask,         XK_h,      moveresizeedge, {.v = "l"} },
	{ Mod1Mask|ControlMask,         XK_l,      moveresizeedge, {.v = "r"} },
	{ Mod1Mask|ControlMask|ShiftMask, XK_k,    moveresizeedge, {.v = "T"} },
	{ Mod1Mask|ControlMask|ShiftMask, XK_j,    moveresizeedge, {.v = "B"} },
	{ Mod1Mask|ControlMask|ShiftMask, XK_h,    moveresizeedge, {.v = "L"} },
	{ Mod1Mask|ControlMask|ShiftMask, XK_l,    moveresizeedge, {.v = "R"} },
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

