#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "friend.h"

#define DATA "1108.dat"

void print_fr(char *str);

int main(int argc, char **argv)
{
	FRIEND_T fr;
	int fd;
	int i=0;
	int changeValue, address;
	char *buf;

	print_fr("Original");

	if((fd=open(DATA, O_RDWR))==-1){
		perror("open failed");
		exit(1);
	}

	for(int i=0;i<argc-1;i++){
		buf = strtok(argv[i+1], "=");
		if(buf==NULL){
			perror("Not Found");
			exit(1);
		}
		address = atoi(buf)*sizeof(fr);

		buf = strtok(NULL, "=");
//		buf+=2;
		changeValue = atoi(buf);

		lseek(fd, address, SEEK_SET);
		read(fd, &fr, sizeof(fr));
		fr.age = changeValue;
		lseek(fd, address, SEEK_SET);
		write(fd, &fr, sizeof(fr));
	}
	close(fd);

	print_fr("Change");
	return 0;
}

void print_fr(char *str)
{
	FRIEND_T fr;
	int fd, i=0;

	printf("\t%s\n",str);
	
	if((fd=open(DATA, O_RDONLY))==-1){
		perror("open failed");
		exit(1);
	}
	while(read(fd, &fr, sizeof(fr))>0){
		printf("[%02d] fr.age = %02d\n", i, fr.age);
		i++;
	}

	close(fd);
	printf("\n");
}
