#include "munit.h"

#include "f8.h"

struct u_pair {
    char    *utf8;
    wchar_t *utf32;
};

struct u_pair text_fixture[] = {
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


static void *test_utf8_strlen_setup(
        const MunitParameter    params[],
        void                   *user_data)
{
    (void) params;

    return user_data;
}

static MunitResult test_utf8_strlen(
        const MunitParameter    params[],
        void                   *fixture)
{
    (void) params;
    struct u_pair *f = fixture;

    for (int i = 0; i < 4; i++)
        munit_assert_ulong(
                utf8_strlen(f[i].utf8) * (i + 1),
                ==,
                strlen(f[i].utf8));

    return MUNIT_OK;
}

static void *test_utf8to32_strcpy_setup(
        const MunitParameter    params[],
        void                   *user_data)
{
    (void) params;

    return user_data;
}

static MunitResult test_utf8to32_strcpy(
        const MunitParameter    params[],
        void                   *fixture)
{
    (void) params;

    struct u_pair  *f = fixture;

    for (int i = 0; i < 4; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        wchar_t *str = malloc((len + 1) * sizeof(wchar_t));
        wchar_t *dest = utf8to32_strcpy(str, f[i].utf8);
        munit_assert_ptr(dest, ==, str);
        munit_assert_uint(memcmp(str, f[i].utf32, len), ==, 0);
        free(str);
    }

    return MUNIT_OK;
}

static void *test_utf8_strncpy_setup(
        const MunitParameter    params[],
        void                   *user_data)
{
    (void) params;

    return user_data;
}

static MunitResult test_utf8_strncpy(
        const MunitParameter    params[],
        void                   *fixture)
{
    (void) params;

    struct u_pair  *f = fixture;

    for (int i = 0; i < 4; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        char *str = malloc((len + 1) * sizeof(char));
        char *dest = utf8_strncpy(str, f[i].utf8, 100);
        munit_assert_ptr(dest, ==, str);
        munit_assert_uint(memcmp(str, f[i].utf8, len), ==, 0);
        free(str);
    }

    for (int i = 0; i < 4; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        for (size_t j = 0; j < len; j++) {
#define SIZE j * (i + 1)
            char *str = malloc((len + 1) * sizeof(char));
            char *dest = utf8_strncpy(str, f[i].utf8, j);
            munit_assert_ptr(dest, ==, str);
            munit_assert_uint(memcmp(str, f[i].utf8, SIZE), ==, 0);
            munit_assert_uchar(*(str + SIZE), ==, 0);
            free(str);
        }
    }

    return MUNIT_OK;
}

static void *test_utf8_strsizen_setup(
        const MunitParameter    params[],
        void                   *user_data)
{
    (void) params;

    return user_data;
}

static MunitResult test_utf8_strsizen(
        const MunitParameter    params[],
        void                   *fixture)
{
    (void) params;

    struct u_pair  *f = fixture;

    for (int i = 0; i < 4; i++) {
        size_t len = utf8_strlen(f[i].utf8);
        for (size_t j = 0; j < len; j++) {
            size_t size = utf8_strsizen(f[i].utf8, j);
            munit_assert_uint(size, ==, j * (i + 1));
        }
    }

    return MUNIT_OK;
}

static const MunitSuite test_suite = {
    "unit",
    (MunitTest[]){
        {
            "/unicode/utf8_strlen",
            test_utf8_strlen,
            test_utf8_strlen_setup,
            NULL,
            MUNIT_TEST_OPTION_NONE,
            NULL
        },
        {
            "/unicode/utf8to32_strcpy",
            test_utf8to32_strcpy,
            test_utf8to32_strcpy_setup,
            NULL,
            MUNIT_TEST_OPTION_NONE,
            NULL
        },
        {
            "/unicode/utf8_strncpy",
            test_utf8_strncpy,
            test_utf8_strncpy_setup,
            NULL,
            MUNIT_TEST_OPTION_NONE,
            NULL
        },
        {
            "/unicode/utf8_strsizen",
            test_utf8_strsizen,
            test_utf8_strsizen_setup,
            NULL,
            MUNIT_TEST_OPTION_NONE,
            NULL
        },
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
    },
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char **argv)
{
    return munit_suite_main(&test_suite, text_fixture, argc, argv);
}
