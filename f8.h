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
size_t      utf8_strlen(char *str);

/*
 * Converts UTF8 to UTF32.
 *
 * */
wchar_t    *utf8to32_strcpy(wchar_t *dest, char *src);

/*
 * Differs from standard strcpy by ensuring null-terminated dest string.
 *
 * */
char       *utf8_strncpy(char *dest, char *src, size_t n);

/*
 * Returns size of first n utf8 characters of str in bytes.
 *
 * Terminating null character does not counts.
 *
 * */
size_t      utf8_strsizen(char *str, size_t n);
