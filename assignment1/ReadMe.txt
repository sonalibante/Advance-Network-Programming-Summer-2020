Open university linux servers, can test on two different servers. 

First complile both the server and client files with following commands on respective University Linux servers.

gcc server.c -o server.o
gcc client.c -o client.o

Now start the server 

./server.o <ip address of the machine>

Now start the client 

./client.o <ip address of the machine>