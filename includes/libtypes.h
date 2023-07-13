#ifndef LIBTYPES_H
#define LIBTYPES_H

#define NULL ((void *)0)

#define DT_UNKNOWN  0
#define DT_FIFO     1
#define DT_CHR      2
#define DT_DIR      4
#define DT_BLK      6
#define DT_REG      8
#define DT_LNK      10
#define DT_SOCK     12
#define DT_WHT      14

typedef struct linux_dirent64 {
    unsigned long  d_ino;    /* Inode number */
    unsigned long  d_off;    /* Offset to next linux_dirent64 */
    unsigned short d_reclen; /* Length of this linux_dirent64 */
    unsigned char  d_type;   /* File type */
    char           d_name[]; /* Filename (null-terminated) */
} linux_dirent64;

typedef unsigned long int size_t;
typedef long int ssize_t;
typedef unsigned short umode_t;

#endif