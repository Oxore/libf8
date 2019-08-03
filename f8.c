#include <stdlib.h>
#include <string.h>

#include "f8.h"

static inline size_t utf8_char_len(unsigned char c)
{
    if (c > 0x00 && c < 0xC0)
        return 1;
    else if (c >= 0xC2 && c < 0xE0)
        return 2;
    else if (c >= 0xE0 && c < 0xF0)
        return 3;
    else if (c >= 0xF0 && c < 0xF5)
        return 4;
    else
        return 0;
}

size_t utf8_strlen(const char *string)
{
    size_t len = 0, keep = 0;
    for (const char *c = string; *c; (keep ? --keep : ++len), ++c)
        if (!keep)
            keep = (keep = utf8_char_len(*c)) ? keep - 1 : keep;
    return len;
}

int32_t *utf8to32_strcpy(int32_t *dest, char *src)
{
    int32_t *dc = dest;
    char *c = src;
    size_t len = 0;
    while (*c) {
        size_t clen = utf8_char_len(*c);
        if (clen == 1) {
            dc[len] = c[0] & 0x7f;
        } else if (clen == 2) {
            dc[len] = ((c[0] & 0x1f) << 6) | ((c[1] & 0x3f) << 0);
        } else if (clen == 3) {
            dc[len] = ((c[0] & 0x0f) << 12) | ((c[1] & 0x3f) << 6)
                | ((c[2] & 0x3f) << 0);
        } else if (clen == 4) {
            dc[len] = ((c[0] & 0x07) << 18) | ((c[1] & 0x3f) << 12)
                | ((c[2] & 0x3f) << 6) | ((c[3] & 0x3f) << 0);
        } else {
            dc[len] = 0;
            return dest;
        }
        c += clen;
        ++len;
    }
    dc[len] = 0;
    return dest;
}

char *utf8_strncpy(char *dest, const char *src, size_t n)
{
    char *d = dest;
    for ( ; *src && n; --n) {
        size_t char_len = utf8_char_len(*src);
        for (size_t i = 0; i < char_len; ++i)
            d[i] = src[i];
        src += char_len;
        d += char_len;
    }
    *d = 0;
    return dest;
}

size_t utf8_strnsize(const char *str, size_t n)
{
    size_t size = 0;
    for ( ; *str && n; --n) {
        size_t char_len = utf8_char_len(*str);
        size += char_len;
        str += char_len;
    }
    return size;
}
