
# Android-Kernel-RW

**Android-Kernel-RW** is a custom Android kernel module and userland interface that enables **stealthy, low-level read/write access** to memory of any user-space process, operating entirely from kernel space. Designed for **rooted environments**, it allows memory read and write operations with minimal footprint and no interaction with userland APIs.

---

## Features

- **Stealth Memory Access** – Read and Write operations that are invisible to userland process
- **Process-Specific Targeting** – Target any process by Process IDentifier
- **Secure IOCTL-based Interface** – Kernel module communicates with userland securely

---

## 🔧 Build Instructions

### 1. Compile Kernel Module (Against Your Kernel Source)

```bash
cd kernelmodule
make -C /path/to/kernel/source M=$(pwd) modules
```

> Must be compiled using the **same kernel config and toolchain** as your device. The module is kernel-version specific.

### 2. Load Kernel Module

```bash
insmod module.ko
```

Check logs:
```bash
dmesg
```

### 3. Unload Module

```bash
rmmod module.ko
```

---

## Using From Userland

1. **Include** `driver.hpp` in your project:
```cpp
#include "driver.hpp"
```

2. **Run Example**:
See `userlandmodule/main.cpp` for a full demo of how to read/write memory from your userland program.

> No need to implement ioctl calls – just use `Read<T>()`, `Write<T>()`.

---

## Notes

- **Kernel-Specific** – Must be compiled for individual kernel seperately. Not portable.
- **Root Required** – Requires a rooted device to load kernel modules.
- **No Auto-Start** – Must load the kernel driver after reboot.

---

## Disclaimer

> **Note:** This project is provided **for educational and research purposes only**.