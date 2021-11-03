#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct profile{
	int age;
	char name[128];
	char address[256];
	char gender;
	char phone[16];
	char email[64];
} FRIEND_T;
	

int main(int argc, char **argv){

	FRIEND_T fr;
	int fd=0;

	// argc check
	if(argc<2){
		printf("argc failed\n");
		exit(1);
	}
	
	// READ FILE FOR WRITE
	if((fd=open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666))==-1){
		perror("oepn failed");
		exit(1);
	}


	// WRITE
	for(int i=0;i<10;i++){
		// INIT fr
		bzero(&fr,sizeof(fr));	
		
		fr.age = i+10;
//		printf("Friends age : %d\n",fr.age);

		if((write(fd, &fr, sizeof(fr)))==-1){
			perror("write failed");
			exit(1);
		}
	}
	close(fd);


	// READ TEST
	fd = 0;
	if((fd=open(argv[1], O_RDONLY))==-1){
		perror("read failed");
		exit(1);
	}
	while(read(fd,&fr,sizeof(fr))>0){
		printf("age : %d\n",fr.age);
	}
	close(fd);
}		
