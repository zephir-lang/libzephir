ROOT_DIR       := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SHELL          := $(shell which bash)

RE2C_FLAGS     ?=
RE2C_BIN        = $(shell command -v re2c 2> /dev/null)

# no need for @
.SILENT: ;

# Run make build by default
.DEFAULT_GOAL = build

lemon:
	gcc -w lemon.c -o $@

scanner.c:
	echo -e "Generating scanner..."
	$(RE2C_BIN) $(RE2C_FLAGS) --no-generation-date -o $@ scanner.re

parser.c: lemon
	echo -e "Generating parser..."
	./lemon -s parser.lemon
	cat base.c >> parser.c

# Public targets

.PHONY: build
build: check parser.c

.PHONY: check
check:
ifndef RE2C_BIN
	$(error "re2c is not available please install re2c: http://re2c.org/")
endif

.PHONY: clean
clean:
	rm -f *.o *.lo *.loT lemon scanner.c parser.c parser.out
	rm -rf .libs
