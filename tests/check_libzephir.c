/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdlib.h>
#include <check.h>
#include "../src/libzephir.h"

START_TEST(test_namespace)
{
  const char *actual;
  char program[] = "namespace Phalcon;";
  int retval;

  retval = parse_program(&actual, program, sizeof(program) / sizeof(*program), "eval code");

  ck_assert_int_eq(retval, 0);
  ck_assert_str_eq(actual, "[ { \"type\": \"namespace\", \"name\": \"Phalcon\", \"file\": \"eval code\", \"line\": 1, \"char\": 19 } ]");
}
END_TEST

Suite * zephir_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Zephir Library");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_namespace);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;


  s = zephir_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

