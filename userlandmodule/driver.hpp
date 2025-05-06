#include <sys/fcntl.h>
#include <sys/ioctl.h>

#define DRIVER_PATH "/dev/Harsh"

class kernel_driver {
private:
    int fd;
    pid_t pid;

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

public:
    //Constructor - Open driver file
    kernel_driver() {
        fd = open(DRIVER_PATH, O_RDWR);
        if (fd == -1) {
            printf("Driver not found\n");
        }
    }

    //Destructor - close driver file
    ~kernel_driver() {
        if (fd > 0)
            close(fd);
    }

    void initialize(pid_t pid) {
        this->pid = pid;
    }


    bool Read(uintptr_t addr, void *buffer, size_t size) {
        COPY_MEMORY cm;

        cm.pid = this->pid;
        cm.addr = addr;
        cm.buffer = buffer;
        cm.size = size;

        if (ioctl(fd, READ_MEMORY, &cm) != 0) {
            return false;
        }
        return true;
    }

    bool Write(uintptr_t addr, void *buffer, size_t size) {
        COPY_MEMORY cm;

        cm.pid = this->pid;
        cm.addr = addr;
        cm.buffer = buffer;
        cm.size = size;

        if (ioctl(fd, WRITE_MEMORY, &cm) != 0) {
            return false;
        }
        return true;
    }

    template <typename T>
    T Read(uintptr_t addr) {
        T res;
        if (this->Read(addr, &res, sizeof(T)))
            return res;
        return {};
    }

    template <typename T>
    bool Write(uintptr_t addr,T value) {
        return this->Write(addr, &value, sizeof(T));
    }
};

static kernel_driver *driver = new kernel_driver();
