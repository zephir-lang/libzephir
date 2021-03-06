#!/bin/sh
#
# Zephir Library
# Copyright (c) 2013-2018 Zephir Team (https://zephir-lang.com/)
#
# This source file is subject the MIT license, that is bundled with this
# package in the file LICENSE, and is available through the world-wide-web
# at the following url: https://zephir-lang.com/license.html
#

# Run this to generate configure, Makefile.in's, etc

set -e

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

ORIGDIR=`pwd`
cd ${srcdir}

if [ -z ${LIBTOOLIZE} ] && GLIBTOOLIZE="`which glibtoolize 2>/dev/null`"; then
    LIBTOOLIZE="${GLIBTOOLIZE}"
    export LIBTOOLIZE
fi

echo "Checking for autoreconf ..."
(autoreconf --version) < /dev/null > /dev/null 2>&1 || {
    (autoconf --version) < /dev/null > /dev/null 2>&1 || {
        echo
        echo "**Error**: You must have the GNU Build System (autoconf, automake, "
        echo "libtool, etc) to update the build system.  Download the appropriate"
        echo "packages for your distribution, or get the source tar balls from"
        echo "ftp://ftp.gnu.org/pub/gnu/."
        exit 1
    }
    echo
    echo "**Error**: Your version of autoconf is too old (you need at least 2.57)"
    echo "to update the build system.  Download the appropriate updated package"
    echo "for your distribution, or get the source tar ball from"
    echo "ftp://ftp.gnu.org/pub/gnu/."
    exit 1
}

echo "Checking for aclocal ..."
(aclocal --version) < /dev/null > /dev/null 2>&1 || {
    echo
    echo "**Error**: You must have GNU Automake to compile this package."
    echo "Download the appropriate package for your distribution,"
    echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
    exit 1
}

echo "Start autotools ..."

echo "Running autoreconf ..."
# - The --force option rebuilds the configure script regardless of its
#   timestamp in relation to that of the file configure.ac.
# - The option --install copies some missing files to the directory,
#   including the text files e.g. COPYING and INSTALL.
autoreconf --verbose --install --force --warnings=all || exit $?

echo "Removing autom4te.cache ..."
rm -rf autom4te.cache

cd ${ORIGDIR}

echo "Finished."
