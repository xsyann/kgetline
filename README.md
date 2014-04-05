kgetline
========

Linux kernel version of libc getline()

###Synopsis
    ssize_t kgetline(char **lineptr, size_t *n, kfile *stream);

###Description
**kgetline()** reads an entire line from `stream`, storing the address of the buffer containing the text into `*lineptr`. The buffer is null-terminated and **do not** includes the newline character.

If `*lineptr` is NULL, the **kgetline()** will allocate a buffer for storing the line, which should be freed by the user program (**kfree()**). (In this case, the value `*n` is ignored.)

Alternatively, before calling **kgetline()**, `*lineptr` can contain a pointer to a kmalloc()-allocated buffer `*n` bytes in size. If the buffer is not large enough to hold the line, **kgetline()** resizes it with **krealloc()**, updating `*lineptr` and `*n` as necessary.

In  either case, on a successful call, `*lineptr` and `*n` will be updated to reflect the buffer address and allocated size respectively.

###Return value
On success, **kgetline() return the number of characters read, not including the newline character and the terminating null byte.

**kgetline()** return -1 on failure to read a line (including end-of-file condition).

------------------------------

###File Handling

    typedef struct file kfile;

    kfile           *kopen(const char *filename, int flags, umode_t mode);
    void            kclose(kfile *f);
    ssize_t         kread(kfile *file, char __user *buf, size_t count);

Are convenient functions for file handling.
