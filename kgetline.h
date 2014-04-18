/*
** kgetline.h
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Mar 14 21:27:27 2014 xsyann
** Last update Fri Apr 18 22:20:12 2014 xsyann
*/

#ifndef                 __KGETLINE_H__
#define                 __KGETLINE_H__

#define MIN_CHUNK       64
#define BUFFER_SIZE     128

ssize_t kgetline(char **lineptr, size_t *n, struct file *f);

#endif                  /* __KGETLINE_H__ */
