/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */
/* clang-format off */

static int topbar = 0;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const int user_bh = 20;               /* add an defined amount of pixels to the bar height */

static const char *fonts[] = {
	"monospace:style=Bold:size=9"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */

static const unsigned int baralpha = 0xcc;
static const unsigned int borderalpha = OPAQUE;
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#aaaaaa", "#000000" },
	[SchemeSel] = { "#000000", "#aaaaaa" },
	[SchemeOut] = { "#000000", "#aaaaaa" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
