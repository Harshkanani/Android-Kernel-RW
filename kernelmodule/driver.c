#include <linux/module.h>
#include <linux/tty.h>
#include <linux/miscdevice.h>

#include "init.h"
#include "memorytranslation.h"

#define DRIVER_NAME "Harsh"

int dispatch_open(struct inode *node, struct file *file)
{
    return 0;
}

int dispatch_close(struct inode *node, struct file *file)
{
    return 0;
}

long dispatch_ioctl(struct file* const file, unsigned int const cmd, unsigned long const arg)
{
    static COPY_MEMORY cm;

    switch (cmd) {
        case READ_MEMORY:
            {
                if (copy_from_user(&cm, (void __user*)arg, sizeof(cm)) != 0) {
                    return -1;
                }
                if (read_memory(cm.pid, cm.addr, cm.buffer, cm.size) == false) {
                    return -1;
                }
            }
            break;
        case WRITE_MEMORY:
            {
                if (copy_from_user(&cm, (void __user*)arg, sizeof(cm)) != 0) {
                    return -1;
                }
                if (write_memory(cm.pid, cm.addr, cm.buffer, cm.size) == false) {
                    return -1;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}

struct file_operations dispatch_functions = {
    .owner   = THIS_MODULE,
    .open    = dispatch_open,
    .release = dispatch_close,
    .unlocked_ioctl = dispatch_ioctl,
};

struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DRIVER_NAME,
	.fops = &dispatch_functions,
};

int __init driver_load(void)
{
	int ret = misc_register(&misc);
	return ret;
}

void __exit driver_unload(void)
{
	misc_deregister(&misc);
}

module_init(driver_load);
module_exit(driver_unload);

MODULE_DESCRIPTION("Android Linux Kernel");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harsh");