#include "unp.h"

int main(int argc, char *argv)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr,servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0); /* ͨ��Socket���ô���һ��IPV4�׽��� */
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* �����ֽ��������ֽ���ת��(32 bit)  */
  servaddr.sin_port = htons(SERV_PORT); /* �����ֽ��������ֽ���ת��(16 bit)  */

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); /* ��һ���׽��ְ󶨵�һ���˿��� */

  Listen(listenfd, LISTENQ); /* ���� */

  for (;;) {
    clilen = sizeof(cliaddr);
    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen); /* ���տͻ������� */

    if ((childpid = Fork()) == 0) { /* �����ӽ��� */
      Close(listenfd); /* �ӽ��̹ر������׽��� */
      str_echo(connfd); /* ����echo���� */
      exit(0);
    }
    Close(connfd); /*�����̹ر������׽���*/
  }
}
