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

const xx_token_names xx_tokens[] =
{
  { XX_T_INTEGER,             "INTEGER" },
  { XX_T_DOUBLE,              "DOUBLE" },
  { XX_T_STRING,              "STRING" },
  { XX_T_IDENTIFIER,          "IDENTIFIER" },
  { XX_T_AT,                  "@" },
  { XX_T_COMMA,               "," },
  { XX_T_ASSIGN,              "=" },
  { XX_T_COLON,               ":" },
  { XX_T_PARENTHESES_OPEN,    "(" },
  { XX_T_PARENTHESES_CLOSE,   ")" },
  { XX_T_BRACKET_OPEN,        "{" },
  { XX_T_BRACKET_CLOSE,       "}" },
  { XX_T_SBRACKET_OPEN,       "[" },
  { XX_T_SBRACKET_CLOSE,      "]" },
  {  0, NULL }
};

static void *xx_wrapper_alloc(size_t bytes)
{
  return malloc(bytes);
}

static void xx_wrapper_free(void *pointer)
{
  free(pointer);
}

/**
 * Creates a parser_token to be passed to the parser
 */
static void xx_parse_with_token(void* xx_parser, int opcode, int parsercode, xx_scanner_token *token, xx_parser_status *parser_status) {

  xx_parser_token *pToken;

  pToken = malloc(sizeof(xx_parser_token));
  pToken->opcode = opcode;
  pToken->token = token->value;
  pToken->token_len = token->len;
  pToken->free_flag = 1;

  xx_(
    xx_parser,    /* The parser */
    parsercode,   /* The major token code number */
    pToken,       /* The value for the token */
    parser_status /* Optional %extra_argument parameter */
  );

  token->value = NULL;
  token->len = 0;
}

int parse_program(const char **result, char *program, unsigned int program_length, char *file_path)
{
  char *error;
	xx_scanner_state *state;
	xx_scanner_token token;
	int scanner_status, status = EXIT_SUCCESS, start_lines;
	xx_parser_status *parser_status = NULL;
	void* xx_parser;

  /**
	 * Check if the program has any length
	 */
  if (!program_length || program_length < 2) {
    *result = "[]";
    return EXIT_SUCCESS;
  }

	/**
	 * Start the reentrant parser
	 */
	xx_parser = xx_Alloc(xx_wrapper_alloc);

  parser_status = malloc(sizeof(xx_parser_status));
  state = malloc(sizeof(xx_scanner_state));

  parser_status->status = XX_PARSING_OK;
	parser_status->scanner_state = state;
	parser_status->ret = NULL;
	parser_status->token = &token;
	parser_status->syntax_error = NULL;
	parser_status->number_brackets = 0;

  /**
	 * Initialize the scanner state
	 */
  state->active_token = 0;
	state->start = program;
	state->start_length = 0;
	state->active_file = file_path;
	state->active_line = 1;
	state->active_char = 1;
	state->class_line = 0;
	state->class_char = 0;
	state->method_line = 0;
	state->method_char = 0;
  state->end = state->start;

  token.value = NULL;

  while (0 <= (scanner_status = xx_get_token(state, &token))) {
    state->active_token = token.opcode;
    state->start_length = (program + program_length - state->start);

    switch (token.opcode) {
    case XX_T_IGNORE:
      break;
    case XX_T_NAMESPACE:
      xx_(xx_parser, XX_NAMESPACE, NULL, parser_status);
      break;
    case XX_T_DOTCOMMA:
      xx_(xx_parser, XX_DOTCOMMA, NULL, parser_status);
      break;
    case XX_T_IDENTIFIER:
      xx_parse_with_token(xx_parser, XX_T_IDENTIFIER, XX_IDENTIFIER, &token, parser_status);
      break;
    default:
      parser_status->status = XX_PARSING_FAILED;
      fprintf(stderr, "Scanner: unknown opcode %d\n", token.opcode);
      break;
    }

    if (parser_status->status != XX_PARSING_OK) {
      fprintf(stderr, "Scanner status error: opcode %d\n", token.opcode);
      status = EXIT_FAILURE;
      break;
    }

    state->end = state->start;
  }

  if (status != EXIT_FAILURE) {
    switch (scanner_status) {
    case XX_SCANNER_RETCODE_ERR:
    case XX_SCANNER_RETCODE_IMPOSSIBLE:
      {
        char *x = malloc(sizeof(char) * 1024);
        if (state->start) {
          sprintf(x, "Scanner error: %d %s", scanner_status, state->start);
        } else {
          sprintf(x, "Scanner error: %d", scanner_status);
        }
        fprintf(stderr, "%s\n", x);
        free(x);
        status = EXIT_FAILURE;
    }
      break;
    default:
      xx_(xx_parser, 0, NULL, parser_status);
    }
  }

  state->active_token = 0;
  state->start = NULL;

  if (parser_status->status != XX_PARSING_OK) {
    status = EXIT_FAILURE;
  }

  xx_Free(xx_parser, xx_wrapper_free);

  if (parser_status->ret) {
    *result = json_object_to_json_string(parser_status->ret);
  }

  free(parser_status);
	free(state);

  return status;
}
