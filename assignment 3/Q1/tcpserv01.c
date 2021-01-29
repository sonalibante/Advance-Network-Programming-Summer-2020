#include <netinet/tcp.h>
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#define MAX 1000
#define PORT 4545
#define SA struct sockaddr 

void str_echo(int socketfd)
{
  struct msghdr msg;
  struct iovec iov;
  int s;
  char message[MAX] , client_reply[MAX];

  while(1)
    {
      message[MAX] = '\0';
      client_reply[MAX] = '\0';

      memset(&msg, 0, sizeof(msg));
      memset(&iov, 0, sizeof(iov));

      msg.msg_name = NULL;
      msg.msg_namelen = 0;
      iov.iov_base = client_reply;
      iov.iov_len = MAX;
      msg.msg_iov = &iov;
      msg.msg_iovlen = 1;
      msg.msg_control = NULL;
      msg.msg_controllen = 0;
      msg.msg_flags = 0;

      //printf("msg: %s\n", (char *) iov.iov_base);

      s = recvmsg(socketfd, &msg, 0);
      
      if(s < 0)
        perror("recvmsg error: ");

      else
        printf("Print data received from client > %s\n", client_reply);


      printf("Enter message to client: ");
      fgets(message, sizeof(message), stdin);

      memset(&msg, 0, sizeof(msg));
      memset(&iov, 0, sizeof(iov));

      msg.msg_name = NULL;
      msg.msg_namelen = 0;
      iov.iov_base = message;
      iov.iov_len = strlen(message)+1;
      msg.msg_iov = &iov;
      msg.msg_iovlen = 1;
      msg.msg_control = NULL;
      msg.msg_controllen = 0;
      msg.msg_flags = 0;


      s = sendmsg(socketfd, &msg, 0);

      if(s < 0)
        perror("sendmsg error: ");
    }
}


int main(int argc, char* argv[])
{

    int listenfd, s2, len, slen, connfd;
    socklen_t t;
    struct sockaddr_in  cliaddr, servaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error: ");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(PORT);

    if (bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind error: ");
        exit(1);
    }

    if (listen(listenfd, 5) == -1)
    {
        perror("listen error: ");
        exit(1);
    }

    printf("Waiting for a connection...\n");

    len = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len)) == -1)
    {
        perror("accept error: ");
        exit(1);
    }

    printf("Connected...\n");
    
    str_echo(connfd);

    close(connfd);

    return 0;
}