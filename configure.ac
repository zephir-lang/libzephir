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

dnl Checks for libraries.
dnl -------------------------------------------------------------------------
PKG_CHECK_MODULES([LIBJSONC], [json-c >= 0.9],, AC_MSG_ERROR([libjson-c-dev 0.9 or newer not found.]))

LT_INIT

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])

AC_OUTPUT
