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

#ifndef LIBZEPHIR_SCANNER_H
#define LIBZEPHIR_SCANNER_H

#ifdef YYDEBUG
#undef YYDEBUG
#endif

#define YYDEBUG(s, c) do { \
  printf("State: %d char: %c\n", s, c); \
} while (0)

#endif
