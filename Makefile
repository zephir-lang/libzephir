ROOT_DIR       := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SHELL          := $(shell which bash)

RE2C_FLAGS     ?=
RE2C_BIN        = $(shell command -v re2c 2> /dev/null)

lemon:
	gcc -w lemon.c -o $@

scanner.c:
	$(RE2C_BIN) $(RE2C_FLAGS) --no-generation-date -o $@ scanner.re

# Run make build by default
.DEFAULT_GOAL = build

# Public targets

.PHONY: build
build: check lemon scanner.c

.PHONY: check
check:
ifndef RE2C_BIN
	$(error "re2c is not available please install re2c: http://re2c.org/")
endif
