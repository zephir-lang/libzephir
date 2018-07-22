## Process this file with automake to produce Makefile.in

include $(top_srcdir)/build/Makefile.am.common

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir) \
	-I$(top_srcdir)/tests

TESTS += test001

check_PROGRAMS += test001

EXTRA_DIST += \
	install-re2c \
	$(TESTS)

test001_SOURCES = \
	test001.c \
	$(top_builddir)/src/libzephir.h

test001_CFLAGS = @CHECK_CFLAGS@

test001_LDADD = \
	$(LIBZEPHIR_LA) \
	@CHECK_LIBS@

CK_VERBOSITY = verbose

distclean-local:
	-rm -rf $(testsubdir)
	-rm -f *.gcda *.gcno

maintainer-clean-local:
	-rm -f Makefile.in
