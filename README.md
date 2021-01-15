Minimal POSIX compliant `sleep`.

# Results
### Only 3 syscalls per execution
```
$ strace ./sleep 1
execve("./sleep", ["./sleep", "1"], 0x7ffc998d09a8 /* 40 vars */) = 0
nanosleep({tv_sec=1, tv_nsec=0}, NULL)  = 0
exit(0)                                 = ?
+++ exited with 0 +++
```

Compared to an empty C program
```
$ strace ./a.out
execve("./a.out", ["./a.out"], 0x7ffe2f0aa150 /* 40 vars */) = 0
brk(NULL)                               = 0x561007006000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffeacd2dff0) = -1 EINVAL (Invalid argument)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=116514, ...}) = 0
mmap(NULL, 116514, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f74729a9000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\202\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\207\360\21\247\344\314?\306\nT\320\323\335i\16t"..., 68, 880) = 68
fstat(3, {st_mode=S_IFREG|0755, st_size=2159552, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f74729a7000
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 1868448, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f74727de000
mmap(0x7f7472804000, 1363968, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f7472804000
mmap(0x7f7472951000, 311296, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x173000) = 0x7f7472951000
mmap(0x7f747299d000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1be000) = 0x7f747299d000
mmap(0x7f74729a3000, 12960, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f74729a3000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f74727dc000
arch_prctl(ARCH_SET_FS, 0x7f74729a8540) = 0
mprotect(0x7f747299d000, 12288, PROT_READ) = 0
mprotect(0x5610050fc000, 4096, PROT_READ) = 0
mprotect(0x7f74729f2000, 4096, PROT_READ) = 0
munmap(0x7f74729a9000, 116514)          = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

### Small binary
```
$ du -b ./sleep /bin/sleep
1024    ./sleep
39048   /bin/sleep             # default arch sleep binary
```

The above measurement is the apparent size, as modern file systems allocate memory in blocks of 4096 bytes, further reducing the size won't actually change the disk usage reported below.

```
$ du -B1 ./sleep /bin/sleep
4096    ./sleep
40960   /bin/sleep             # default arch sleep binary
```

# Compilation
Compilation dependencies:
* `gcc`
* `make`

```
make sleep
```

# Usage
```
./sleep SECONDS
```
where `SECONDS` is a non negative number (e.g. `15`, `12.003`)
