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

#ifndef LIBZEPHIR_H
#define LIBZEPHIR_H

/**
 * @brief Parses a program returning an intermediate array representation
 */
int parse_program(const char **result, char *program, unsigned int program_length, char *file_path);

#endif // LIBZEPHIR_H
