#include "../includes/libsys.h"
#include "../includes/libio.h"

void sys_write(const char *msg) {
    size_t msg_len = str_len(msg);
    asm volatile (
        "mov $1, %%rax\n"
        "mov $1, %%rdi\n"
        "mov %[msg], %%rsi\n"
        "mov %[msg_len], %%rdx\n"
        "syscall"
        : 
        : [msg] "m" (msg), [msg_len] "r" (msg_len)
        : "%rax", "%rdx", "%rsi", "%rdi", "memory"
    );
}

void sys_write_len(const char *msg, size_t msg_len) {
    asm volatile (
        "mov $1, %%rax\n"
        "mov $1, %%rdi\n"
        "mov %[msg], %%rsi\n"
        "mov %[msg_len], %%rdx\n"
        "syscall"
        : 
        : [msg] "m" (msg), [msg_len] "m" (msg_len)
        : "%rax", "%rdx", "%rsi", "%rdi", "memory"
    );
}

void sys_exit(int error_code) {
    asm volatile (
        "mov $60, %%rax\n"
        "mov %[error_code], %%rdi\n"
        "syscall"
        :
        : [error_code] "m" (error_code)
        : "%rdi", "memory"
    );
}

int sys_mkdir(const char *pathname) {
    int errno_val = 0;
    asm volatile (
        "mov $0x53, %%rax\n"
        "mov %[pathname], %%rdi\n"
        "mov $0x1ED, %%rsi\n"
        "syscall\n"
        "mov %%eax, %[errno_val]"
        : [errno_val] "=r" (errno_val)
        : [pathname] "m" (pathname)
        : "%rax", "%rdi", "%rdi", "memory"
    );
    return errno_val;
}

void sys_read_dir(const char *path, int type, char **entries, short int max_entries) {
    unsigned int fd;
    long nread;
    char buf[8192];
    short int count = 0;

    asm volatile (
        "mov $2, %%rax\n" // SYS_open
        "mov %[path], %%rdi\n" // File path
        "mov $0, %%rsi\n" // Flags: O_RDONLY
        "mov $0, %%rdx\n"
        "syscall\n"
        "mov %%eax, %[fd]\n" //Store file descriptor

        "xor %%rax, %%rax\n"
        "mov $0xd9, %%rax\n" // SYS_getdents64
        "mov %[fd], %%edi\n" // File descriptor
        "lea %[buf], %%rsi\n"
        "mov $8192, %%rdx\n"
        "syscall\n"
        "mov %%rax, %[nread]\n" // Store number of bytes read

        : [fd] "=r" (fd), [nread] "=r" (nread)
        : [path] "m" (path), [buf] "m" (buf)
        : "%rax", "%rdi", "%rsi", "%rdx", "memory"
    );

    if (nread == -1) {
        sys_write("Error reading directory");
        return;
    } 
    char *ptr = buf;
    while (ptr < buf + nread && count < max_entries) {
        linux_dirent64 *entry = (struct linux_dirent64 *)ptr;
        char *name = entry->d_name;
        unsigned char d_type = entry->d_type;
        short int dir_check_cur = str_cmp(name, ".");
        short int dir_check_prev = str_cmp(name, "..");


        if (d_type == DT_DIR && type == DT_DIR && (dir_check_cur && dir_check_prev)) {  // Filter only directory entries
            entries[count] = name;
            count++;
        } else if (d_type == DT_REG && type == DT_REG) {
            entries[count] = name;
            count++;
            str_cat(name, "\n");
            sys_write(name);
        }
        
        ptr += entry->d_reclen;
    }

    asm volatile (
        "mov $3, %%rax\n"           // SYS_close
        "mov %[fd], %%rdi\n"        // File descriptor
        "syscall\n"
        :
        : [fd] "m" (fd)
        : "%rax", "%rdi", "memory"
    );
}

