#include "f8.h"
#include "munit.h"

#include "test.h"

static MunitResult test_utf8_strnsize(const MunitParameter params[],
        void *fixture)
{
    (void) params;
    (void) fixture;

    const struct u_pair *f = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        for (size_t j = 0; j < len; j++) {
            size_t size = utf8_strnsize(f[i].utf8, j);
            munit_assert_uint(size, ==, j * (i + 1));
        }
    }

    return MUNIT_OK;
}

MunitSuite test_suite_utf8_strnsize = {
    "/utf8_strnsize",
    (MunitTest[]){
        {
            "/Basic test",
            test_utf8_strnsize,
            NULL,
            NULL, MUNIT_TEST_OPTION_NONE, NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    }, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
