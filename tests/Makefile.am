## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir) -I$(top_srcdir)/tests

LIBZEPHIR_LA = $(top_builddir)/src/libzephir.la

TESTS =
TESTS += check_libzephir

check_PROGRAMS =
check_PROGRAMS += check_libzephir

EXTRA_DIST =
EXTRA_DIST += $(TESTS)

check_libzephir_SOURCES = check_libzephir.c $(top_builddir)/src/libzephir.h

check_libzephir_CFLAGS = @CHECK_CFLAGS@
check_libzephir_LDADD = $(LIBZEPHIR_LA) @CHECK_LIBS@

CK_VERBOSITY = verbose

distclean-local:
	-rm -rf $(testsubdir)
	-rm -f *.gcda *.gcno
