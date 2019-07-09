#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include <arpa/inet.h>
#include<errno.h>

int main(int argc,char **argv)
{
int len;
int sockfd,n;
int r;
struct sockaddr_in servaddr,cliaddr;
char str[1000];
char buff[1024];
char buff1[1024];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(atoi(argv[2]));
r=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(r==-1)
  printf("Errorno = %d\n",errno);
printf("Connect returned %d\n",r);
//Sending Message
printf("\nEnter the message");
scanf("%s",buff);
n=send(sockfd,buff,sizeof(buff),0);
n=recv(sockfd,buff1,sizeof(buff1),0);
printf("\nServer: \t%s",buff1);
close(sockfd);
return 0;
}
