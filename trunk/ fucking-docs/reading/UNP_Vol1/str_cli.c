#include "unp.h"

void str_cli(FILE *fp, int sockfd)
{
  char sendline[MAXLINE], recvline[MAXLINE];
  
  while(Fgets(sendline, MAXLINE, fp) != NULL) { /* 从文件中读取MAXLINE长度的字符串 */
    Writen(sockfd, sendline, strlen(sendline));

    if (Readline(sockfd, recvline, MAXLINE) == 0)
      err_quit("str_cli: server terminated prematurely");

    Fputs(recvline, stdout);
  }
}
