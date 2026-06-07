## .xinitrc
# This file is being read everytime X11 starts
# using xinit or startx.

#export FREETYPE_PROPERTIES="truetype:interpreter-version=38"

#if [ "$(pgrep acpi_control)" == "" ]; then
#	acpi_control &
#fi

xrdb ~/.Xresources;
exec dwm > /tmp/dwm.log
