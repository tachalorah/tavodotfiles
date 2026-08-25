/* clang-format off */
//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	{ " ^c#e12323^⛅ ", "~/.local/scripts/bar-wttr", 30,	0 },
	{ " ^c#f06903^💿 ", "df -h | awk '/\\/$/ { print $3\" \"$5\" \"$4 }'", 5,	0 },
	{ " ^c#06a43e^ ",  "free -h | awk 'NR==2 { print $3 }'", 1,	0 },
	{ " ^c#f06903^📶 ", "nmcli -f IN-USE,SIGNAL dev wifi list | awk '/^\\*/ { print $2\"%\" }'", 1, 0},
	{ " ^c#2779e1^🌎 ", "fcitx5-remote -n", 1, 0 },
	{ " ^c#06a43e^",    "~/.local/scripts/bar-volume", 1, 0 },
	{ " ^c#dc206f^🔋 ", "~/.local/scripts/bar-battery", 1, 0 },
	{ " ^c#2779e1^📅 ", "date '+%a %d.%m'",	1, 0 },
	{ " ^c#c3c3c3^🕓 ", "date '+%r  '",	1, 0 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = " ";
static unsigned int delimLen = 5;
