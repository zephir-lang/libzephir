/*
  +--------------------------------------------------------------------------+
  | Zephir Library                                                           |
  | Copyright (c) 2013-2018 Zephir Team (https://zephir-lang.com/)           |
  |                                                                          |
  | This source file is subject the MIT license, that is bundled with this   |
  | package in the file LICENSE, and is available through the world-wide-web |
  | at the following url: https://zephir-lang.com/license.html               |
  +--------------------------------------------------------------------------+
*/

#include <stdio.h>
#include <string.h>

#include "xx.h"
#include "scanner.h"

#define YYCTYPE unsigned char
#define YYCURSOR (s->start)
#define YYLIMIT (s->end)
#define YYMARKER qm

int xx_get_token(xx_scanner_state *s, xx_scanner_token *token)
{
	char *start = YYCURSOR, *qm;
	int status = XX_SCANNER_RETCODE_IMPOSSIBLE;
	// TODO
	// int is_constant = 0, j;

	while (XX_SCANNER_RETCODE_IMPOSSIBLE == status) {
		/*!re2c
		re2c:indent:top = 2;
		re2c:yyfill:enable = 0;

		'namespace' {
			s->active_char += sizeof("namespace")-1;
		}

		[ \t\r]+ {
			s->active_char += (YYCURSOR - start);
			token->opcode = XX_T_IGNORE;
			return 0;
		}

		[\n] {
			s->active_line++;
			s->active_char = 0;
			token->opcode = XX_T_IGNORE;
			return 0;
		}

		"\000" {
			status = XX_SCANNER_RETCODE_EOF;
			break;
		}

		[^] {
			status = XX_SCANNER_RETCODE_ERR;
			break;
		}

		*/
	}

	return status;
}

/*
 * Local variables:
 * mode: c
 * tab-width: 4
 * indent-tabs-mode: t
 * coding: utf-8
 * End:
 */
