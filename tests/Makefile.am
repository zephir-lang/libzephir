## Process this file with automake to produce Makefile.in

include $(top_srcdir)/build/Makefile.am.common

AM_CPPFLAGS = \
	-I$(top_srcdir)/src \
	-I$(top_srcdir) \
	-I$(top_srcdir)/tests

TESTS += test001
TESTS += test_comments

check_PROGRAMS += $(TESTS)

EXTRA_DIST += $(TESTS)
EXTRA_DIST += install-re2c

test001_SOURCES = \
	test001.c \
	$(top_builddir)/src/libzephir.h

test001_CFLAGS = @CHECK_CFLAGS@

test001_LDADD = \
	$(LIBZEPHIR_LA) \
	@CHECK_LIBS@

test_comments_SOURCES = \
	test_comments.c \
	$(top_builddir)/src/libzephir.h

test_comments_CFLAGS = @CHECK_CFLAGS@

test_comments_LDADD = \
	$(LIBZEPHIR_LA) \
	@CHECK_LIBS@

CK_VERBOSITY = verbose

distclean-local:
	-rm -rf $(testsubdir)
	-rm -f *.gcda *.gcno

maintainer-clean-local:
	-rm -f Makefile.in
