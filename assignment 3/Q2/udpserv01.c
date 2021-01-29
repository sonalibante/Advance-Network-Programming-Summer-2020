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
#define PORT 6666
#define SA struct sockaddr 

void dg_echo(int socketfd, SA *pcliaddr, socklen_t clilen)
{
  struct msghdr msg;
  struct iovec iov;
  int s;
  char message[MAX] , client_reply[MAX];
  socklen_t len;

  while(1)
    {
      message[MAX] = '\0';
      client_reply[MAX] = '\0';
      len = clilen;
      memset(&msg, 0, sizeof(msg));
      memset(&iov, 0, sizeof(iov));

      msg.msg_name = pcliaddr;
      msg.msg_namelen = len;
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
        printf("Print the data received from client > %s\n", client_reply);


      printf("Enter message to client: ");
      fgets(message, sizeof(message), stdin);
      len = clilen;
      memset(&msg, 0, sizeof(msg));
      memset(&iov, 0, sizeof(iov));

      msg.msg_name = pcliaddr;
      msg.msg_namelen = len;
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

    int sockfd, s2, len, slen, connfd;
    socklen_t t;
    struct sockaddr_in  cliaddr, servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket error: ");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(PORT);

    if (bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind error: ");
        exit(1);
    }
    
    dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));

    close(sockfd);

    return 0;
}