## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libzephir.la

libzephir_la_SOURCES = scanner.c zephir.c
include_HEADERS = libzephir.h

scanner.c: $(srcdir)/scanner.re
	$(RE2C) @RE2C_FLAGS@ --output $@ $(srcdir)/scanner.re

zephir.c: base.c $(srcdir)/lemon
	$(srcdir)/lemon -l -s zephir.lemon
	cat base.c >> zephir.c

lemon: lemon.c lempar.c
	$(CC) -w lemon.c -o $@

clean-local:
	-rm -f *.out *.loT lemon scanner.c zephir.c libzephir.so
	-rm -rf .libs
