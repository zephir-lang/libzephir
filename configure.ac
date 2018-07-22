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

dnl Unless the user specified ARFLAGS, force it to be cr
dnl -------------------------------------------------------------------------
AC_ARG_VAR(ARFLAGS, [Flags for the archiver, defaults to <cr> if not set])
if test "x${ARFLAGS+set}" != "xset"; then
  ARFLAGS="cr"
fi

AC_LANG([C])
AC_CANONICAL_HOST

dnl Fairly severe build strictness
dnl -------------------------------------------------------------------------
AM_INIT_AUTOMAKE([foreign])

dnl Make the compilation flags quiet unless V=1 is used
dnl -------------------------------------------------------------------------
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl Check if the CFLAGS has been overridden (here before libtool and ar).
if test "x${CFLAGS+set}" = "xset"; then
  cflags_overridden=yes
else
  cflags_overridden=no
fi

LIBZEPHIR_BASIC_CHECKS

dnl Checks for libjson-c
dnl -------------------------------------------------------------------------
PKG_CHECK_MODULES([LIBJSONC], [json-c >= 0.11],,
  AC_MSG_ERROR([libjson-c 0.11 or newer not found.])
)

dnl Checks for json-c
dnl -------------------------------------------------------------------------
AC_CHECK_HEADERS([json-c/json.h], [json_found_headers=yes; break;])
AS_IF([test "x$json_found_headers" != "xyes"], [
  AC_MSG_ERROR([Unable to find json-c headers.])
])

dnl Enable ccache
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([ccache],
  [AS_HELP_STRING([--disable-ccache],
                  [do not use ccache for building (default is to use if found)])],
  [use_ccache=$enableval],
  [use_ccache=auto])

dnl Enable lcov
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([lcov],
  [AS_HELP_STRING([--enable-lcov],
                  [whether to enable lcov testing (default is no)])],
  [use_lcov=$enableval],
  [use_lcov=no])

dnl Enable lcov-branch-coverage
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([lcov-branch-coverage],
  [AS_HELP_STRING([--enable-lcov-branch-coverage],
                  [enable lcov testing branch coverage (default is no)])],
  [use_lcov_branch=yes],
  [use_lcov_branch=no])

dnl Installing manpages
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE(man,
  [AS_HELP_STRING([--disable-man],
                  [do not install man pages (default is to install)])],,
  enable_man=yes
)
AM_CONDITIONAL(ENABLE_MAN, test "$enable_man" != no)

dnl Enable debug
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [use debug compiler flags and macros (default is no)])],
  [enable_debug=$enableval],
  [enable_debug=no]
)

dnl Enable gprof profiling
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([gprof],
  [AS_HELP_STRING([--enable-gprof],
                  [use gprof profiling compiler flags (default is no)])],
  [enable_gprof=$enableval],
  [enable_gprof=no]
)

dnl Test if --enable-unit-test given
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([unit-test],
  [AS_HELP_STRING([--enable-unit-test],
                  [enable unit test (default is no)])],
  [enable_unit_test=$enableval],
  [enable_unit_test=no]
)

dnl Turn warnings into errors
dnl --------------------------------------------------------------------------
AC_ARG_ENABLE([werror],
  [AS_HELP_STRING([--enable-werror],
                  [treat certain compiler warnings as errors (default is no)])],
  [enable_werror=$enableval],
  [enable_werror=no]
)
AX_CHECK_COMPILE_FLAG([-Werror], [CFLAG_WERROR="-Werror"], [CFLAG_WERROR=""])

