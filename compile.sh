#!/bin/zsh

# simple compile.sh script
# by Albert Zeyer, 2010 or so
# code under zlib

cd "$(dirname $0)"
ROOTDIR="$(pwd)"
BUILDDIR="build"

# $1 - target
# $... - deps
function checkdeps() {
	local t="$1"
	[ ! -e "$t" ] && return -1
	for arg in $*; do
		[ "$arg" != "" ] && [ ! -e "$arg" ] && return -1
		[ "$arg" != "" ] && [ "$arg" -nt "$t" ] && return -1
	done
	return 0
}

# $1 - dep-file
function listdeps() {
	sed -e "s/\\\\$//g" -e "s/.*\\.o://g" \
		-e "s/^ *//g" -e "s/ *$//g" \
		"$1"
		#-e "s/^/\\\"/g" -e "s/$/\\\"/g" 
}

typeset -A C
C[cpp]=g++
C[cc]=g++
C[c]=gcc
C[m]=gcc

typeset -A Cflags
Cflags[.]="-I source"
[ "$(uname)" = "Darwin" ] && Cflags[.]+=" -I /Library/Frameworks/SDL.framework/Headers"

# $1 - c/cpp-file
# will compile the o-file
function srccompile() {
	local f="$1"
	local fext="${f##*.}"
	local o="$BUILDDIR/${f/.${fext}/.o}"
	local deps="$BUILDDIR/$f.deps"
	mkdir -p "$(dirname "$o")"
	[ -e $deps ] && checkdeps $o $f $(listdeps $deps) && echo "uptodate: $o" && return 0
	echo "compiling $o"
	$C[$fext] -c -MMD -MF $deps -o $o -iquote $(dirname $f) ${(z)Cflags[$f]} ${(z)Cflags[.]} -g $f || exit -1
}

typeset -A Lflags
Lflags[.]="-lz"
[ "$(uname)" = "Darwin" ] && Lflags[.]+=" -framework SDL -framework Cocoa"

# $1 - c/cpp-file
# will link all the $OBJS together
function srclink() {
	local f="$1"
	local fext="${f##*.}"
	local o="$BUILDDIR/${f/.${fext}/.o}"
	local b="bin/${f/.${fext}/}"
	checkdeps $b $OBJS $o && echo "uptodate: $b" && return 0
	echo "linking $b"
	$C[$fext] $OBJS $o -o $b ${(z)Lflags[$f]} ${(z)Lflags[.]} || exit -1
}

BINS=("source/main.cpp")

# compile all sources
OBJS=()
for f in source/*.cpp; do
	srccompile "$f"
	[[ ${BINS[(i)$f]} -gt ${#BINS} ]] && \
		OBJS=($OBJS "$BUILDDIR/${f/.cpp/.o}")
done

if [ "$(uname)" = "Darwin" ]; then
	srccompile "source/SDLmain.m"
	OBJS=($OBJS "$BUILDDIR/source/SDLmain.o")
fi

for b in $BINS; do
	mkdir -p "bin/$(dirname "$b")"
	srclink $b
done
