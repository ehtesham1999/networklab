#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>


int main(int argc,char **argv)
{
int fd, sz; 
char *c = (char *) calloc(100, sizeof(char)); 


int len;
int sockfd,newfd,n;
struct sockaddr_in servaddr,cliaddr;
char buff[1024];
char str[1000];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(atoi(argv[1]));
if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
perror("Bind error");

listen(sockfd,4);
for(int i=0;i<3;i++)
{
len=sizeof(cliaddr);
printf("Waiting for connection:\n");
newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
printf("Connected");
//Receiving the message
n=read(newfd,buff,sizeof(buff));
printf("\nfilename: \t%s",buff);
fd = open(buff, O_RDONLY); 
sz = read(fd, c, 100); 
c[sz] = '\0'; 
printf("\nThose bytes are as follows: %s\n", c); 

//printf("\nEnter the message:");
//scanf("%s",buff);
write(newfd,c,sizeof(c));
printf("\n");
close(newfd);
close(fd);
}
close(sockfd);
return 0;
}
