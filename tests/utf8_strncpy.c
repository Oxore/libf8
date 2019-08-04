#include "f8.h"
#include "munit.h"

#include "test.h"

struct fixture {
    char *str;
    char *str_copy;
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
        f[i].len = utf8_strlen(tf[i].utf8);
        f[i].size = (f[i].len * (i + 1) + 1) * sizeof(char);
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

static MunitResult test_n_is_size_max(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;
    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        char *dest = utf8_strncpy(f[i].str, tf[i].utf8, SIZE_MAX);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal(f[i].size - 1 * sizeof(char), f[i].str,
                tf[i].utf8);
        munit_assert_char(f[i].str[f[i].size - 1], ==, 0);
    }

    return MUNIT_OK;
}

static MunitResult test_n_is_zero(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;
    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        char *dest = utf8_strncpy(f[i].str, tf[i].utf8, 0);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_char(f[i].str[0], ==, 0);
    }

    return MUNIT_OK;
}

static MunitResult test_n_is_one(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;
    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        char *dest = utf8_strncpy(f[i].str, tf[i].utf8, 1);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal((i + 1) * sizeof(char), f[i].str, tf[i].utf8);
        munit_assert_char(f[i].str[i + 1], ==, 0);
    }

    return MUNIT_OK;
}

static MunitResult test_exact_values(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;
    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        char *dest = utf8_strncpy(f[i].str, tf[i].utf8, f[i].len);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal(f[i].size - 1 * sizeof(char), f[i].str,
                tf[i].utf8);
        munit_assert_char(f[i].str[f[i].size - 1], ==, 0);
    }
    return MUNIT_OK;
}

static MunitResult test_dest_is_null(const MunitParameter params[],
        void *fixture)
{
    (void) params;

    struct fixture *f = fixture;
    const struct u_pair *tf = text_fixture;

    for (size_t i = 0; i < text_fixture_len; i++) {
        char *dest = utf8_strncpy(NULL, tf[i].utf8, f[i].len);

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
        char *dest = utf8_strncpy(f[i].str, NULL, f[i].len);

        munit_assert_ptr(dest, ==, f[i].str);
        munit_assert_memory_equal(f[i].size, f[i].str, f[i].str_copy);
    }
    return MUNIT_OK;
}

MunitSuite test_suite_utf8_strncpy = {
    "/utf8_strncpy",
    (MunitTest[]){
        {
            "/Number of characters `n` is SIZE_MAX",
            test_n_is_size_max,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
        {
            "/Number of characters `n` is 0",
            test_n_is_zero,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
        {
            "/Number of characters `n` is 1",
            test_n_is_one,
            setup,
            tear_down,
            MUNIT_TEST_OPTION_NONE, NULL
        },
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
