## Process this file with automake to produce Makefile.in

include $(top_srcdir)/build/Makefile.am.common

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir) \
	-I$(top_srcdir)/tests

TESTS += check_libzephir

check_PROGRAMS += check_libzephir

EXTRA_DIST += \
	install-re2c \
	$(TESTS)

check_libzephir_SOURCES = \
	check_libzephir.c \
	$(top_builddir)/src/libzephir.h

check_libzephir_CFLAGS = @CHECK_CFLAGS@

check_libzephir_LDADD = \
	$(LIBZEPHIR_LA) \
	@CHECK_LIBS@

CK_VERBOSITY = verbose

distclean-local:
	-rm -rf $(testsubdir)
	-rm -f *.gcda *.gcno

maintainer-clean-local:
	-rm -f Makefile.in
