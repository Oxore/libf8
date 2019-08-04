#include "f8.h"
#include "munit.h"

#include "test.h"

static MunitResult test_utf8_strlen(const MunitParameter params[],
        void *fixture)
{
    (void) params;
    (void) fixture;
    const struct u_pair *f = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++)
        munit_assert_ulong(
                utf8_strlen(f[i].utf8) * (i + 1),
                ==,
                strlen(f[i].utf8));

    return MUNIT_OK;
}

MunitSuite test_suite_utf8_strlen = {
    "/utf8_strlen",
    (MunitTest[]){
        {
            "/Basic test",
            test_utf8_strlen,
            NULL,
            NULL, MUNIT_TEST_OPTION_NONE, NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    }, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

