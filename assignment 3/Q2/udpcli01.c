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

void dg_cli(int socketfd, const SA *pservaddr, socklen_t servlen)
{

  struct msghdr msg;
  struct iovec iov;
  int s;
  char message[MAX] , server_reply[MAX];
  socklen_t len;

while(1)
{
  message[MAX] = '\0';
  server_reply[MAX] = '\0';
  len = servlen;
  printf("Enter message to server: ");
  fgets(message, sizeof(message), stdin);

  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));

  msg.msg_name = pservaddr;
  msg.msg_namelen = servlen;
  iov.iov_base = message;
  iov.iov_len = strlen(message)+1;
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;

  s = sendmsg(socketfd, &msg, 0);

  if(s < 0)
  {
    perror("sendmsg error: ");
    break;
  }

  len = servlen;
  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));

  msg.msg_name = pservaddr;
  msg.msg_namelen = servlen;
  iov.iov_base = server_reply;
  iov.iov_len = MAX;
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = NULL;
  msg.msg_controllen = 0;
  msg.msg_flags = 0;


  s = recvmsg(socketfd, &msg, 0);
  
  if(s < 0)
  {
    perror("recvmsg error: ");
    break;
  }
    
  else
    printf("Print the data received from server > %s\n", server_reply);

 }
}


int main(int argc, char* argv[])
{
    int sockfd, len, slen;
    struct sockaddr_in servaddr, cli;
    char data[MAX];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
            perror("socket error: ");
            exit(1);
        }

    printf("Connecting to server...\n");

    bzero(&servaddr, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(PORT); 

    dg_cli(sockfd, (SA *) &servaddr, sizeof(servaddr));


    close(sockfd);

    return 0;
}