 #include "unp.h"
 
 ssize_t	/* write "n" bytes to a descriptor */
 writen (int fd, const void *vptr, suze_t n)
 {
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	
	ptr = vptr;
	nleft = n;
	
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return (-1);
		}
		nleft -= nwritten;		/* 减去已写完的字节 */
		ptr += nwritten;		/* 指针往后偏移，继续从vptr中读取字节，往与fd相关的文件中写 */
	}
	return (n);
 }