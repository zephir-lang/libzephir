ROOT_DIR       := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SHELL          := $(shell which bash)

RE2C_BIN        = $(shell command -v re2c 2> /dev/null)

# no need for @
.SILENT: ;

# Run make build by default
.DEFAULT_GOAL = build

lemon:
	gcc -w lemon.c -o $@

scanner.c:
	echo -e "Generating scanner..."
	$(RE2C_BIN) -W --no-debug-info --no-generation-date --nested-ifs --output $@ scanner.re

parser.c: lemon
	echo -e "Generating parser..."
	./lemon -l -s parser.lemon

# Public targets

.PHONY: build
build: check base.c scanner.c parser.c
	cat base.c >> parser.c
	gcc -Wl,-rpath /usr/local/lib -I/usr/local/include -L/usr/local/lib -L/opt/local/lib -Wall -Werror -fpic -g3 -O0 -w parser.c scanner.c -ljson-c

.PHONY: check
check:
ifndef RE2C_BIN
	$(error "re2c is not available please install re2c: http://re2c.org/")
endif

.PHONY: clean
clean:
	rm -f *.o *.lo *.loT lemon scanner.c parser.c parser.out
	rm -rf .libs
