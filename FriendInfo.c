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
void str_fit(char *dest, char *src, int max);
void add(int fd, FRIEND_T fr);
void del(int fd, FRIEND_T fr);
void fav(int fd, FRIEND_T fr);

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
//			system("clear");
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
		}else if(strcmp(buf, "add")==0){
			add(fd,fr);
			print_list(fd, check, fr);
		}else if(isdigit(*buf)){
			detailInfo(fd,fr,atoi(buf));
		}else if(strcmp(buf, "del")==0){
			del(fd, fr);
			print_list(fd, check, fr);
		}else if(strcmp(buf, "fav")==0){
			fav(fd, fr);
//			print_list(fd, check, fr);
		}


	}
	close(fd);
	return 0;
}
		

void print_list(int fd, int page, FRIEND_T fr)
{
	int re;
	int size[5]={10,5,17,13,25};
	char arr[1024],ages[10],menu[1024];
		
//	system("clear");

	bzero(menu, sizeof(menu));
	str_fit(menu,"[Name]",size[0]);
	str_fit(menu,"[Age]",size[1]);
	str_fit(menu,"[E-mail]",size[2]);
	str_fit(menu,"[Phone]",size[3]);
	str_fit(menu,"[Address]", size[4]);
	printf("[NUM] %s\n",menu);
	

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

		bzero(arr,sizeof(arr));	

		str_fit(arr,fr.name,size[0]);
		sprintf(ages, "%2d", fr.age);
		str_fit(arr,ages,size[1]);
		str_fit(arr,fr.email, size[2]);
		str_fit(arr,fr.phone, size[3]);
		str_fit(arr,fr.address, size[4]);
		printf("[%03d] %s\n", i,arr);
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

	printf("Flag : %d\n",fr.flag);


}

void str_fit(char *dest, char *src, int max)
{
	int hanCount=0;
	int hanmax=0;

	for(int i=0;i<strlen(src);i++){
		if(src[i]&128)
			hanCount++;
	}
	if(hanCount){
		if((hanCount/3)>4){
			max +=5;
		}else
			max = max + hanCount/3;
	}
	
	if(strlen(src)>=max){
		strncat(dest, src, max);
	}else{
		strcat(dest, src);
	}

	if(strlen(src)<=max){
		for(int i=0;i<max-strlen(src);i++){
			strcat(dest," ");
		}
	}
	strcat(dest, "   ");
}

void add(int fd, FRIEND_T fr)
{
	char buf[1024];
	int re;
	int th;

	th = lseek(fd, 0, SEEK_END)/sizeof(fr);

	printf("%d's....",th);


	bzero(buf,sizeof(buf));

	re=lseek(fd, 0, SEEK_END);
	if(re<0){
		printf("Not Found Pass\n");
		exit(1);
	}
	re=read(fd, &fr, sizeof(fr));
	if(re<sizeof(fr)){
		bzero(&fr, sizeof(fr));
	}

	printf("Name : ");
	fflush(stdout);
	readline(0,buf,sizeof(buf));
	strcpy(fr.name, buf);

	printf("age : ");
	fflush(stdout);
	readline(0,buf,sizeof(buf));
	if(atoi(buf)<100){
		fr.age=atoi(buf);
	}else{
		printf("age Over\n");
		exit(1);
	}

	printf("E-mail : ");
	fflush(stdout);
	readline(0,buf,sizeof(buf));
	strcpy(fr.email, buf);

	printf("Phone : ");
	fflush(stdout);
	readline(0,buf,sizeof(buf));
	strcpy(fr.phone, buf);

	printf("Address : ");
	fflush(stdout);
	readline(0,buf,sizeof(buf));
	strcpy(fr.address, buf);

//	lseek(fd, sizeof(fr), SEEK_END);
	write(fd, &fr, sizeof(fr));
}

void del(int fd, FRIEND_T fr)
{
	int address;
	char buf[1024];
	

	bzero(buf,sizeof(buf));
	printf("Del address : ");
	fflush(stdout);

	readline(0,buf,sizeof(buf));
	address=sizeof(fr)*atoi(buf);
	lseek(fd, address, SEEK_SET);
	bzero(&fr, sizeof(fr));
	write(fd, &fr, sizeof(fr));
}

void fav(int fd, FRIEND_T fr)
{
	char num[10];
	char address;

	bzero(num, sizeof(num));

	printf("Favorite Friend Num : ");
	fflush(stdout);
	readline(0,num,sizeof(num));

	printf("Input : %d\n",atoi(num));

	address= sizeof(fr)*atoi(num);

	lseek(fd, address, SEEK_SET);
	read(fd,&fr,sizeof(fr));
	fr.flag=1;
	lseek(fd, address, SEEK_SET);
	write(fd, &fr, sizeof(fr));

}

	
