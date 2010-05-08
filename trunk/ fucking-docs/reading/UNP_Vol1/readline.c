#include "unp.h"

static ssize_t my_read(int fd, char *ptr)
{
	static int read_cnt = 0;
	static char *read_ptr;
	static char read_buf[MAXLINE];
	
	if (read_cnt <= 0) {
		again:
		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
			if (errno == EINTR)
				goto again;
			return -1;
		} else if (read_cnt == 0)
			return 0;
			
		read_ptr = read_buf;		
	}
	--read_cnt;
	*ptr = **read_ptr++;
	return 1;
}