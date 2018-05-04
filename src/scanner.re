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
	int is_constant = 0, j;

	while (XX_SCANNER_RETCODE_IMPOSSIBLE == status) {
		/*!re2c
		re2c:indent:top = 2;
		re2c:yyfill:enable = 0;

		'namespace' {
			s->active_char += sizeof("namespace")-1;
			token->opcode = XX_T_NAMESPACE;
			return 0;
		}

		IDENTIFIER = [\\_\$]?[_a-zA-Z\\][a-zA-Z0-9_\\]*;
		IDENTIFIER {
			if (start[0] == '$') {
				token->value = strndup(start + 1, YYCURSOR - start - 1);
				token->len = YYCURSOR - start - 1;
				s->active_char += (YYCURSOR - start - 1);
			} else {
				token->value = strndup(start, YYCURSOR - start);
				token->len = YYCURSOR - start;
				s->active_char += (YYCURSOR - start);
			}


			if (token->len > 3 && token->value[0] == '_') {

				if (!strcmp(token->value, "_GET")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_POST")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_REQUEST")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_COOKIE")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_SERVER")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_SESSION")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_FILES")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}

				if (!strcmp(token->value, "_ENV")) {
					token->opcode = XX_T_IDENTIFIER;
					return 0;
				}
			}

			/* This is hack */
			if ((token->len == 1 && (!memcmp(token->value, "_", sizeof("_")-1)))
				|| (token->len == 2 && (!memcmp(token->value, "__", sizeof("__")-1)))
				|| (token->len == 3 && (!memcmp(token->value, "___", sizeof("___")-1)))
				|| (token->len == 4 && (!memcmp(token->value, "____", sizeof("____")-1)))
				) {
				token->opcode = XX_T_IDENTIFIER;
				return 0;
			}

			is_constant = 1;
			for (j = 0; j < token->len; j++) {
				if (!((token->value[j] >= 'A' && token->value[j] <= 'Z') || (token->value[j] >= '0' && token->value[j] <= '9') || token->value[j] == '_')) {
					is_constant = 0;
					break;
				}
			};
			if (is_constant) {
				token->opcode = XX_T_CONSTANT;
			} else {
				token->opcode = XX_T_IDENTIFIER;
			}
			return 0;
		}

		";" {
			s->active_char++;
			token->opcode = XX_T_DOTCOMMA;
			return 0;
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
