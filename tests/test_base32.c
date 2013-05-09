#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "../src/base32.h"

START_TEST (test_base32)
{
  char str[] = "This is a test.";
  char correct_encoded[] = "KRUGS4ZANFZSAYJAORSXG5BO";

  char *encoded = NULL;
  encoded = malloc(strlen(str) * 2 + 1);

  int ret = base32_encode(str, strlen(str), encoded);

  ck_assert_int_eq(ret, 1);
  ck_assert_str_eq (encoded, correct_encoded);

  free(encoded);
}
END_TEST

START_TEST (test_base32_encode_block)
{
  char str[] = "TEST.";
  char correct_encoded[] = "KRCVGVBO";

  char encoded[9];

  base32_encode_block(str, encoded);

  ck_assert_str_eq(encoded, correct_encoded);
}
END_TEST

Suite*
base32_suite(void)
{
  Suite* s = suite_create("Base32");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test (tc_core, test_base32);
  tcase_add_test (tc_core, test_base32_encode_block);
  suite_add_tcase(s, tc_core);

  return s;
}

int
main(void)
{
  int number_failed;
  Suite *s = base32_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
