# dwm version
VERSION = 6.6

# Customize below to fit your system

# paths
PREFIX = ~/.local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# Xinerama, comment if you don't want it
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
# *BSD (uncomment)
#FREETYPEINC = ${X11INC}/freetype2
#KVMLIB = -lkvm
# OpenBSD/NetBSD (uncomment)
#MANPREFIX = ${PREFIX}/man

# This is needed for the swallow patch
XCBLIBS = -lX11-xcb -lxcb -lxcb-res

# includes and libs
INCS = -I${X11INC} -I${FREETYPEINC}
LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS} ${XCBLIBS} ${KVMLIB} -lXrender

# flags
# FreeBSD: add -D__BSD_VISIBLE
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700L -DVERSION=\"${VERSION}\" ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=gnu99 -pedantic -Wall -Wno-deprecated-declarations -O2 -march=native ${INCS} ${CPPFLAGS}
LDFLAGS  = -Wl,-O2 -Wl,--as-needed -s ${LIBS}

# Solaris
#CFLAGS = -fast ${INCS} -DVERSION=\"${VERSION}\"
#LDFLAGS = ${LIBS}

# compiler and linker
CC = cc
