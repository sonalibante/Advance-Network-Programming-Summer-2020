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

void str_cli(int socketfd)
{

  struct msghdr msg;
  struct iovec iov;
  int s;
  char message[MAX], server_reply[MAX];

while(1)
{
  message[MAX] = '\0';
  server_reply[MAX] = '\0';
  printf("Enter message to server: ");
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
  {
    perror("sendmsg error: ");
    break;
  }

  memset(&msg, 0, sizeof(msg));
  memset(&iov, 0, sizeof(iov));

  msg.msg_name = NULL;
  msg.msg_namelen = 0;
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
    printf("[+]Print the data received from server > %s\n", server_reply);

 }
}


int main(int argc, char* argv[])
{
    int sockfd, len, slen;
    struct sockaddr_in servaddr, cli;
    char data[MAX];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket error: ");
            exit(1);
        }

    printf("[+]Connecting to server...\n");

    bzero(&servaddr, sizeof(servaddr)); 
   
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    servaddr.sin_port = htons(PORT); 

    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) == -1) {
            perror("connect error: ");
            exit(1);
        }

    printf("[+]Connected...\n");

    str_cli(sockfd);


    close(sockfd);

    return 0;
}