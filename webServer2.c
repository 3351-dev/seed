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
#include "friend.h"

#define PORT 8002
#define MAXPENDDING 5
#define MAX 102400

char htmlheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: text/html\r\n\r\n";
char jpgheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: image/jpeg\r\n\r\n";
char pngheader[] = "HTTP/1.1 200 Ok\r\n" "Content-Type: image/png\r\n\r\n";

int readline(int fd, char *buf, int bufsize);

int friends(int sfd,char *option,int select)
{
	int frifd,opt;
	char buf[2048], content[1024];
	FRIEND_T fr;

	option = strtok(option,"=");
	option = strtok(NULL, "=");

	if((frifd=open("1109.dat", O_RDONLY))==-1){
		printf("open failed\n");
		return -1;
	}
	opt = atoi(option);
	write(sfd, htmlheader, strlen(htmlheader));
	sprintf(buf, "<!DOCTYPE html> <html laon=\"ko\"> <head> <title> Friends </title> </head>"
			"<body><h1> Friends List </h1>"
			"<form action=\"find\" method=\"get\">"
			"<input type=\"find\" name=\"what\"><input type=\"submit\"></form>");
	write(sfd, buf, strlen(buf));

	// 1 Show Friends List
	if(select==1){
		for(int i=15*(opt-1);i<15*opt;i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			if(read(frifd, &fr, sizeof(fr))<=0){
				sprintf(buf,"END\n");
				write(sfd, buf, strlen(buf));
				break;
			}
			else{
				sprintf(content, "%s / %d / %s / %s / %s\n"
						, fr.name, fr.age, fr.address, fr.phone, fr.email);
				sprintf(buf, "<p><a href=\"detail=%d\"> %s </a></p>", i+1,content);
				write(sfd, buf, strlen(buf));
			}
		}

	// 2 Detail
	}else if(select==2){
		lseek(frifd, (opt-1)*sizeof(fr), SEEK_SET);
		read(frifd, &fr, sizeof(fr));

		sprintf(buf,"Name : %s<br>Age : %d<br>Address : %s<br>Phone : %s<br>E-mail : %s<br>Favorite : %d<br>",fr.name, fr.age, fr.address, fr.phone, fr.email, fr.flag);
		write(sfd, buf, strlen(buf));
		sprintf(buf, "<p><a href=\"fr?view=%d\"> Home </a></p>",1);
		write(sfd, buf, strlen(buf));

	// 3 Search
	}else if(select==3){
		int size_fri = lseek(frifd, 0,SEEK_END);
		for(int i=0; i*sizeof(fr)<size_fri; i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			read(frifd, &fr, sizeof(fr));
			if((strstr(fr.name, option)
					|| strstr(fr.email, option)
					|| strstr(fr.address, option))){
				sprintf(content, "%s / %d / %s / %s / %s\n", fr.name, fr.age, fr.address, fr.phone, fr.email);
				sprintf(buf, "<p><a href=\"detail=%d\"> %s </a></p>", i+1,content);
				write(sfd, buf, strlen(buf));
			}
		}
	}

	sprintf(buf, "</body> </html>");
	write(sfd, buf, strlen(buf));
	return 0;
	
}


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

		printf("\n\n[%d] Client is in\n",clntSockfd);

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
//					printf("recvBuffer : %s\n", recvBuffer);
					requestptr = strstr(recvBuffer,"GET /");
//					printf("request ptr : %s\n",requestptr);
					requestptr += 5;
//					printf("request ptr : %s\n",requestptr);
					strtok(requestptr, " ");
					printf("request ptr : %s\n\n",requestptr);

					if(!strncmp(requestptr, "fr?",3)){
						return friends(clntSockfd,requestptr+3,1);
					}else if(strstr(requestptr, "detail")){
						return friends(clntSockfd, requestptr,2);
					}else if(!strncmp(requestptr, "find?", 5)){
						return friends(clntSockfd, requestptr+5,3);
					}

					if(strstr(requestptr, "HTTP/")){
						printf("HTTP\n");
						requestptr = "index.html";
						write(clntSockfd, htmlheader, sizeof(htmlheader)-1);
						filefd=open(requestptr, O_RDONLY);
						while((n=read(filefd,requestBuffer, MAX))>0){
							write(clntSockfd, requestBuffer,n);
						}
					}else if((filefd=open(requestptr, O_RDONLY))==-1){
						printf("Not found\n");
					}else{
						printf("requestptr : %s\n", requestptr);
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
