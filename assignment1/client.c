#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include "checkopts.c"

#define MAXIMUM 1024
#define SERV_PORT 8080
#define LISTENQ 5
#define MAXLINE 1000
#define SA struct sockaddr



int main(int argc,char** argv[])
{
    int sockfd, sock_option, fd;
    char buffer[1024];
    struct sockaddr_in servaddr;

    struct sock_opts *ptr;
    socklen_t len;
    char option_strng[600], optionval[600],totalval[1200];

    if(argc!=2)
    {
        printf("usage:tcpcli<IPaddress>\n");
    }

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd == -1)
    {
        printf("[-]Failed creating the socket \n\n");
        exit(1);
    }
    else
    {
        printf("[+]Client Created socket successfully \n");

        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(SERV_PORT);
        inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

        if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))<0)
        {
            printf("[-]Failed connecting to the server \n");
            exit(2);

        }
        else
        {
            printf("[+]Connected with server successfully \n");

        }



        for (ptr = sock_opts; ptr->opt_str != NULL; ptr++)
        {
            if (ptr->opt_val_str == NULL)
                printf("(undefined) \n");
            else
            {
                switch (ptr->opt_level)
                {
                case SOL_SOCKET:
                case IPPROTO_IP:
                case IPPROTO_TCP:
                    fd = socket(AF_INET, SOCK_STREAM, 0);
                    break;
#ifdef IPV6
                case IPPROTO_IPV6:
                    fd = socket(AF_INET6, SOCK_STREAM, 0);
                    break;
#endif
#ifdef IPPROTO_SCTP
                case IPPROTO_SCTP:
                    fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
                    break;
#endif

                default:
                    perror("cannot create socket descriptor");
                }
                len = sizeof(val);
                if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len) == -1)
                {
                    perror("getsockopt Error");
                }
                else
                {
                    strcpy(option_strng, ptr->opt_str);
                    strcpy(optionval, (*ptr->opt_val_str)(&val, len));
                    snprintf(totalval,sizeof(totalval),"%s=%s",option_strng,optionval);

                    puts(totalval);
                    write(sockfd, totalval, strlen(totalval));

                }
            }
        }



        printf("[+]Data trasmitted\n");

    }

    exit(0);
}
