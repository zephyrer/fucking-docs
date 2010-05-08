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
		nleft -= nwritten;		/* ��ȥ��д����ֽ� */
		ptr += nwritten;		/* ָ������ƫ�ƣ�������vptr�ж�ȡ�ֽڣ�����fd��ص��ļ���д */
	}
	return (n);
 }