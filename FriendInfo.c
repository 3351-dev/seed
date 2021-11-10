#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "friend.h"
#define DATA "1109.dat"

void print_list(int fd, int page,FRIEND_T fr);
int readline(int fd, char *buf, int bufsize);
void edit(int fd, FRIEND_T fr);
void detailInfo(int fd, FRIEND_T fr, int num);

int check = 0;
int main(int argc, char **argv)
{
	FRIEND_T fr;
	char buf[1024];
	int fd;

	if((fd=open(DATA, O_RDWR))==-1){
		perror("open failed");
		exit(1);
	}

	while(1){
		if(check==0){
			print_list(fd, 1,fr);
			check++;
		}
		printf("Command >> ");
		fflush(stdout);
		readline(0,buf,sizeof(buf));
//		printf("%s\n",buf);

		if(strcmp(buf,"quit")==0){
			system("clear");
			printf("Good Bye~\n");
			break;
		}else if(strcmp(buf,"ls")==0){
			check = 0;
		}else if(strcmp(buf,"")==0){
			check++;
			print_list(fd,check,fr);
		}else if(strcmp(buf, "pre")==0){
			check--;
			print_list(fd, check, fr);
		}else if(strcmp(buf, "edit")==0){
			edit(fd,fr);
		}else if(isdigit(*buf)){
			detailInfo(fd,fr,atoi(buf));
		}


	}
	close(fd);
	return 0;
}
		

void print_list(int fd, int page, FRIEND_T fr)
{
	int re;

	system("clear");
	printf("[Num]\t[Name]\t[age]\t[E-mail]\t\t[Phone]\t\t[Address]\n");
	for(int i=15*(page-1);i<15*page;i++){
		re = lseek(fd, i*sizeof(fr), SEEK_SET);
		if(re<0){
			printf("Not found Pass\n");
			break;
		}
		re = read(fd, &fr, sizeof(fr));
		if(re<sizeof(fr)){
			bzero(&fr, sizeof(fr));
		}
		printf("[%03d]\t%s\t%02d\t%s\t%s\t%s\n",
				i,fr.name,fr.age,fr.email,fr.phone,fr.address);	
	}
}

int readline(int fd, char *buf, int bufsize)
{
	char c;
	int i,rc;

	bzero(buf, bufsize);

	for(i=0;;i++){
		rc=read(fd,&c,1);
		if(rc<=0||c=='\n')
			break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
	return i;
}

void edit(int fd, FRIEND_T fr)
{
	char str1[1024],*str2,*str3;
	int ChangeValue, ChangeAddress,re;

	char arr2[100],arr3[1024];
	str2=arr2;
	str3=arr3;


	while(1){
		printf("Edit >> ");
		fflush(stdout);

		readline(0,str1,sizeof(str1));

		if(!strcmp(str1,"quit"))
			break;
		
		if(!(str2=strtok(str1,"="))){
			// str1에 =이 없으면 그냥 빠져나오도록(segmentation error pass)
			break;
		}
		
		if(str2==NULL){
			// NULL 값일 경우 빠져 나오도록
			break;
		}
	
		ChangeAddress = atoi(str2)*sizeof(fr);
	
		re=lseek(fd, ChangeAddress, SEEK_SET);
		if(re<0){
			printf("Not Found Pass\n");
			exit(1);
		}
		re=read(fd, &fr, sizeof(fr));
		if(re<sizeof(fr)){
			bzero(&fr, sizeof(fr));
		}
	
		str3=strtok(NULL,"=");

		switch(str2[strlen(str2)-1]){
			case 'a' :
				ChangeValue = atoi(str3);
				fr.age = ChangeValue;
				break;
			case 'n' :
				strcpy(fr.name, str3);
				break;
			case 'p' :
				strcpy(fr.phone, str3);
				break;
			case 'A' :
				strcpy(fr.address, str3);
				break;
			case 'e' :
				strcpy(fr.email, str3);
				break;
			default :
				printf("Not found\n");
				break;
		}
		lseek(fd, ChangeAddress, SEEK_SET);
		write(fd, &fr, sizeof(fr));
		print_list(fd, check, fr);
	}


}

void detailInfo(int fd, FRIEND_T fr, int num)
{
	int re;
	int address;

	address = num*sizeof(fr);
	re=lseek(fd, address, SEEK_SET);
	if(re<0){
		printf("Not found Pass\n");
		exit(1);
	}
	re=read(fd, &fr, sizeof(fr));
	if(re<sizeof(fr)){
		bzero(&fr, sizeof(fr));
	}

	printf("\tName\t: %s\n\tAge\t: %d\n\tE-mail\t: %s\n\tPhone\t: %s\n\tAddress\t: %s\n",
			fr.name,fr.age,fr.email,fr.phone,fr.address);
}


