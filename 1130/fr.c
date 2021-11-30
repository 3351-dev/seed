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

int main(int argc, char **argv)
{
	char *local_url, *option;

	printf("Content-type: text/html\n\n");
	local_url = getenv("QUERY_STRING");

	if(strstr(local_url, "list")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		friends(1,option);
	}else if(strstr(local_url, "detail")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		friends(2,option);
	}else if(strstr(local_url, "search")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		friends(3,option);
	}else{
		friends(1,"1");
	}
	return 0;
}

int friends(int select, char *option)
{	
	int frifd, opt;
	char Buf[MAX*10], content[MAX];
	FRIEND_T fr;

	if((frifd=open(DATA, O_RDONLY))==-1){
		printf("open failed\n");
		return -1;
	}

	opt = atoi(option);

	sprintf(Buf,"<!DOCTYPE html> <html> <head> <title> Fr </title> </head>"
			"<body> <h1> Friends List </h1>"
			"<form action\"./fr.cgi\" method=\"get\">"
			"<input type=\"search\" name=\"search\">"
			"<input type=\"submit\"> </form><br>"
		   );

	printf("%s\n", Buf);


	// 1 Show Friends List
	if(select == 1){
//		char arr[MAX], ages[10];
		for(int i=15*(opt-1); i<15*opt; i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			if(read(frifd, &fr, sizeof(fr))<=0){
				sprintf(Buf,"END");
				printf("%s\n",Buf);
				break;
			}else{
				sprintf(content,"%s / %d / %s / %s / %s\n", fr.name, fr.age, fr.phone, fr.email, fr.address);
				sprintf(Buf, "<p>[%03d] <a href=\"./fr.cgi?detail=%d\"> %s </a> </p>", i+1, i+1, content);
				printf("%s\n", Buf);
			}
		}
	}
	// 2 Show Detail
	else if(select == 2){
		lseek(frifd, (opt-1)*sizeof(fr), SEEK_SET);
		read(frifd, &fr, sizeof(fr));

		sprintf(Buf, " Name: %s<br>Age: %d<br>Phone: %s<br>E-mail: %s<br>Address: %s<br>Favorite: %d<br>"
				, fr.name, fr.age, fr.phone, fr.email,fr.address, fr.flag);
		printf("%s\n", Buf);
		sprintf(Buf, "<p> <a href=\"./fr.cgi?list=%d\"> Home </a></p>", 1);
		printf("%s\n", Buf);
	}

	// 3 Show Search
	else if(select == 3){
		int size_fri = lseek(frifd, 0, SEEK_END);
		for(int i=0;i*sizeof(fr)<size_fri;i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			read(frifd, &fr, sizeof(fr));
			if((strstr(fr.name, option)
						|| strstr(fr.email, option)
						|| strstr(fr.address, option))){
				sprintf(content,"%s / %d / %s / %s / %s\n", fr.name, fr.age, fr.address, fr.phone, fr.email);
				sprintf(Buf, "<p>[%03d] <a href=\"./fr.cgi?detail=%d\"> %s </a> </p>", i+1, i+1, content);
				printf("%s\n", Buf);
			}
		}
	}

	close(frifd);

	sprintf(Buf, "<p> select : %d </p> </body></html>",select);
	printf("%s\n", Buf);

	return 0;
}
