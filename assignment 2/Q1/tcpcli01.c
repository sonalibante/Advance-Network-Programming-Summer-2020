#include	"unp.h"
#include	<netinet/tcp.h>	


int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;
	int flag= 1;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	Setsockopt(sockfd, SOL_SOCKET, IPPROTO_TCP, &flag, sizeof(flag));

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
