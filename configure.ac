dnl Process this file with autoconf to produce a configure script.

dnl Minimum Autoconf version required.
dnl -------------------------------------------------------------------------
AC_PREREQ(2.53)

AC_INIT([Zephir Library], [(see version.h)], [serghei@phalconphp.com], [libzephir], [https://zephir-lang.com/])

dnl Include libzephir specific macro definitions first.
dnl -------------------------------------------------------------------------
m4_include([m4/libzephir.m4])

AM_INIT_AUTOMAKE([foreign -Wall])

dnl Locate ar using standard macro.
dnl Old automake 1.11 does not know about `AM_PROG_AR'.
dnl -------------------------------------------------------------------------
m4_ifdef([AM_PROG_AR],
         [AM_PROG_AR],
         [AC_PATH_PROG(AR, ar, ar, $PATH)])

AC_CONFIG_MACRO_DIRS([m4])

dnl Enable silent build by default.
dnl -------------------------------------------------------------------------
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

LIBZEPHIR_BASIC_CHECKS

dnl Checks for modules.
dnl -------------------------------------------------------------------------
PKG_CHECK_MODULES([LIBJSONC], [json-c >= 0.11],,
  AC_MSG_ERROR([libjson-c 0.11 or newer not found.])
)

AC_CHECK_HEADERS([json-c/json.h], [json_found_headers=yes; break;])
AS_IF([test "x$json_found_headers" != "xyes"], [
  AC_MSG_ERROR([Unable to find json-c headers.])
])

AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
  [use debug compiler flags and macros (default is no)])],
  [enable_debug=$enableval],
  [enable_debug=no])

if test "x$enable_debug" = xyes; then
   CFLAGS="$CFLAGS -DDEBUG -g3 -O0"
else
  CFLAGS="$CFLAGS -O3"
fi

LT_INIT([shared static])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

AC_OUTPUT
