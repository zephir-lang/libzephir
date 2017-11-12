dnl
dnl This file contains local autoconf functions.

dnl
dnl AC_PROG_RE2C
dnl
dnl Search for the re2c binary and check the version
dnl -------------------------------------------------------------------------
AC_DEFUN([AC_PROG_RE2C],[
  AC_CHECK_PROG(RE2C, re2c, re2c)
  if test -n "$RE2C"; then
    AC_CACHE_CHECK([for re2c version], libzephir_cv_re2c_version, [
      re2c_vernum=`$RE2C --vernum 2>/dev/null`
      if test -z "$re2c_vernum"; then
        libzephir_cv_re2c_version=no
      elif test "$re2c_vernum" -lt "1306"; then
        libzephir_cv_re2c_version=invalid
      else
        libzephir_cv_re2c_version="`$RE2C --version | cut -d ' ' -f 2  2>/dev/null` (ok)"
      fi
    ])
  fi
  case $libzephir_cv_re2c_version in
    ""|invalid|no[)]
      AC_MSG_ERROR([To use libzephir you need re2c 0.13.6 or later.])
      RE2C="exit 1;"
      ;;
  esac
  AC_SUBST(RE2C)
])
