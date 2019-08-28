# GDB 常用命令

1. 设置断点 
`b mian` 从main函数开始运行

2. 开始运行代码
`r`

3. `next`
简记为 n，单步跟踪程序，当遇到函数调用时，也不进入此函数体；此命令同 step 的主要区别是，step 遇到用户自定义的函数，将步进到函数中去运行，而 next 则直接调用函数，不会进入到函数体内。

4. `step`
简记为 s ，单步跟踪程序，当遇到函数调用时，则进入此函数体（一般只进入用户自定义函数）。

5. 显示变量的值
`p + <变量名>`

# arrays
1. `void *memcpy(void* dst, const void* src, size_t n)`

- 将字符串src中的n个字符拷贝到dst中，并返回s

2. `void *memcmp(const void* ca, const void* cb, size_t n)`

- 将ca的前n个字符与cb比较
ca < cb => <0
ca = cb => 0
ca > cb => >0

3. `size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *stream)`
- fwrite函数从ptr指向的数组中读取nobj个长度为size的对象，并输出到流stream中。它返回输出对象的数目。如果发生错误，返回值会小于nobj的值
                           
4. `size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream)`
- fread函数从流stream中读取最多nobj个长度为size的对象，并保存到ptr指向的数组中。它返回输出对象的数目，此返回值可能小于nobj。必须通过函数feof和ferror获得结果执行状态

# strings

1. `long int strtol (const char* str, char** endptr, int base)`

- strtol() 函数用来将字符串转换为长整型数(long)。 
- str 为要转换的字符串
- endstr 为第一个不能转换的字符的指针
- base 为字符串 
- str 所采用的进制
- 返回值：返回转换后的长整型数
- 如果不能转换或者 str 为空字符串，那么返回 0(0L)；如果转换得到的值超出 long int 所能表示的范围，函数将返回 LONG_MAX 或 LONG_MIN（在 limits.h 头文件中定义），并将 errno 的值设置为 ERANGE。

# sys_programming

1. `int open(char *name, int flags, int perms)`

- name: 一个包含文件名的字符串
- flags: int宏，说明以何种方式打开文件
    - O_RDONLY: Read Only
    - O_WRONLY: Write Only
    - O_RDWR: Read and Write

2. `long lseek(int fd, long offset, int origin)`

- fd: File description
- offset: r/w location relative to origin
- origin: 
    - 0: start from file head
    - 1: start from current location
    - 2: start from file tail
- return: the number of byte read in, if error, return -1

3. `int n_read = read(int fd, char *buf, int n)`
4. `int n_written = write(int fd, char *buf, int n)`

- fd: File description
- buf: the buffer to r/w from
- n: number of byte

- return: the number of byte w/r in, if already reach tail, return 0, if error occurs, return -1

5. `int fstat(int fd, struct stat * metadata)`

- function: Get file attributes for the file, device, pipe, or socket that file descriptor FD is open on and put them in BUF.
- fd: file description
- metadata: the struct to store informations
- return: -1 if error


