/*
 * f8.h
 *
 * libf8 - library with some helper unicode functions.
 *
 * */

#include <wchar.h>

/*
 * Returns number of characters in str.
 *
 * Terminating null character does not counts.
 *
 * */
size_t      utf8_strlen(const char *str);

/*
 * Converts UTF8 to UTF32.
 *
 * */
wchar_t    *utf8to32_strcpy(wchar_t *dest, const char *src);

/*
 * Differs from standard strcpy by ensuring null-terminated dest string.
 * dest array must have at least (n + 1) * sizeof(char) allocated bytes.
 *
 * */
char       *utf8_strncpy(char *dest, const char *src, size_t n);

/*
 * Returns size of first n utf8 characters of str in bytes.
 *
 * Terminating null character does not counts.
 *
 * */
size_t      utf8_strnsize(const char *str, size_t n);
