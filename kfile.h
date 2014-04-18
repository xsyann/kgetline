/*
** kfile.h
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Mar 14 12:03:30 2014 xsyann
** Last update Fri Apr 18 22:19:06 2014 xsyann
*/

#ifndef                 __KFILE_H__
#define                 __KFILE_H__


struct file *kopen(const char *filename, int flags, umode_t mode);
void kclose(struct file *f);
ssize_t kread(struct file *file, char __user *buf, size_t count);

#endif                  /* __KFILE_H__ */
