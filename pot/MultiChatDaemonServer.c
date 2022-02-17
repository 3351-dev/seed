#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>		// epoll
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#define EPOLL_SIZE 60
#define EPOLL_EVENT_SIZE 100
#define PORT 8001
#define MAX 1024

int main(int argc, char **argv)
{
	struct epoll_event *events;	// epoll
	struct epoll_event ev;
	struct sockaddr_in serverAddr, clientAddr;
	int sfd, efd, cfd;	//server fd, epoll fd, client fd
	int cliLen;
	int max_got_events;
	int result, readn;
	int sendflags=0;
	char buf[1024]={'\0'};
	int count = 0;
	int recvLen;
	char recvBuffer[MAX];

	// Create Epoll
	if((efd=epoll_create(EPOLL_EVENT_SIZE))<0){
		perror("Epoll Create failed");
		exit(1);
	}

	// Init Epoll
	events=(struct epoll_event *) malloc (sizeof(* events)*EPOLL_SIZE);
	if(events == NULL){
		perror("Epool Init failed");
		exit(1);
	}

	// Create Server Socket 
	cliLen = sizeof(clientAddr);
	if((sfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("Server Socket failed");
		exit(1);
	}

	// SocketInfo, bind, listen
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))==-1){
		close(sfd);
		exit(2);
	}

	if(listen (sfd, 5)==-1){
		perror("Init Accept Socket failed");
		exit(1);
	}

	// Server Start & Epoll event setting, control func on
	printf("Running Server port %d\n",PORT);
	ev.events=EPOLLIN;
	ev.data.fd = sfd;
	if((result = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev))<0){
		perror("epoll_ctl failed");
		exit(1);
	}

	// Server
	while(1){
		max_got_events = epoll_wait(efd, events, EPOLL_SIZE, -1);

		// for, max got events
		for(int i=0; i<max_got_events; i++){
			// Event Socket request

			// First connect 
			if(events[i].data.fd == sfd){
				if((cfd=accept(sfd, (struct sockaddr*)&clientAddr, (unsigned int *)&cliLen))==-1){
					perror("Accept failed");
					exit(1);
				}
				
				ev.events = EPOLLIN;
				ev.data.fd = cfd;
				epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &ev);

				printf("Accept socket : %d\n", cfd);
				count++;
			}else{
				// Event from connected socket
				cfd = events[i].data.fd;

				memset(buf, 0x00, 1024);
				readn = read(cfd, buf, 1024);

				if(readn<=0){
					epoll_ctl(efd, EPOLL_CTL_DEL, cfd, &ev);
					close(cfd);
					printf("Close fd %d\n", cfd);
					count --;
				}else{
					for(int j=5;j<count+5;j++){
						if(cfd != j){
							/*
							char ch_cfd[10];
							sprintf(ch_cfd, "[%d]say:", cfd);
							strcat(buf, ch_cfd);
							*/
							send(j, buf, strlen(buf), sendflags);
						}
					}

				}

				if((recvLen = recv(cfd, recvBuffer,	MAX, 0))==-1){
					perror("Recv Faeild");
					return -1;
				}
				if(recvLen == 0)
					break;
				recvBuffer[recvLen] = '\0';
				printf("[%d] Client >> %s", cfd, recvBuffer);
			}
		}
	}
	return 0;
}

int readline(int fd, char *buf, int bufsize)
{
	char c;
	int i, rc;
	
	bzero(buf, bufsize);

	for(i=0;;i++){
		rc=read(fd, &c, 1);
		if(rc<=0 || c=='\n')
			break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
	return i;
}
	
