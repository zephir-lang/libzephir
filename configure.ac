AC_PREREQ(2.64)

dnl Process this file with autoconf to produce a configure script.
dnl FIXME: move version to the version.h
dnl -------------------------------------------------------------------------
AC_INIT([Zephir Library], 0.0.1, [serghei@phalconphp.com])

dnl Include libzephir specific macro definitions first
dnl -------------------------------------------------------------------------
sinclude(m4/libzephir.m4)

dnl AM_INIT_AUTOMAKE([-Wall -Werror foreign])
dnl -------------------------------------------------------------------------
AM_INIT_AUTOMAKE([-Wall foreign])

dnl locate ar using standard macro
dnl -------------------------------------------------------------------------
m4_ifdef([AM_PROG_AR],
         [AM_PROG_AR],
         [AC_PATH_PROG(AR, ar, ar, $PATH)])

AC_CONFIG_MACRO_DIRS([m4])

AC_PROG_MAKE_SET

AC_CANONICAL_HOST

dnl enable silent build by default
dnl -------------------------------------------------------------------------
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl Search for the re2c binary and check the version
dnl -------------------------------------------------------------------------
AC_DEFUN([AC_PROG_RE2C],[
  AC_CHECK_PROG(RE2C, re2c, re2c)
  if test -n "$RE2C"; then
     AC_CACHE_CHECK([for re2c version], libzephir_cv_re2c_version, [
       re2c_vernum=`$RE2C --vernum 2>/dev/null`
       if test -z "$re2c_vernum" || test "$re2c_vernum" -lt "1306"; then
         libzephir_cv_re2c_version=invalid
       else
        libzephir_cv_re2c_version="`$RE2C --version | cut -d ' ' -f 2  2>/dev/null` (ok)"
      fi
    ])
  fi
  case $libzephir_cv_re2c_version in
    ""|invalid[)]
      AC_MSG_ERROR([You will need re2c 0.13.6 or later.])
      ;;
  esac
  AC_SUBST(RE2C)
])

dnl Checks for header files.
dnl -------------------------------------------------------------------------
AC_HEADER_STDC
AC_CHECK_HEADERS([assert.h stdlib.h string.h])

dnl checks for programs
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
