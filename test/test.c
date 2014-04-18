/*
** test.c for kgetline
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Mar 14 10:04:32 2014 xsyann
** Last update Fri Apr 18 22:23:56 2014 xsyann
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include "kfile.h"
#include "kgetline.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yann KOETH");
MODULE_DESCRIPTION("kgetline Test");
MODULE_VERSION("0.1");

static int print_file(const char *filename)
{
        struct file *f;
        char *line = NULL;
        size_t len = 0;
        ssize_t read = 0;

        f = kopen(filename, O_RDONLY, 0);
        if (f == NULL)
                return -1;
        while (((read = kgetline(&line, &len, f)) != -1)) {
                printk(KERN_INFO "%s (%zu char read, buffer size: %zu)\n", line, read, len);
        }
        if (line != NULL)
                kfree(line);
        return 0;
}

static int init_test(void)
{
        printk(KERN_INFO "Load Module\n");
        print_file("test.txt");
        return 0;
}

static void cleanup_test(void)
{
        printk(KERN_INFO "Unload syscall\n");
}

module_init(init_test);
module_exit(cleanup_test);
