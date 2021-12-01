#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "friend.h"

#define LIST_NUM 5
#define MAX 1024
#define DATA "1109.dat"
#define HOME (((opt-1)/LIST_NUM)+1)

char header[] ={ 
			"<!DOCTYPE html> <html> <head> <title> Fr </title> </head>"
			"<body> <h1 align=\"center\"> Friends List &nbsp </h1>"
};
char end[]={
			"</body></html>"
};

int friends(int select, char *option);
int friends_rdwr(int select, char *option);

int main(int argc, char **argv)
{
	char *local_url, *option;

	printf("Content-type: text/html\n\n");
	local_url = getenv("QUERY_STRING");

	if(strstr(local_url, "list")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		if(atoi(option)<=0){
			friends(1,"1");
			return -1;
		}
		friends(1,option);
	}else if(strstr(local_url, "detail")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		if(atoi(option)<=0){
			friends(2,"1");
			return -1;
		}
		friends(2,option);
	}else if(strstr(local_url, "search")){
		option = strtok(local_url,"=");
		option = strtok(NULL," ");
		if(option==NULL){
			friends(1, "1");
			return -1;
		}
		friends(3,option);
	}else if(strstr(local_url, "addValue")){
		option = strtok(local_url,"=");
		option = strtok(NULL, " ");
		friends_rdwr(1, option);
	}else if(strstr(local_url, "name")){
		friends_rdwr(2,local_url);
	}else{
		printf("Error... reset page...<br>");
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

	sprintf(Buf,
			"%s"
			"<div align=\"center\">"
			"<form action=\"./fr.cgi\" method=\"get\">"
			"<input type=\"search\" name=\"search\">"
			"<input type=\"submit\" value=\"Search\"> </form> </div>"
			"<h5 align=\"center\"> #%d &nbsp </h5>"
			, header,opt
		   );

	printf("%s\n", Buf);


	// 1 Show Friends List
	if(select == 1){
		sprintf(Buf,
			"<div align=\"center\">"
			"<a href=\"./fr.cgi?list=%d\"><button> Pre </button></a>&nbsp"
			"<a href=\"./fr.cgi?list=%d\"><button> &#9829 </button></a>&nbsp"
			"<a href=\"./fr.cgi?list=%d\"><button> Next</button></a>"
			"</div>"
			, opt-1, opt ,opt+1
			);
		printf("%s\n", Buf);
		for(int i=LIST_NUM*(opt-1); i<LIST_NUM*opt; i++){
			lseek(frifd, i*sizeof(fr), SEEK_SET);
			if(read(frifd, &fr, sizeof(fr))<=0){
				break;
			}
			else{
				sprintf(content,"%s / %s\n", fr.name, fr.phone);
				sprintf(Buf, "<p>[%03d] <a href=\"./fr.cgi?detail=%d\"> %s </a> </p>", i+1, i+1, content);
				printf("%s\n", Buf);
			}
		}
	}

	// 2 Show Detail
	else if(select == 2){
		lseek(frifd, (opt-1)*sizeof(fr), SEEK_SET);
		read(frifd, &fr, sizeof(fr));
		sprintf(Buf,
				"<div align=\"center\">"
				"<a href=\"./fr.cgi?detail=%d\"><button> Pre </button></a>&nbsp"
				"<a href=\"./fr.cgi?list=%d\"><button> &#9829 </button></a>&nbsp"
				"<a href=\"./fr.cgi?detail=%d\"><button> Next</button></a>"
				"</div>"
				, opt-1, HOME,opt+1
			   );
		printf("%s\n", Buf);

		sprintf(Buf, "<h2>Name: %s</h2>Age: %d<br>Phone: %s<br>E-mail: %s<br>Address: %s<br>Favorite: %d<br>"
				, fr.name, fr.age, fr.phone, fr.email,fr.address, fr.flag);
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


	int endNum;
	endNum = lseek(frifd, 0, SEEK_END)/sizeof(fr);

//	printf("opt : %d<br>end : %d<br>",opt,endNum);


	sprintf(Buf, 
			"<a href=\"./fr.cgi?addValue%d\">"
			"<button> add </button> <br>"
			"</a>"
			,endNum+1
			);
	printf("%s\n", Buf);
	printf("%s\n", end);

	close(frifd);
	return 0;
}

int friends_rdwr(int select, char *option)
{
	int frifd, th, opt;
	char buf[MAX], *ptrOpt, *ptrValue;
	char *menu[5]={"name", "age", "phone", "email", "address"};
	FRIEND_T fr;

	if((frifd=open(DATA, O_WRONLY, 0755))==-1){
		printf("open failed\n");
		return -1;
	}

	sprintf(buf,"%s",header);
	printf("%s", buf);
	
	
	// add form 
	if(select==1){
		opt = atoi(option);
		th = lseek(frifd, 0, SEEK_END)/sizeof(fr)+1;

		sprintf(buf,
//				"%s"
				"<h5 align=\"center\"> #%d &nbsp </h5>"
				"<form action=\"./fr.cgi\" method=\"get\">"
				,opt
			   );
		printf("%s", buf);

		printf("th : %d<br>", th);
		for(int i=0;i<5;i++){
			sprintf(buf,
					"%s<br>"
					"<input type=\"text\" name=\"%s\"><br>",menu[i],menu[i]);
			printf("%s\n",buf);
		}
		
		sprintf(buf, "<input type=\"submit\" value=\"submit\"> </form>");
		printf("%s", buf);

	// add input
	}else if(select == 2){
//		ptrOpt = option;
		for(int i=0;i<5;i++){
			ptrOpt = option;

			for(int j=0;j<i;j++){
				ptrOpt=strtok(ptrOpt,"&");
				ptrOpt=strtok(NULL,"&");
				ptrOpt=strtok(NULL,"&");
			}

			printf("ptrOpt : %s<br>",ptrOpt);
			ptrOpt = strtok(ptrOpt,"&");
			ptrValue = strtok(ptrOpt,"=");
			ptrValue = strtok(NULL,"=");
			printf("&nbsp ptrOpt : %s<br>&nbsp ptrValue : %s<br>", ptrOpt,ptrValue);
/*
			ptrOpt=option;
			ptrOpt = strtok(ptrOpt, "&");
			ptrOpt = strtok(NULL, "=");
*/

			printf("<br>");
		}

	}



	printf("%s\n", end);
	close(frifd);
	return 0;
}

