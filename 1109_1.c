#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "friend.h"

#define DATA "1109.dat"

void print_fr(char *str);
//void ChangeValue(char ch);

int main(int argc, char **argv)
{
	FRIEND_T fr;
	int fd;
	int changeValue, address;
	char *buf;
	int ad;

	print_fr("Original");

	if((fd=open(DATA, O_RDWR))==-1){
		perror("open failed");
		exit(1);
	}

	for(int i=0;i<argc-1;i++){
		buf = strtok(argv[i+1], "=");	// where
		if(buf==NULL){
			perror("Not Found");
			exit(1);
		}

//		printf("Buf[0] : %c\n", buf[0]);
//		printf("Buf[1] : %c\n", buf[1]);
		ad = atoi(buf);
//		printf("ad : %d\n",ad);
		address= ad*sizeof(fr);

		printf("Size of Buf : %ld\n",strlen(buf));

		

		switch(buf[strlen(buf)-1]){
			case 'a' :
				buf = strtok(NULL,"=");
				changeValue = atoi(buf);

				lseek(fd, address, SEEK_SET);
				read(fd, &fr, sizeof(fr));
				fr.age = changeValue;
				lseek(fd, address, SEEK_SET);
				write(fd, &fr, sizeof(fr));
				break;

			case 'n' :
				buf = strtok(NULL,"=");

				lseek(fd, address, SEEK_SET);
				read(fd, &fr, sizeof(fr));
				strcpy(fr.name, buf);
				lseek(fd, address, SEEK_SET);
				write(fd, &fr, sizeof(fr));
				break;\

			case 'p' :
				buf = strtok(NULL,"=");

				lseek(fd, address, SEEK_SET);
				read(fd, &fr, sizeof(fr));
				strcpy(fr.phone, buf);
				lseek(fd, address, SEEK_SET);
				write(fd, &fr, sizeof(fr));
				break;

			case 'A' :
				buf = strtok(NULL,"=");

				lseek(fd, address, SEEK_SET);
				read(fd, &fr, sizeof(fr));
				strcpy(fr.address, buf);
				lseek(fd, address, SEEK_SET);
				write(fd, &fr, sizeof(fr));
				break;

			case 'e':
				buf = strtok(NULL,"=");

				lseek(fd, address, SEEK_SET);
				read(fd, &fr, sizeof(fr));
				strcpy(fr.email, buf);
				lseek(fd, address, SEEK_SET);
				write(fd, &fr, sizeof(fr));
				break;
			default :
				printf("Not Found\n");
				exit(1);

		}

	}
	close(fd);

	print_fr("Change");
	return 0;
}

void print_fr(char *str)
{
	FRIEND_T fr;
	int fd, i=0;

	printf("\t\t\t%s\n",str);
	
	if((fd=open(DATA, O_RDONLY))==-1){
		perror("open failed");
		exit(1);
	}
	while(read(fd, &fr, sizeof(fr))>0){
		printf("[%02d] fr.Name = %s\n", i, fr.name);
		printf("[%02d] fr.age = %02d\n", i, fr.age);
		printf("[%02d] fr.Address = %s\n", i, fr.address);
		printf("[%02d] fr.Phone = %s\n", i, fr.phone);
		printf("[%02d] fr.Email = %s\n", i, fr.email);
		printf("- - - - - - - - - \n");
		i++;
	}

	close(fd);
	printf("\n");
}