LEMON_FLAGS="-l"
if test "x$enable_debug" = xyes; then
  # Clear default -g -O2 flags
  if test "x$cflags_overridden" = xno; then
    CFLAGS=""
  fi

  LEMON_FLAGS="-s"
  AC_DEFINE(LIBZEPHIR_DEBUG, 1, [Whether debug is enabled])

  # Prefer -Og, fall back to -O0 if that is unavailable.
  AX_CHECK_COMPILE_FLAG(
    [-Og],
    [[DEBUG_CFLAGS="$DEBUG_CFLAGS -Og"]],
    [AX_CHECK_COMPILE_FLAG([-O0],[[DEBUG_CFLAGS="$DEBUG_CFLAGS -O0"]],,[[$CFLAG_WERROR]])],
    [[$CFLAG_WERROR]])

  # Prefer -g3, fall back to -g if that is unavailable.
  AX_CHECK_COMPILE_FLAG(
    [-g3],
    [[DEBUG_CFLAGS="$DEBUG_CFLAGS -g3"]],
    [AX_CHECK_COMPILE_FLAG([-g],[[DEBUG_CFLAGS="$DEBUG_CFLAGS -g"]],,[[$DEBUG_CFLAGS]])],
    [[$CFLAG_WERROR]])

  AX_CHECK_PREPROC_FLAG([-DDEBUG],[[DEBUG_CFLAGS="$DEBUG_CFLAGS -DDEBUG"]],,[[$DEBUG_CFLAGS]])
else
  AC_DEFINE(LIBZEPHIR_DEBUG, 0, [Whether debug is enabled])
fi

ERROR_CFLAGS=
if test "x$enable_werror" = "xyes"; then
  if test "x$CFLAG_WERROR" = "x"; then
     AC_MSG_ERROR("enable-werror set but -Werror is not usable")
  fi
  AX_CHECK_COMPILE_FLAG([-Werror=vla],[ERROR_CFLAGS="$ERROR_CFLAGS -Werror=vla"],,[[$CFLAG_WERROR]])
fi

if test "x$cflags_overridden" = "xno"; then
  AX_CHECK_COMPILE_FLAG([-Wall],[WARN_CFLAGS="$WARN_CFLAGS -Wall"],,[[$CFLAG_WERROR]])
  AX_CHECK_COMPILE_FLAG([-Wvla],[WARN_CFLAGS="$WARN_CFLAGS -Wvla"],,[[$CFLAG_WERROR]])

  ## Some compilers (gcc) ignore unknown -Wno-* options, but warn about all
  ## unknown options if any other warning is produced. Test the -Wfoo case, and
  ## set the -Wno-foo case if it works.
  AX_CHECK_COMPILE_FLAG([-Wunused-variable],[NOWARN_CFLAGS="$NOWARN_CFLAGS -Wno-unused-variable"],,[[$CFLAG_WERROR]])
fi

if test x$use_lcov = xyes; then
  if test x$LCOV = x; then
    AC_MSG_ERROR("lcov testing requested but lcov not found")
  fi

  if test x$GCOV = x; then
    AC_MSG_ERROR("lcov testing requested but gcov not found")
  fi

  if test x$GENHTML = x; then
    AC_MSG_ERROR("lcov testing requested but genhtml not found")
  fi

  LCOV="$LCOV --gcov-tool=$GCOV"

  AX_CHECK_LINK_FLAG([[--coverage]], [LDFLAGS="$LDFLAGS --coverage"],
    [AC_MSG_ERROR("lcov testing requested but --coverage linker flag does not work")])

  AX_CHECK_COMPILE_FLAG([--coverage],[CFLAGS="$CFLAGS --coverage"],
    [AC_MSG_ERROR("lcov testing requested but --coverage flag does not work")])

  AC_DEFINE(USE_COVERAGE, 1, [Whether coverage is enabled])
  CFLAGS="$CFLAGS -Og"
else
  AC_DEFINE(USE_COVERAGE, 0, [Whether coverage is enabled])
fi

if test x$use_lcov_branch != xno; then
  AC_SUBST(LCOV_OPTS, "$LCOV_OPTS --rc lcov_branch_coverage=1")
fi

if test "x$enable_gprof" = xyes; then
  AX_CHECK_COMPILE_FLAG([-pg],[GPROF_CFLAGS="-pg"],
    [AC_MSG_ERROR(gprof profiling requested but not available)],[[$CFLAG_WERROR]])

  AX_CHECK_LINK_FLAG([[-no-pie]], [GPROF_LDFLAGS="-no-pie"])

  AX_CHECK_LINK_FLAG([[-pg]],[GPROF_LDFLAGS="$GPROF_LDFLAGS -pg"],
    [AC_MSG_ERROR(gprof profiling requested but not available)],[[$GPROF_LDFLAGS]])
