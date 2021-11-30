#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "friend.h"

#define MAX 1024
#define DATA "1109.dat"

int friends(int select, char *option);
int str_fit(char *dest, char *src, int max);

int main(int argc, char **argv)
{
	friends(1,"1");
	return 0;
}

int friends(int select, char *option)
{	
	int frifd, opt;
	char Buf[MAX*10],get[MAX];
	FRIEND_T fr;

	if((frifd=open(DATA, O_RDONLY))==-1){
		printf("open failed\n");
		return -1;
	}

	opt = atoi(option);

	sprintf(Buf, "Content-type: text/html\n\n"
			"<!DOCTYPE html> <html> <head> <title> Fr </title> </head>"
			"<body> <h1> Friends List </h1>"
			"<form action\"find\" method=\"get\">"
			"<input type=\"find\" name=\"find\">"
			"<input type=\"submit\"> </form>"
		   );

	printf("%s\n", Buf);


	// 1 Show Friends List
	if(select == 1){
		char arr[MAX], ages[10];
		for(int i=15*(opt-1); i<15*opt; i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			if(read(frifd, &fr, sizeof(fr))<=0){
				sprintf(Buf,"END");
				printf("%s\n",Buf);
				break;
			}else{
				bzero(arr, sizeof(arr));
				//10 5 17 13 25
				str_fit(arr, fr.name, 4);
				sprintf(ages, "%2d", fr.age);
				str_fit(arr, ages, 4);
				str_fit(arr, fr.email, 10);
				str_fit(arr, fr.phone, 10);
				str_fit(arr, fr.address, 10);

				sprintf(Buf, "<p>[%03d]"
						"<a href=\"detail=%d\"> %s </a> </p>", i+1, i+1, arr);
				printf("%s\n",Buf);
			}
		}
	}else if(select == 2){


	sprintf(Buf, "<p> select : %d </p> </body></html>",select);
	printf("%s\n", Buf);

	return 0;
}

int str_fit(char *dest, char *src, int max)
{
	int krCount = 0;
	// 한글 확인
	for(int i=0;i<strlen(src);i++){
		if(src[i]&128)
			krCount++;
	}
	// 한글 처리
	if(krCount){
		if((krCount/3)>4){
			max+=5;
		}else
			max = max+krCount/3;
	}
	// dest에 src 써주기
	if(strlen(src)>=max){
		strncat(dest, src, max);
	}else{
		strcat(dest, src);
	}
	// max값보다 작으면 공백으로 채워줌
//	printf("strlen : %ld, max : %d<br>", strlen(src),max);
	if(strlen(src)<=max){
		for(int i=0;i<max-strlen(src);i++){
			strcat(dest,"&nbsp");
		}
	}
	strcat(dest, "&nbsp");
	return 0;
}


