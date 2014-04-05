/*
** kfile.h
** 
** Made by xsyann
** Contact <contact@xsyann.com>
** 
** Started on  Fri Mar 14 12:03:30 2014 xsyann
** Last update Sat Apr  5 14:46:59 2014 xsyann
*/

#ifndef		__KFILE_H__
#define		__KFILE_H__

typedef struct file kfile;

kfile		*kopen(const char *filename, int flags, umode_t mode);
void		kclose(kfile *f);
ssize_t		kread(kfile *file, char __user *buf, size_t count);

#endif		/* __KFILE_H__ */
