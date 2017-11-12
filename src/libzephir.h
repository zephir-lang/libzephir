/*
  +--------------------------------------------------------------------------+
  | Zephir Parser                                                            |
  | Copyright (c) 2013-2017 Zephir Team (https://zephir-lang.com/)           |
  |                                                                          |
  | This source file is subject the MIT license, that is bundled with this   |
  | package in the file LICENSE, and is available through the world-wide-web |
  | at the following url: https://zephir-lang.com/license.html               |
  +--------------------------------------------------------------------------+
*/

#ifndef LIBZEPHIR_H
#define LIBZEPHIR_H

#ifndef VERSION
/* Get libzephir version number. */
#include "version.h"
#endif

/**
 * Parses a comment returning an intermediate array representation
 */
extern int parse_program(char *program, unsigned int program_length, char *file_path);

#endif
