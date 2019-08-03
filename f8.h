/*
 * f8.h
 *
 * libf8 - library with some helper unicode functions.
 *
 * */

#include <stddef.h>
#include <stdint.h>

/*
 * Returns number of characters in str.
 *
 * Terminating null character is not counted.
 *
 * */
size_t utf8_strlen(const char *str);

/*
 * Converts UTF8 to UTF32.
 *
 * Writes at most `n` UTF32 characters null terminated string to the location
 * pointed by `dest` which size is `destsz` bytes.
 *
 * The destination UTF32 string is always null terminated, even if all `n` or
 * less characters of the source UTF8 string does not fit into `destsz` bytes.
 *
 * Returns `dest`.
 *
 * */
int32_t *utf8to32_strncpy_s(int32_t *dest, size_t destsz, const char *src,
        size_t n);

/*
 * Converts UTF8 to UTF32.
 *
 * Writes null terminated UTF32 string to the location pointed by `dest` which
 * size is `destsz` bytes.
 *
 * The destination UTF32 string is always null terminated, even if all
 * characters of the source UTF8 string does not fit into `destsz` bytes.
 *
 * Returns dest.
 *
 * */
int32_t *utf8to32_strcpy_s(int32_t *dest, size_t destsz, const char *src);

/*
 * Converts UTF8 to UTF32.
 *
 * Writes at most `n` UTF32 characters null terminated string to the location
 * pointed by `dest`.
 *
 * The destination UTF32 string is always null terminated. If the source UTF8
 * string pointed by `src` has more than `n` bytes, then `n` bytes of the
 * destination UTF32 string will be written to location pointed by `dest` plus
 * null terminator character.
 *
 * BE CAREFUL: location pointed by `dest` should be able to hold at least (`n`
 * + 1) * sizeof(*dest) bytes so null character can fit into it.
 *
 * Returns dest.
 *
 * */
int32_t *utf8to32_strncpy(int32_t *dest, const char *src, size_t n);

/*
 * Converts UTF8 to UTF32.
 *
 * Writes null terminated UTF32 string to the location pointed by `dest`.
 *
 * Returns dest.
 *
 * */
int32_t *utf8to32_strcpy(int32_t *dest, const char *src);

/*
 * Differs from standard strcpy by ensuring null-terminated dest string.
 * dest array must have at least (n + 1) * sizeof(char) allocated bytes.
 *
 * */
char *utf8_strncpy(char *dest, const char *src, size_t n);

/*
 * Returns size of first n utf8 characters of str in bytes.
 *
 * Terminating null character is not counted.
 *
 * */
size_t utf8_strnsize(const char *str, size_t n);
