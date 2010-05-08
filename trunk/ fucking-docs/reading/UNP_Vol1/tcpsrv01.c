#include "unp.h"

int main(int argc, char *argv)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_in cliaddr,servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0); /* 通过Socket调用创建一个IPV4套接字 */
  
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* 主机字节序到网络字节序转换(32 bit)  */
  servaddr.sin_port = htons(SERV_PORT); /* 主机字节序到网络字节序转换(16 bit)  */

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); /* 将一个套接字绑定到一个端口上 */

  Listen(listenfd, LISTENQ); /* 侦听 */

  for (;;) {
    clilen = sizeof(cliaddr);
    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen); /* 接收客户端连接 */

    if ((childpid = Fork()) == 0) { /* 创建子进程 */
      Close(listenfd); /* 子进程关闭侦听套接字 */
      str_echo(connfd); /* 处理echo请求 */
      exit(0);
    }
    Close(connfd); /*父进程关闭连接套接字*/
  }
}
