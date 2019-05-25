This is my version of the **[42](https://www.42.us.org/)** cadet project `ft_ls` from the UNIX branch.

# ft_ls
The command `ls` recoded.

### Functions used
* `opendir()` to open a directory
* `readdir()` to read the next file in an open directory
* `closedir()` to close a directory
* `stat()` and `lstat()`, which get most of a file's info
```c
struct stat {
     dev_t           st_dev;           /* ID of device containing file */
     mode_t          st_mode;          /* mode of file */
     nlink_t         st_nlink;         /* number of hard links */
     ino_t           st_ino;           /* file serial number */
     uid_t           st_uid;           /* user ID of the file */
     gid_t           st_gid;           /* group ID of the file */
     dev_t           st_rdev;          /* device ID */
     struct timespec st_atimespec;     /* time of last access */
     struct timespec st_mtimespec;     /* time of last data modification */
     struct timespec st_ctimespec;     /* time of last status change */
     struct timespec st_birthtimespec; /* time of file creation(birth) */
     off_t           st_size;          /* file size, in bytes */
     blkcnt_t        st_blocks;        /* blocks allocated for file */
     blksize_t       st_blksize;       /* optimal blocksize for I/O */
     uint32_t        st_flags;         /* user defined flags for file */
     uint32_t        st_gen;           /* file generation number */
     int32_t         st_lspare;        /* RESERVED: DO NOT USE! */
     int64_t         st_qspare[2];     /* RESERVED: DO NOT USE! */
};
struct timespec {
     time_t         tv_sec;  /* seconds */
     long           tv_nsec; /* nanoseconds */
}
```
* `getpwuid()` to get the name of a file's user
* `getgrgid()` to get the name of a file's group
* `time()` to get the current time
* `ctime()` to turn the date (`time_t`) into a str that formats the date for human use, rather than machine use. (Example: `Wed Apr 17 12:55:20 2019`)
* `major()` and `minor()`—which are technically macros, but function-like ones—to pull the major and minor device number out of the device ID.
* `readlink()` to get the link of a file that is a link
* `listxattr()` to get the extended attributes of a file that has them
* `getxattr()` to get the size of a specific extended attribute
* `acl_get_link_np()` to get ACL (access control list) for a file
