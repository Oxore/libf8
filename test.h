struct u_pair {
    char    *utf8;
    int32_t *utf32;
    size_t   len;
    size_t   size_utf8;
    size_t   size_utf32;
};

extern const struct u_pair text_fixture[];
extern const size_t text_fixture_size;
extern const size_t text_fixture_len;
