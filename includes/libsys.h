#ifndef LIBSYS_H
#define LIBSYS_H

#include "libtypes.h"

void sys_write(const char *msg);
void sys_write_len(const char *msg, size_t msg_len);
void sys_exit(int error_code);
int sys_mkdir(const char *pathname);
void sys_read_dir(const char *path, int type, char **entries, short int max_entries);

#endif