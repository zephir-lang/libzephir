dnl Process this file with autoconf to produce a configure script.

dnl Prelude.
dnl -------------------------------------------------------------------------
AC_PREREQ(2.53)
AC_INIT([Zephir Library], [0.0.1], [serghei@phalconphp.com], [libzephir], [https://zephir-lang.com/])

dnl Set sane defaults for various variables
test -z "$SED" && SED=sed

dnl Include libzephir specific macro definitions first.
dnl -------------------------------------------------------------------------
m4_include([m4/libzephir.m4])

dnl The place to put some extra build scripts installed.
dnl -------------------------------------------------------------------------
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])

dnl Fairly severe build strictness
dnl -------------------------------------------------------------------------
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

dnl Locate ar using standard macro.
dnl Old automake 1.11 does not know about `AM_PROG_AR'.
dnl -------------------------------------------------------------------------
m4_ifdef([AM_PROG_AR],
         [AM_PROG_AR],
         [AC_PATH_PROG(AR, ar, ar, $PATH)])

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

dnl This macro is defined in check.m4 and tests if check.h and
dnl libcheck.a are installed in your system. It sets CHECK_CFLAGS and
dnl HECK_LIBS accordingly.
dnl ------------------------------------------------------------------------
PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])

AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [use debug compiler flags and macros (default is no)])],
  [enable_debug=$enableval],
  [enable_debug=no]
)

AC_ARG_ENABLE([gcov],
  [AS_HELP_STRING([--enable-gcov],
                  [whether to include gcov symbols (default is no)])],
  [enable_gcov=$enableval],
  [enable_gcov=no]
)

LEMON_FLAGS="-l"

if [test "x$enable_debug" = xyes] || [test "x$enable_gcov" = xyes]; then
  LEMON_FLAGS="-s"

  AC_DEFINE(LIBZEPHIR_DEBUG, 1, [Whether enabled debug])

  dnl Remove all optimization flags from CFLAGS
  changequote({,})
  CFLAGS=`echo "$CFLAGS" | $SED -e 's/-O[0-9s]*//g'`
  CXXFLAGS=`echo "$CXXFLAGS" | $SED -e 's/-O[0-9s]*//g'`

  CFLAGS=`echo "$CFLAGS" | $SED -e 's/-g[0-9]*//g'`
  CXXFLAGS=`echo "$CXXFLAGS" | $SED -e 's/-g[0-9]*//g'`
  changequote([,])

  CFLAGS="$CFLAGS -g -O0"
  CXXFLAGS="$CXXFLAGS -g -O0"

  if test "x$enable_gcov" = xyes; then
    dnl FIXME Deal with clang
    if test "$GCC" != "yes"; then
      AC_MSG_ERROR([GCC is required for --enable-gcov])
    fi

    AC_DEFINE(HAVE_GCOV, 1, [Whether you have gcov])

    CFLAGS="$CFLAGS -fprofile-arcs -ftest-coverage"
    CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"
  else
    AC_DEFINE(HAVE_GCOV, 0, [Whether you have gcov])
  fi
else
  CFLAGS="$CFLAGS -O3"
  AC_DEFINE(LIBZEPHIR_DEBUG, 0, [Whether enabled debug])
fi

AC_SUBST(LEMON_FLAGS)

AC_CONFIG_HEADERS([config.h])

LT_INIT([shared static])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])

AC_OUTPUT
