#include "libsys.h"

#ifndef LIBIO_H
#define LIBIO_H

size_t str_len(const char *str);
void str_cat(char *str, const char *cat_str);
short int str_cmp(const char *original, const char *cmp);
short int file_ext(const char *path, const char *ext);
void str_cpy(char *dest, const char* src);

#endif

