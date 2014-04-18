/*
** kgetline.c
**
** Made by xsyann
** Contact <contact@xsyann.com>
**
** Started on  Fri Mar 14 21:29:24 2014 xsyann
** Last update Fri Apr 18 22:22:10 2014 xsyann
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/fs.h>
#include "kfile.h"
#include "kgetline.h"

int alloc_line(char **lineptr, size_t *n)
{
        if (!lineptr || !n)
                return -1;
        if (!*lineptr) {
                *n = MIN_CHUNK;
                *lineptr = kmalloc(*n, GFP_KERNEL);
                if (!*lineptr)
                        return -1;
        }
        memset(*lineptr, 0, *n);
        return 0;
}

int realloc_line(char **lineptr, size_t *n)
{
        void *tmp;

        if (*n > MIN_CHUNK)
                *n *= 2;
        else
                *n += MIN_CHUNK;
        tmp = krealloc(*lineptr, *n, GFP_KERNEL);
        if (tmp == NULL)
                return -1;
        *lineptr = tmp;
        return 0;
}

int concat_buffer(char **lineptr, size_t *n, const char *buf,
                              char *save, char terminator)
{
        uint i;
        uint j;

        i = strlen(*lineptr);
        j = 0;
        while (buf[j]) {
                if (i == *n)
                        if (realloc_line(lineptr, n) == -1)
                                return -1;
                if (buf[j] == terminator || i == *n) {
                        (*lineptr)[i] = '\0';
                        if (buf[j] == terminator)
                                ++j;
                        save = strcpy(save, buf + j);
                        return i;
                }
                (*lineptr)[i++] = buf[j++];
        }
        save[0] = '\0';
        (*lineptr)[i] = '\0';
        return -1;
}

ssize_t kgetstr(char **lineptr, size_t *n, struct file *f, char terminator)
{
        static char save[BUFFER_SIZE];
        char buf[BUFFER_SIZE];
        ssize_t linelen;
        ssize_t readlen;

        if (alloc_line(lineptr, n) == -1)
                return -1;
        /* Saved buffer */
        if ((linelen = concat_buffer(lineptr, n, save, save, terminator)) != -1)
                return linelen;
        while ((readlen = kread(f, buf, BUFFER_SIZE - 1)) > 0) {
                buf[readlen] = '\0';
                if ((linelen = concat_buffer(lineptr, n, buf, save, terminator)) != -1)
                        return linelen;
        }
        /* Partial line */
        if (*lineptr && (*lineptr)[0] != '\0')
                return strlen(*lineptr);
        return -1;
}

ssize_t kgetline(char **lineptr, size_t *n, struct file *f)
{
        return kgetstr(lineptr, n, f, '\n');
}
