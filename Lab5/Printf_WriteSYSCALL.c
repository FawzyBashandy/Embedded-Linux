#include <stdio.h>
#include <string.h>

typedef long ssize_t;

void myPrintf(char *string);
ssize_t myWriteSysCall(int fd, const void *buf, size_t count);
int main()
{
    myPrintf("Hello\nI'm FooZ\n");
}
void myPrintf(char *string)
{
    int fd = 1;
    const void *buf = string;
    size_t count = strlen(buf);

    myWriteSysCall(fd, buf, count);
}

ssize_t myWriteSysCall(int fd, const void *buf, size_t count)
{
    ssize_t returnval = -1;
    __asm__ volatile (
        "movq $1, %%rax;"    // syscall number for write = 1
        "movq %1, %%rdi;"    // fd
        "movq %2, %%rsi;"    // buf
        "movq %3, %%rdx;"    // count
        "syscall;"           // SW INT syscall
        "movq %%rax, %0;"    // store return value
        : "=r"(returnval)
        : "r"((long)fd), "r"(buf), "r"(count)
        : "%rax", "%rdi", "%rsi", "%rdx", "rcx", "r11", "memory"
    );
    return returnval;
}
