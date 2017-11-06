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

/**
 * Wrapper to alloc memory within the parser
 */
static void *xx_wrapper_alloc(size_t bytes)
{
  return malloc(bytes);
}

/**
 * Wrapper to free memory within the parser
 */
static void xx_wrapper_free(void *pointer)
{
  free(pointer);
}

/**
 * Parses a comment returning an intermediate array representation
 */
int xx_parse_program(char *program, unsigned int program_length, char *file_path)
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
  if (!program_length) {
    return EXIT_FAILURE;
  }

  if (program_length < 2) {
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
    default:
      parser_status->status = XX_PARSING_FAILED;
      break;
    }
  }

  xx_Free(xx_parser, xx_wrapper_free);

  free(parser_status);
	free(state);

  return status;
}