fi

case $host in
  *mingw*)
    TARGET_OS=windows
    ;;
  *darwin*)
    TARGET_OS=darwin
    ;;
  *linux*)
    TARGET_OS=linux
    ;;
  *)
    AC_MSG_ERROR(Unsupported host: $host. Please file a bug report.)
    ;;
esac

if test x$TARGET_OS != xwindows; then
  # All windows code is PIC, forcing it on just adds useless compile warnings
  AX_CHECK_COMPILE_FLAG([-fPIC],[PIC_FLAGS="-fPIC"])
fi

dnl this flag screws up non-darwin gcc even when the check fails. special-case it.
if test x$TARGET_OS = xdarwin; then
  AX_CHECK_LINK_FLAG([[-Wl,-dead_strip]], [LDFLAGS="$LDFLAGS -Wl,-dead_strip"])
fi

if test "x$use_ccache" != "xno"; then
  AC_MSG_CHECKING(if ccache should be used)
  if test x$CCACHE = x; then
    if test "x$use_ccache" = "xyes"; then
      AC_MSG_ERROR([ccache not found.]);
    else
      use_ccache=no
    fi
  else
    use_ccache=yes
    CC="$ac_cv_path_CCACHE $CC"
    CXX="$ac_cv_path_CCACHE $CXX"
  fi
  AC_MSG_RESULT($use_ccache)
fi

if test "x$use_ccache" = "xyes"; then
    AX_CHECK_PREPROC_FLAG([-Qunused-arguments],[CFLAGS="-Qunused-arguments $CFLAGS"])
fi

if test "x$enable_unit_test" = "xyes" ; then
  dnl This macro is defined in check.m4 and tests if check.h and
  dnl libcheck.a are installed in your system. It sets CHECK_CFLAGS and
  dnl CHECK_LIBS accordingly.
  dnl ------------------------------------------------------------------------
  PKG_CHECK_MODULES([CHECK], [check >= 0.9.6], have_check=yes,
    AC_MSG_ERROR([check 0.9.6 or newer not found.])
  )
else
  have_check=no
fi

AM_CONDITIONAL([TARGET_DARWIN], [test "x$TARGET_OS" = "xdarwin"])
AM_CONDITIONAL([TARGET_WINDOWS], [test "x$TARGET_OS" = "xwindows"])
AM_CONDITIONAL([TARGET_LINUX], [test "x$TARGET_OS" = "xlinux"])
AM_CONDITIONAL([HAVE_CHECK], [test x"$have_check" = "xyes"])
AM_CONDITIONAL([USE_LCOV], [test "x$use_lcov" = "xyes"])
AM_CONDITIONAL([ENABLE_DEBUG], [test "x$enable_debug" = "xyes"])

AC_CONFIG_HEADERS([config.h])

LT_INIT([shared static])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
])

AC_SUBST(DEBUG_CFLAGS)
AC_SUBST(WARN_CFLAGS)
AC_SUBST(NOWARN_CFLAGS)
AC_SUBST(ERROR_CFLAGS)
AC_SUBST(GPROF_CFLAGS)
AC_SUBST(GPROF_LDFLAGS)
AC_SUBST(LEMON_FLAGS)
AC_SUBST(PIC_FLAGS)

AC_OUTPUT

echo
echo "Options used to compile and link:"
echo "  with test     = $enable_unit_test"
echo "  debug enabled = $enable_debug"
echo "  gprof enabled = $enable_gprof"
echo "  target os     = $TARGET_OS"
echo "  build os      = $BUILD_OS"
echo
echo "  CC            = $CC"
echo "  CFLAGS        = $DEBUG_CFLAGS $WARN_CFLAGS $NOWARN_CFLAGS $ERROR_CFLAGS $GPROF_CFLAGS $CFLAGS"
echo "  CXX           = $CXX"
echo "  LDFLAGS       = $GPROF_LDFLAGS $LDFLAGS"
echo "  ARFLAGS       = $ARFLAGS"
echo "  LEMON_FLAGS   = $LEMON_FLAGS"
echo
