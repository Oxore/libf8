#include "f8.h"
#include "munit.h"

#include "test.h"

struct fixture {
    int32_t *str;
    int32_t *str_copy;
    size_t len;
    size_t size;
};

static void *setup(const MunitParameter params[], void *user_data)
{
    (void) params;
    (void) user_data;

    const struct u_pair *tf = text_fixture;
    struct fixture *f = malloc((text_fixture_len + 1) * sizeof(struct fixture));
    for (size_t i = 0; i < text_fixture_len; i++) {
        f[i].len = tf[i].len;
        f[i].size = tf[i].size_utf32;
        f[i].str = malloc(f[i].size);
        f[i].str_copy = malloc(f[i].size);
        memset(f[i].str, 0xff, f[i].size);
        memset(f[i].str_copy, 0xff, f[i].size);
    }
    return f;
}

static void tear_down(void *fixture)
{
    struct fixture *f = fixture;
    for (size_t i = 0; i < text_fixture_len; i++) {
        free(f[i].str);
        free(f[i].str_copy);
    }
    free(f);
}

static MunitResult test_exact_values(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    const struct u_pair *tf = text_fixture;
    struct fixture *f = fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        int32_t *dest = utf8to32_strcpy(f[i].str, tf[i].utf8);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal(f[i].size, f[i].str, tf[i].utf32);
    }

    return MUNIT_OK;
}

static MunitResult test_dest_is_null(const MunitParameter params[],
        void *fixture)
{
    (void) params;
    (void) fixture;

    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        int32_t *dest = utf8to32_strcpy(NULL, tf[i].utf8);

        munit_assert_ptr(dest, ==, NULL);
    }

    return MUNIT_OK;
}

static MunitResult test_src_is_null(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        int32_t *dest = utf8to32_strcpy(f[i].str, NULL);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal(f[i].size, f[i].str, f[i].str_copy);
    }

    return MUNIT_OK;
}

MunitSuite test_suite_utf8to32_strcpy = {
    "/utf8to32_strcpy",
    (MunitTest[]){
        {
            "/Exact values",
            test_exact_values,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
        {
            "/Pointer `dest` is NULL",
            test_dest_is_null,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
        {
            "/Pointer `src` is NULL",
            test_src_is_null,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    }, NULL, 1, MUNIT_SUITE_OPTION_NONE
};
