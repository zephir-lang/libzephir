dnl Process this file with autoconf to produce a configure script.
dnl FIXME: move version to the version.h
dnl -------------------------------------------------------------------------
AC_INIT([libzephir], 0.0.1, [serghei@phalconphp.com])

dnl Include libzephir specific macro definitions first.
dnl -------------------------------------------------------------------------
sinclude($(datadir)/m4/libzephir.m4)

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

LIBZEPHIR_BASIC_CHECKS

dnl Checks for header files.
dnl -------------------------------------------------------------------------
AC_CHECK_HEADERS([assert.h stdlib.h string.h])

dnl Checks for programs.
dnl -------------------------------------------------------------------------
AC_PROG_INSTALL

dnl Checks for typedefs, structures, and compiler characteristics.
dnl -------------------------------------------------------------------------
AC_C_CONST
AC_TYPE_SIZE_T

dnl Test if we should test features that depend on 64-bitness.
dnl -------------------------------------------------------------------------
AC_CHECK_SIZEOF([void *])
AM_CONDITIONAL([TEST_64BIT], [test "$ac_cv_sizeof_void_p" -eq 8])

dnl Checks for library functions.
dnl -------------------------------------------------------------------------
AC_FUNC_MALLOC

dnl Checks for modules.
dnl -------------------------------------------------------------------------
PKG_CHECK_MODULES([LIBJSONC], [json-c >= 0.11],, AC_MSG_ERROR([libjson-c-dev 0.11 or newer not found.]))
AC_CHECK_HEADERS([json-c/json.h], [json_found_headers=yes; break;])
AS_IF([test "x$json_found_headers" != "xyes"], [AC_MSG_ERROR([Unable to find json-c headers.])])

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
