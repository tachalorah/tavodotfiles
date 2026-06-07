/* clang-format off */
/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#0e0e0e",   /* during input */
	[FAILED] = "black",   /* wrong password */
};

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.15;

/* lock screen opacity */
static const float alpha = 0.8;

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* default message */
static const char *message = "Suckless: Software that sucks less.";

/* text color */
static const char *text_color = "#aaaaaa";

/* text size (must be a valid size) */
static const char *font_name = "MonaspiceNe Nerd Font Propo:size=10";
