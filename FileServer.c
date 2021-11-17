#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sendfile.h>

#define PORT 8001
#define MAXPENDDING 5
#define MAX 1024

int readline(int fd, char *buf, int bufsize);
int ls(char *list, int listCount);
int get(int clntSockfd,char *recvBuffer, char *list);

int main()
{
	int servSockfd, clntSockfd;
	struct sockaddr_in servAddr,clntAddr;
	char recvBuffer[MAX], sendBuffer[MAX];
	int clntLen, recvLen;
	char list[MAX*100];
	int listCount=0, getSize=0;
	char server_msg[MAX];

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

	while(1){
		clntLen = sizeof(clntAddr);

		if((clntSockfd=accept(servSockfd, (struct sockaddr*)&clntAddr, (unsigned int *)&clntLen))==-1){
			perror("accept failed");
			exit(1);
		}

		printf("[%d] Client is in\n",clntSockfd);
		printf("- - - - - - - - - -\n");

		switch(fork()){
			case -1:
				perror("fork failed");
				exit(1);

			case 0:
				close(servSockfd);
				while(1){
					if((recvLen=recv(clntSockfd, recvBuffer, MAX, 0))==-1){
						perror("recv failed");
						exit(1);
					}
					if(recvLen==0)
						break;

					recvBuffer[recvLen]='\0';

					printf("[%d] ", clntSockfd);
					printf("Client >>> %s", recvBuffer);

					// ★  Very Important
					strtok(recvBuffer, "\r");

					bzero(server_msg, sizeof(server_msg));
					bzero(list, sizeof(list));
					if((strcmp(recvBuffer, "ls"))==0){
						listCount=ls(list, listCount);
						sprintf(server_msg, "ok, total count : %d\n",listCount);
						send(clntSockfd, server_msg, strlen(server_msg), MSG_NOSIGNAL);
						send(clntSockfd, list, strlen(list), MSG_NOSIGNAL);
					}else if((strstr(recvBuffer, "get"))!=NULL){
						printf("cmd > get\n");
						getSize=get(clntSockfd, recvBuffer, list);
						sprintf(server_msg, "ok, total size : %d\n",getSize);
						send(clntSockfd, server_msg, strlen(server_msg), MSG_NOSIGNAL);
						send(clntSockfd, list, strlen(list), MSG_NOSIGNAL);
					}

				}
				close(clntSockfd);
				exit(0);

			default:
				while(1){
					char serverMacro[MAX]="[Server say] ";
					readline(0,sendBuffer,sizeof(sendBuffer));
					strcat(sendBuffer,"\n");
					strcat(serverMacro, sendBuffer);
//					printf("SERVER : %s\n",serverMacro);

					if(!strcmp(sendBuffer, "quit\n")){
						printf("Good Bye~\n");
						close(servSockfd);
						close(clntSockfd);
						exit(1);
					}

					if(send(clntSockfd, serverMacro, strlen(serverMacro), MSG_NOSIGNAL)
							!= strlen(serverMacro)){
						if(errno==EPIPE){
							printf("Client is out\n");
							break;
						}

						perror("send failed");
						exit(1);
					}
							
				}
		}
		close(clntSockfd);
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

int ls(char *list,int listCount)
{
	int size=MAX*100;
	int fd,re;
	char ptr[size], *ptr2;

	listCount = 0;
	system("rm list.txt");
	bzero(list, size);
	system("ls >list.txt");
	if((fd=open("list.txt", O_RDONLY))==-1){
		perror("open failed");
		exit(1);
	}
	re=read(fd, list, size);
	if(re<sizeof(list)){
		bzero(list, size);
	}

	strcpy(ptr, list);

	ptr2 = strtok(ptr, "\n");
	while(ptr2!=NULL){
		ptr2 = strtok(NULL, "\n");
		listCount++;
	}
	printf("Count : %d\n",listCount);
	printf("ls : %s\n",list);

	close(fd);
	return listCount;
}

int get(int clntSockfd,char *recvBuffer, char *list)
{
	char buf[MAX], *ptr, fileName[MAX];
	int size,filehandle;

//	printf("clntSockfd : %d\n", clntSockfd);

	strcpy(buf, recvBuffer);
	ptr=strtok(buf, " ");
	ptr=strtok(NULL, " ");
	printf("%s\n", ptr);

	strcpy(fileName, ptr);
	printf("%s\n", fileName);

	if(strcmp(fileName, "1116test.c")==0){
		printf("Same\n");
	}

	if((filehandle = open(fileName, O_RDONLY))<0){
		printf("fileHandler failed\n");
	}else{
		size = lseek(filehandle, 0, SEEK_END);
		printf("%s size(%d) : %d\n", fileName, filehandle,size);
		lseek(filehandle, 0, SEEK_SET);
		read(filehandle, list, size);
	}

	if((sendfile(clntSockfd, filehandle, NULL, size))<0){
		printf("sendfile failed\n");
	}
/*
	filehandle=open("1116test.c", O_RDONLY);
	read(filehandle, list, size);
	size=lseek(filehandle, 0, SEEK_END);
*/

	printf("[get]%d:%d\n%s\n",filehandle,size,list);

	close(filehandle);
	return size;

}	
