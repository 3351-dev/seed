#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "friend.h"
#define DATA "fr5.dat"
#define DATA2 "fr4.txt"

int main(int argc, char *argv[])
{
	FRIEND_T fr;
	char buf[1024], *ptr;
	int fd,fd2,end,count=0;
	int ages;


	// fr4.txt
	if((fd=open(DATA2, O_RDWR))==-1){
		perror("open failed 1");
		exit(1);
	}

	// fr5.dat
	if((fd2=open(DATA, O_RDWR | O_CREAT,0644))==-1){
		perror("open failed 2");
		exit(1);
	}

	// count	
	while(read(fd, buf, sizeof(buf))>0){
		if(strcmp(buf,"\n")){
			count++;
		}
	}
	printf("count : %d\n", count);
	

	// init
	lseek(fd, 0, SEEK_SET);
	system("rm fr5.dat");


	// write start
	for(int i=0;i<count;i++){
		lseek(fd2, 0, SEEK_END);
		if(read(fd2, &fr, sizeof(fr))<sizeof(fr)){
			bzero(&fr, sizeof(fr));
		}

		read(fd, buf, sizeof(buf));
		ptr = strtok(buf, ";");
		strcpy(fr.name, ptr);
		printf("ptr : %s\n", ptr);
		
		ptr = strtok(NULL,";");		
		fr.age=atoi(ptr);
		printf("ptr : %s\n", ptr);

		ptr = strtok(NULL, ";");
		strcpy(fr.email, ptr);
		printf("ptr : %s\n", ptr);

		ptr = strtok(NULL, ";");
		strcpy(fr.phone, ptr);
		printf("ptr : %s\n", ptr);
		
		ptr = strtok(NULL, ";");
		strcpy(fr.address, ptr);
		printf("ptr : %s\n", ptr);
		printf("\n");

		write(fd2, &fr, sizeof(fr));
	}
	printf("\n");
	printf("size fd1 : %ld\n", lseek(fd, 0, SEEK_END));
	printf("size fd2 : %ld\n", lseek(fd2, 0, SEEK_END));
	printf("\n");

	lseek(fd, 0 , SEEK_SET);
	lseek(fd2, 0, SEEK_SET);
	while(read(fd2, &fr, sizeof(fr))>0){
		printf("name : %s\n", fr.name);
		printf("age : %d\n", fr.age);
		printf("email : %s\n", fr.email);
		printf("phone : %s\n", fr.phone);
		printf("address : %s\n", fr.address);
		printf("\n");
	}

	close(fd);
	close(fd2);

}
