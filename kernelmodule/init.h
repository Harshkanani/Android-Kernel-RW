typedef struct _COPY_MEMORY {
    pid_t pid;
    uintptr_t addr;
    void* buffer;
    size_t size;
} COPY_MEMORY;

enum OPERATIONS {
    READ_MEMORY = 0x101,
    WRITE_MEMORY = 0x102,
};