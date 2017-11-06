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

#include "xx.h"

#define XX_SCANNER_RETCODE_EOF -1
#define XX_SCANNER_RETCODE_ERR -2
#define XX_SCANNER_RETCODE_IMPOSSIBLE -3

/** Modes */
#define XX_T_IGNORE 297

#define XX_T_NAMESPACE 350

int xx_get_token(xx_scanner_state *s, xx_scanner_token *token);

#ifdef YYDEBUG
#undef YYDEBUG
#endif

#define YYDEBUG(s, c) do { \
  printf("State: %d char: %c\n", s, c); \
} while (0)

#endif
