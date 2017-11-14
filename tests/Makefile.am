## Process this file with automake to produce Makefile.in

TESTS = check_libzephir
check_PROGRAMS = check_libzephir
check_libzephir_SOURCES = check_libzephir.c $(top_builddir)/src/libzephir.h
check_libzephir_CFLAGS = @CHECK_CFLAGS@
check_libzephir_LDADD = $(top_builddir)/src/libzephir.la @CHECK_LIBS@
