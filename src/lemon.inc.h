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

#include <json-c/json.h>
#include <assert.h>
#include <string.h>

#include "zephir.h"
#include "scanner.h"
#include "xx.h"

static json_object *xx_ret_list(json_object *list_left, json_object *right_list)
{
	json_object *ret;
	int i, array_length;

	ret = json_object_new_array();

	if (list_left) {
		if (json_object_get_type(list_left) == json_type_array) {
			if (json_object_get_type(list_left) == json_type_array) {
				array_length = json_object_array_length(list_left);
				for (i = 0; i < array_length; i++) {
					json_object_array_add(ret, json_object_array_get_idx(list_left, i));
				}
			} else {
				json_object_array_add(ret, list_left);
			}
		}
	}

	json_object_array_add(ret, right_list);

	return ret;
}

static json_object *xx_ret_namespace(xx_parser_token *T, xx_scanner_state *state)
{
	json_object *ret = json_object_new_object();

	json_object_object_add(ret, "type", json_object_new_string("namespace"));
	json_object_object_add(ret, "name", json_object_new_string(T->token));

	json_object_object_add(ret, "file", json_object_new_string(state->active_file));
	json_object_object_add(ret, "line", json_object_new_int(state->active_line));
	json_object_object_add(ret, "char", json_object_new_int(state->active_char));

	return ret;
}

static json_object *xx_ret_use_aliases(json_object *use_aliases_list, xx_scanner_state *state)
{
	json_object *ret = json_object_new_object();

	json_object_object_add(ret, "type", json_object_new_string("use"));
	json_object_object_add(ret, "name", use_aliases_list);

	json_object_object_add(ret, "file", json_object_new_string(state->active_file));
	json_object_object_add(ret, "line", json_object_new_int(state->active_line));
	json_object_object_add(ret, "char", json_object_new_int(state->active_char));

	return ret;
}

static json_object *xx_ret_use_aliases_item(xx_parser_token *T, xx_parser_token *A, xx_scanner_state *state)
{
	json_object *ret = json_object_new_object();

	json_object_object_add(ret, "name", json_object_new_string(T->token));
	if (A) {
		json_object_object_add(ret, "alias", json_object_new_string(A->token));
	}

	json_object_object_add(ret, "file", json_object_new_string(state->active_file));
	json_object_object_add(ret, "line", json_object_new_int(state->active_line));
	json_object_object_add(ret, "char", json_object_new_int(state->active_char));

	return ret;
}
