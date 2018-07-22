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

START_TEST(test_empty_file)
{
	const char *actual;
	char program[] = "";
	int retval;

	retval = parse_program(&actual, program, 0, "eval code");

	ck_assert_int_eq(retval, 0);
	ck_assert_str_eq(actual, "[]");
}
END_TEST

START_TEST(test_namespace)
{
	const char *actual;
	const char *expectted = "[ { \"type\": \"namespace\", \"name\": \"Phalcon\", \"file\": \"eval code\", \"line\": 1, \"char\": 19 } ]";

	char program[] = "namespace Phalcon;";
	int retval;

	retval = parse_program(&actual, program, sizeof(program) / sizeof(*program), "eval code");

	ck_assert_int_eq(retval, 0);
	ck_assert_str_eq(actual, expectted);
}
END_TEST

START_TEST(test_single_import)
{
	const char *actual;
	const char *expectted = "[ { \"type\": \"namespace\", \"name\": \"Phalcon\", \"file\": \"eval code\", \"line\": 2, \"char\": 3 }, { \"type\": \"use\", \"name\": [ { \"name\": \"Psr\\\\Log\\\\LoggerAwareInterface\", \"file\": \"eval code\", \"line\": 2, \"char\": 33 } ], \"file\": \"eval code\", \"line\": 3, \"char\": 0 } ]";

	char program[] =
		"namespace Phalcon;\n"
		"use Psr\\Log\\LoggerAwareInterface;\n";

	int retval;

	retval = parse_program(&actual, program, sizeof(program) / sizeof(*program), "eval code");

	ck_assert_int_eq(retval, 0);
	ck_assert_str_eq(actual, expectted);
}
END_TEST

START_TEST(test_single_import_as)
{
	const char *actual;
	const char *expectted = "[ { \"type\": \"namespace\", \"name\": \"Phalcon\", \"file\": \"eval code\", \"line\": 3, \"char\": 3 }, { \"type\": \"use\", \"name\": [ { \"name\": \"Psr\\\\Log\\\\LoggerAwareInterface\", \"alias\": \"Loggerable\", \"file\": \"eval code\", \"line\": 3, \"char\": 47 } ], \"file\": \"eval code\", \"line\": 4, \"char\": 0 } ]";

	char program[] =
		"namespace Phalcon;\n"
		"\n"
		"use Psr\\Log\\LoggerAwareInterface as Loggerable;\n";

	int retval;

	retval = parse_program(&actual, program, sizeof(program) / sizeof(*program), "eval code");

	ck_assert_int_eq(retval, 0);
	ck_assert_str_eq(actual, expectted);
}
END_TEST

Suite * zephir_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Zephir Library");

	/* test001 test case */
	tc_core = tcase_create("test001");

	tcase_add_test(tc_core, test_empty_file);
	tcase_add_test(tc_core, test_namespace);
	tcase_add_test(tc_core, test_single_import);
	tcase_add_test(tc_core, test_single_import_as);

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

