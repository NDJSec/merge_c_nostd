#include "../includes/libio.h"

size_t str_len(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void str_cat(char *str, const char *cat_str) {
    if (str == NULL || cat_str == NULL) {
        return;
    }
    while (*str != '\0') {
        str++;
    }
    while ((*str++ = *cat_str++));
}


short int str_cmp(const char *original, const char *cmp) {
    short int index = 0;
    while (original[index] == cmp[index]) {
        if (original[index] == '\0') {
            return original[index] - cmp[index];
        }
        index++;
    }
    return original[index] - cmp[index];
}

void str_cpy(char *dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}