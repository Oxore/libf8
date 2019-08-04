#include "f8.h"
#include "munit.h"

#include "test.h"

static MunitResult test_utf8_strncpy(const MunitParameter params[],
        void *fixture)
{
    (void) params;
    (void) fixture;

    const struct u_pair *f = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        size_t size = (len * (i + 1) + 1) * sizeof(char);
        char *str = malloc(size);
        memset(str, 0xff, size);

        char *dest = utf8_strncpy(str, f[i].utf8, 100);

        munit_assert_ptr(dest, ==, str);
        munit_assert_uint(memcmp(str, f[i].utf8, size - 1 * sizeof(char)),
                ==,
                0);
        munit_assert_uchar(*(str + size - 1 * sizeof(char)), ==, 0);

        free(str);
    }

    for (size_t i = 0; i < text_fixture_len; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        for (size_t j = 0; j < len; j++) {
            size_t size = (j * (i + 1) + 1) * sizeof(char);
            char *str = malloc(size);
            memset(str, 0xff, size);

            char *dest = utf8_strncpy(str, f[i].utf8, j);

            munit_assert_ptr(dest, ==, str);
            munit_assert_uint(
                    memcmp(str, f[i].utf8, size - 1 * sizeof(char)),
                    ==,
                    0);
            munit_assert_uchar(*(str + size - 1 * sizeof(char)), ==, 0);

            free(str);
        }
    }

    return MUNIT_OK;
}

MunitSuite test_suite_utf8_strncpy = {
    "/utf8_strncpy",
    (MunitTest[]){
        {
            "/Basic test",
            test_utf8_strncpy,
            NULL,
            NULL, MUNIT_TEST_OPTION_NONE, NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    }, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
