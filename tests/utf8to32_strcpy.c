#include "f8.h"
#include "munit.h"

#include "test.h"

static MunitResult test_utf8to32_strcpy(const MunitParameter params[],
        void *fixture)
{
    (void) params;
    (void) fixture;

    const struct u_pair *f = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        size_t size = (len + 1) * sizeof(int32_t);
        int32_t *str = malloc(size);
        memset(str, 0xff, size);

        int32_t *dest = utf8to32_strcpy(str, f[i].utf8);
        munit_assert_ptr(dest, ==, str);
        munit_assert_uint(memcmp(str, f[i].utf32, len * sizeof(int32_t)),
                ==, 0);
        free(str);
    }

    return MUNIT_OK;
}

MunitSuite test_suite_utf8to32_strcpy = {
    "/utf8to32_strcpy",
    (MunitTest[]){
        {
            "/Basic test",
            test_utf8to32_strcpy,
            NULL,
            NULL, MUNIT_TEST_OPTION_NONE, NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    }, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
