dnl Process this file with autoconf to produce a configure script.
dnl FIXME: move version to the version.h
dnl -------------------------------------------------------------------------
AC_INIT([libzephir], 0.0.1, [serghei@phalconphp.com])

dnl Include libzephir specific macro definitions first.
dnl -------------------------------------------------------------------------
sinclude($(datadir)/m4/libzephir.m4)

dnl AM_INIT_AUTOMAKE([-Wall -Werror foreign])
dnl -------------------------------------------------------------------------
AM_INIT_AUTOMAKE([-Wall foreign])

dnl Locate ar using standard macro.
dnl Old automake 1.11 does not know about `AM_PROG_AR'.
dnl -------------------------------------------------------------------------
m4_ifdef([AM_PROG_AR],
         [AM_PROG_AR],
         [AC_PATH_PROG(AR, ar, ar, $PATH)])

AC_CONFIG_MACRO_DIRS([m4])

AC_PROG_MAKE_SET

AC_CANONICAL_HOST

dnl Enable silent build by default.
dnl -------------------------------------------------------------------------
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl Checks for header files.
dnl -------------------------------------------------------------------------
AC_HEADER_STDC
AC_CHECK_HEADERS([assert.h stdlib.h string.h])

dnl Checks for programs.
dnl -------------------------------------------------------------------------
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RE2C

dnl Checks for typedefs, structures, and compiler characteristics.
dnl -------------------------------------------------------------------------
AC_C_CONST
AC_TYPE_SIZE_T

dnl Checks for library functions.
dnl -------------------------------------------------------------------------
AC_FUNC_MALLOC

LT_INIT

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

AC_OUTPUT
