#include "f8.h"
#include "munit.h"
#include "test.h"

#define STRING_1_BYTE_CHAR      "Single byte ascii symbols string"
#define STRING_1_BYTE_CHAR_L    L"Single byte ascii symbols string"
#define STRING_2_BYTE_CHAR \
    "\u041A\u0438\u0440\u0438\u043B\u043B\u0438\u0446\u0430"
#define STRING_2_BYTE_CHAR_L \
    L"\u041A\u0438\u0440\u0438\u043B\u043B\u0438\u0446\u0430"
#define STRING_3_BYTE_CHAR \
    "\u0814\u0820\u080C\u081D\u0813\u0829\u0809\u080C"
#define STRING_3_BYTE_CHAR_L \
    L"\u0814\u0820\u080C\u081D\u0813\u0829\u0809\u080C"
#define STRING_4_BYTE_CHAR      "𓁹𓁹𓁹𓁹𓁹"
#define STRING_4_BYTE_CHAR_L    L"𓁹𓁹𓁹𓁹𓁹"

const struct u_pair text_fixture[] = {
    {
        .utf8  = STRING_1_BYTE_CHAR,
        .utf32 = STRING_1_BYTE_CHAR_L,
        .len = sizeof(STRING_1_BYTE_CHAR) - 1,
        .size_utf8 = sizeof(STRING_1_BYTE_CHAR),
        .size_utf32 = sizeof(STRING_1_BYTE_CHAR_L),
    },
    {
        .utf8  = STRING_2_BYTE_CHAR,
        .utf32 = STRING_2_BYTE_CHAR_L,
        .len = (sizeof(STRING_2_BYTE_CHAR) - 1) / 2,
        .size_utf8 = sizeof(STRING_2_BYTE_CHAR),
        .size_utf32 = sizeof(STRING_2_BYTE_CHAR_L),
    },
    {
        .utf8  = STRING_3_BYTE_CHAR,
        .utf32 = STRING_3_BYTE_CHAR_L,
        .len = (sizeof(STRING_3_BYTE_CHAR) - 1) / 3,
        .size_utf8 = sizeof(STRING_3_BYTE_CHAR),
        .size_utf32 = sizeof(STRING_3_BYTE_CHAR_L),
    },
    {
        .utf8  = STRING_4_BYTE_CHAR,
        .utf32 = STRING_4_BYTE_CHAR_L,
        .len = (sizeof(STRING_4_BYTE_CHAR) - 1) / 4,
        .size_utf8 = sizeof(STRING_4_BYTE_CHAR),
        .size_utf32 = sizeof(STRING_4_BYTE_CHAR_L),
    },
};

const size_t text_fixture_size = sizeof(text_fixture);
const size_t text_fixture_len = sizeof(text_fixture)/sizeof(*text_fixture);

extern MunitSuite test_suite_utf8_strlen;
extern MunitSuite test_suite_utf8_strncpy;
extern MunitSuite test_suite_utf8_strnsize;
extern MunitSuite test_suite_utf8to32_strncpy_s;

static MunitSuite test_suite_f8 = {
    "/f8", NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char **argv)
{
    MunitSuite *suites = calloc(5, sizeof(MunitSuite));
    suites[0] = test_suite_utf8_strlen;
    suites[1] = test_suite_utf8_strncpy;
    suites[2] = test_suite_utf8_strnsize;
    suites[3] = test_suite_utf8to32_strncpy_s;

    test_suite_f8.suites = suites;

    int ret = munit_suite_main(&test_suite_f8, NULL, argc, argv);

    free(suites);
    return ret;
}
