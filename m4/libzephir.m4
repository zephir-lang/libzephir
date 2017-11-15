dnl
dnl This file contains local autoconf functions.

dnl
dnl LIBZEPHIR_RE2C_CHECK
dnl
dnl Search for the re2c binary and check the version
dnl -------------------------------------------------------------------------
AC_DEFUN([LIBZEPHIR_RE2C_CHECK],[
  AC_CHECK_PROG(RE2C, re2c, re2c)

  if test -n "$RE2C"; then
    AC_CACHE_CHECK([for re2c version], libzephir_cv_re2c_version, [
      re2c_vernum=`$RE2C --vernum 2>/dev/null`
      if test -z "$re2c_vernum"; then
        libzephir_cv_re2c_version=no
      elif test "$re2c_vernum" -lt "1306"; then
        libzephir_cv_re2c_version=invalid
      else
        if test "$re2c_vernum" -gt "1403"; then
          RE2C_FLAGS="--no-generation-date -W"
        else
          RE2C_FLAGS="--no-generation-date"
        fi

        libzephir_cv_re2c_version="`$RE2C --version | cut -d ' ' -f 2`"
      fi
    ])
  fi

  case $libzephir_cv_re2c_version in
    ""|no[)]
      AC_MSG_ERROR([re2c is required to build libzephir.])
      RE2C="exit 1;"
      ;;
    invalid[)]
      AC_MSG_ERROR([re2c 0.13.6 or later is required to build libzephir.])
      RE2C="exit 1;"
      ;;
  esac

  AC_SUBST(RE2C_FLAGS)
  AC_SUBST(RE2C)
])

dnl libzephir basic checks.
dnl --------------------------------------------------------------------------
AC_DEFUN([LIBZEPHIR_BASIC_CHECKS],[
  dnl Checks for programs.
  dnl ------------------------------------------------------------------------
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_CC_C_O])
  AC_REQUIRE([AC_PROG_INSTALL])
  AC_REQUIRE([AC_PROG_MAKE_SET])

  dnl Checks for typedefs, structures, and compiler characteristics.
  dnl ------------------------------------------------------------------------
  AC_REQUIRE([AC_C_CONST])
  AC_REQUIRE([AC_TYPE_SIZE_T])

  LIBZEPHIR_RE2C_CHECK

  dnl Checks for header files.
  dnl ------------------------------------------------------------------------
  AC_REQUIRE([AC_HEADER_STDC])
  AC_REQUIRE([AC_HEADER_ASSERT])
  AC_REQUIRE([AC_HEADER_STDBOOL])

  dnl Checks for library functions.
  dnl ------------------------------------------------------------------------
  AC_REQUIRE([AC_FUNC_MALLOC])

  dnl Test if we should test features that depend on 64-bitness.
  dnl ------------------------------------------------------------------------
  AC_CHECK_SIZEOF([void *])
  AM_CONDITIONAL([TEST_64BIT], [test "$ac_cv_sizeof_void_p" -eq 8])
])
