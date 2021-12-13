#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "friend.h"
#define DATA "1109.dat"
#define DATA2 "fr4.txt"

int main(int argc, char *argv[])
{
	FRIEND_T fr;
	char buf[1024], ages[10];
	int fd,fd2,end;

	if((fd=open(DATA, O_RDWR))==-1){
		perror("open failed 1");
		exit(1);
	}

	if((fd2=open(DATA2, O_RDWR | O_CREAT,0644))==-1){
		perror("open failed 2");
		exit(1);
	}

	end=lseek(fd,0,SEEK_END);

	for(int i=0;i<end/sizeof(fr);i++){
		bzero(buf, sizeof(buf));
		if(lseek(fd, i*sizeof(fr),SEEK_SET)<0)
			break;
		if(read(fd, &fr, sizeof(fr))<0)
			break;

//		printf("%d :: %s %d %s %s %s\n", i, fr.name, fr.age, fr.email, fr.phone, fr.address);
		strcat(buf, fr.name);
		strcat(buf, ";");
		sprintf(ages, "%d" ,fr.age);
		strcat(buf, ages);
		strcat(buf, ";");
		strcat(buf, fr.email);
		strcat(buf, ";");
		strcat(buf, fr.phone);
		strcat(buf, ";");
		strcat(buf, fr.address);
		strcat(buf, ";");
		strcat(buf, "\n");

		write(fd2, buf, sizeof(buf));
	}
	
	lseek(fd2, 0, SEEK_SET);
	while(read(fd2, buf,sizeof(buf))>0){
		printf("%s", buf);
	}

	close(fd);
	close(fd2);

}
