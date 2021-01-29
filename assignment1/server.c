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


int main(int argc, char** argv[])
{


    int listenfd,connfd, client_sock, c, read_size, size;
    pid_t childpid;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in cliaddr, servaddr;
    socklen_t socklen = sizeof(size);




    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd == -1)
    {
        printf("[-]Failed to Created Client Socket.\n");
        exit(1);
    }
    else
    {
        printf("[+]Client Socket Created Sucessfully.\n");

        bzero(&servaddr,sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(SERV_PORT);




        if((bind(listenfd, (SA*)&servaddr, sizeof(servaddr)))<0)
        {
            printf("[-]Failed to socket binding to Server.\n");
            exit(2);

        }
        else
        {
            printf("[+]Binded the socket successfully \n");
            listen(listenfd,5);
            printf("[+]Listening...\n");
            c = sizeof(struct sockaddr_in);

            //accept
            client_sock = accept(listenfd, (SA *)&cliaddr, (socklen_t*)&c);
            if (client_sock < 0)
            {
                perror("[-]accept failed");
                return 1;
            }
            puts("[+]Connection accepted");




            // Printig message from the client

            printf("[+]Message From the CLient\n " );

            while( (read_size = recv(connfd, buffer, sizeof(buffer)-1,0)) > 0 )
            {
                puts(buffer);

                execvp(buffer,NULL);

                buffer[0]='\0';

            }


            // modifying SO_DONTROUTE
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_DONTROUTE,&size,&socklen);
            printf("Before socket SO_DONTROUTE =: %u\n",size);

            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_DONTROUTE,&size,sizeof(size));
                printf("After socket SO_DONTROUTE =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_DONTROUTE,&size,sizeof(size));
                printf("After socket SO_DONTROUTE =: %u\n",size);
            }

// modifying SO_ERROR
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_ERROR,&size,&socklen);
            printf("Before socket SO_ERROR =: %u\n",size);

            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_ERROR,&size,sizeof(size));
                printf("After socket SO_ERROR =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_ERROR,&size,sizeof(size));
                printf("After socket SO_ERROR =: %u\n",size);
            }
// modifying SO_KEEPALIVE
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_KEEPALIVE,&size,&socklen);
            printf("Before socket SO_KEEPALIVE =: %u\n",size);
            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_KEEPALIVE,&size,sizeof(size));
                printf("After socket SO_KEEPALIVE =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_KEEPALIVE,&size,sizeof(size));
                printf("After socket SO_KEEPALIVE =: %u\n",size);
            }
// modifying SO_REUSEPORT
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&size,&socklen);
            printf("Before socket SO_REUSEPORT =: %u\n",size);
            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&size,sizeof(size));
                printf("After socket SO_REUSEPORT =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&size,sizeof(size));
                printf("After socket SO_REUSEPORT =: %u\n",size);
            }
// modifying SO_REUSEADDR
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&size,&socklen);
            printf("Before socket SO_REUSEADDR =: %u\n",size);
            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&size,sizeof(size));
                printf("After socket SO_REUSEADDR =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&size,sizeof(size));
                printf("After socket SO_REUSEADDR =: %u\n",size);
            }
// modifying SO_TYPE
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_TYPE,&size,&socklen);
            printf("Before socket SO_TYPE =: %u\n",size);
            if(size==0)
            {
                size=1;
                setsockopt(listenfd,SOL_SOCKET,SO_TYPE,&size,sizeof(size));
                printf("After socket SO_TYPE =: %u\n",size);
            }
            else
            {
                size=0;
                setsockopt(listenfd,SOL_SOCKET,SO_TYPE,&size,sizeof(size));
                printf("After socket SO_TYPE =: %u\n",size);
            }
// modifying send and recv bugger
            size=65535;
            setsockopt(listenfd,SOL_SOCKET,SO_RCVBUF,&size,sizeof(size));
            size=98538;
            setsockopt(listenfd,SOL_SOCKET,SO_SNDBUF,&size,sizeof(size));
            size=0;
            getsockopt(listenfd,SOL_SOCKET,SO_RCVBUF,&size,&socklen);
            printf("After socket send buffer size: %u\n",size);








            send(connfd, buffer, strlen(buffer), 0);

            if(connfd < 0)
            {
                printf("[-]The server failed to accept the client \n");
                exit(3);
            }
            else
            {
                printf("[+]The server accepts the client \n");
            }

            if(read_size == 0)
            {
                puts("[-]Client disconnected");
                fflush(stdout);
            }






        }
    }



}

