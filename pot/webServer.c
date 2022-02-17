#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define PORT 8002
#define MAXPENDDING 5
#define MAX 102400

int readline(int fd, char *buf, int bufsize);

char htmlheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: text/html\r\n\r\n";
char jpgheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: image/jpeg\r\n\r\n";
char pngheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: image/png\r\n\r\n";

int main()
{
	int servSockfd, clntSockfd;
	struct sockaddr_in servAddr,clntAddr;
	char recvBuffer[MAX]; //, sendBuffer[MAX];
	int clntLen, recvLen;
	char requestBuffer[MAX], *requestptr;//, address[MAX];
	pid_t pid;
	int n;
	int filefd=0;


	if((servSockfd=socket(AF_INET, SOCK_STREAM, 0))== -1){
		perror("Sock failed");
		exit(1);
	}

	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family= AF_INET;
	servAddr.sin_addr.s_addr= htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	if(bind(servSockfd, (struct sockaddr*)&servAddr, sizeof(servAddr))==-1){
		perror("bind failed");
		exit(1);
	}

	if(listen(servSockfd, MAXPENDDING)==-1){
		perror("listen failed");
		exit(1);
	}

	printf("Server Daemon Start\n");
	printf("PORT : %d\n", PORT);

	while(1){
		clntLen = sizeof(clntAddr);

		if((clntSockfd=accept(servSockfd, (struct sockaddr*)&clntAddr, (unsigned int *)&clntLen))==-1){
			perror("accept failed");
			continue;
		}

		printf("[%d] Client is in\n",clntSockfd);

		switch(pid=fork()){
			case -1:
				perror("fork failed");
				exit(1);

			// Child Process
			case 0:		
				close(servSockfd);
				while(1){
					recvLen=0;
					if((recvLen=recv(clntSockfd, recvBuffer, MAX, 0))==-1){
						perror("recv failed");
						exit(1);
					}
					if(recvLen==0||recvLen=='\0')
						break;

					recvBuffer[recvLen]='\0';

					printf("[%d] ", clntSockfd);
					printf("Client >>> %s", recvBuffer);

					// WEB SERVER
					bzero(requestBuffer, sizeof(requestBuffer));

					strtok(recvBuffer,"\n");
					printf("recvBuffer : %s\n", recvBuffer);
					requestptr = strstr(recvBuffer,"GET /");
					printf("request ptr : %s\n",requestptr);
					requestptr += 5;
					printf("request ptr : %s\n",requestptr);
					strtok(requestptr, " ");
					printf("request ptr : %s\n",requestptr);

					if(strstr(requestptr, "HTTP/1.")){
						requestptr = "index.html";
					}

					if((filefd=open(requestptr, O_RDONLY))==-1){
						printf("Not found\n");
					}else{
						if(strstr(requestptr,".html")!=NULL){
							write(clntSockfd, htmlheader, sizeof(htmlheader)-1);
						}else if(strstr(requestptr,".jpeg")!=NULL){
							write(clntSockfd, jpgheader, sizeof(jpgheader)-1);
						}else if(strstr(requestptr,".png")!=NULL){
							write(clntSockfd, pngheader, sizeof(pngheader)-1);
						}

						while((n=read(filefd,requestBuffer, MAX))>0){
							write(clntSockfd, requestBuffer,n);
						}
						printf("Server send : %s\n",requestptr);
					}
					close(filefd);
					close(clntSockfd);
				}

			// Parent process
			default:	
//				exit(1);
				break;
				
		}

		if(clntSockfd) close(clntSockfd);
	}
}

int readline(int fd, char *buf, int bufsize)
{
	char c;
	int i,rc;

	bzero(buf,bufsize);

	for(i=0;;i++){
		rc=read(fd, &c, 1);
			if(rc<=0 || c=='\n')
				break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
	return i;
}
