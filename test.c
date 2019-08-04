#include "f8.h"
#include "munit.h"
#include "test.h"

const struct u_pair text_fixture[] = {
    {
        .utf8  =  "Single byte ascii symbols string",
        .utf32 = L"Single byte ascii symbols string"
    },
    {
        .utf8  =  "\u041A\u0438\u0440\u0438\u043B\u043B\u0438\u0446\u0430",
        .utf32 = L"\u041A\u0438\u0440\u0438\u043B\u043B\u0438\u0446\u0430"
    },
    {
        .utf8  =  "\u0814\u0820\u080C\u081D\u0813\u0829\u0809\u080C",
        .utf32 = L"\u0814\u0820\u080C\u081D\u0813\u0829\u0809\u080C"
    },
    {
        .utf8  =  "𓁹𓁹𓁹𓁹𓁹",
        .utf32 = L"𓁹𓁹𓁹𓁹𓁹"
    }
};

const size_t text_fixture_size = sizeof(text_fixture);
const size_t text_fixture_len = sizeof(text_fixture)/sizeof(*text_fixture);

extern MunitSuite test_suite_utf8_strlen;
extern MunitSuite test_suite_utf8_strncpy;
extern MunitSuite test_suite_utf8_strnsize;
extern MunitSuite test_suite_utf8to32_strcpy;

static MunitSuite test_suite_f8 = {
    "/f8", NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char **argv)
{
    MunitSuite *suites = calloc(5, sizeof(MunitSuite));
    suites[0] = test_suite_utf8_strlen;
    suites[1] = test_suite_utf8_strncpy;
    suites[2] = test_suite_utf8_strnsize;
    suites[3] = test_suite_utf8to32_strcpy;

    test_suite_f8.suites = suites;

    return munit_suite_main(&test_suite_f8, NULL, argc, argv);
}
