/*
** kfile.c
** 
** Made by xsyann
** Contact <contact@xsyann.com>
** 
** Started on  Fri Mar 14 12:00:51 2014 xsyann
** Last update Sat Apr  5 13:41:25 2014 xsyann
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include "kfile.h"

kfile *kopen(const char *filename, int flags, umode_t mode)
{
  struct file *f = NULL;
  mm_segment_t oldfs;

  oldfs = get_fs();
  set_fs(get_ds());
  f = filp_open(filename, flags, mode);
  set_fs(oldfs);
  if(IS_ERR(f) || (f == NULL))
      return NULL;
  return f;
}

void kclose(kfile *f)
{
    filp_close(f, NULL);
}

ssize_t kread(struct file *file, char __user *buf, size_t count)
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_read(file, buf, count, &file->f_pos);

    set_fs(oldfs);
    return ret;
}
