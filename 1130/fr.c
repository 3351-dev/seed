#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>

#include "friend.h"

#define LIST_NUM 15
#define MAX 1024
#define DATA "1109.dat"
#define HOME (((opt-1)/LIST_NUM)+1)

char header[] ={ 
//			"<!DOCTYPE html> <html lang=\"ko\"> <head> <title> Fr </title> </head>"
			"<html lang=\"ko\"> <head>"
			"<meta charset=\"utf-8\"> <title> Home Fr </title></head>"
			// meta charset을 해줘야 페이지에서 한글로 잘 표기된다
			"<body> <h1 align=\"center\"> Friends List &nbsp </h1>"
};
char end[]={
			"</body></html>"
};

int friends(int select, char *option);
int friends_rdwr(int select, char *option);
int decode_url(char *url);
int upload();
int upload_page(char *option);


int main(int argc, char **argv)
{
	char *local_url, *option, *method;

	printf("Content-type: text/html\n\n");
	method = getenv("REQUEST_METHOD");

	if(strcmp(method,"POST")==0){
		upload();
	}else{
		local_url = getenv("QUERY_STRING");
	}
	
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
		
	}else if(strstr(local_url, "upload_page")){
		option = strtok(local_url,"=");
		option = strtok(NULL, " ");
		upload_page(option);
		
	}else{
		/*
		printf("Error... reset page...<br>");
		friends(1,"1");
		*/
	}
	return 0;
}

int friends(int select, char *option)
{	
	int frifd, opt;
	char Buf[MAX*10], content[MAX];
	FRIEND_T fr;

	strcpy(Buf, option);
	decode_url(Buf);

	if((frifd=open(DATA, O_RDONLY))==-1){
		printf("non open failed\n");
		return -1;
	}
	opt = atoi(option);

	sprintf(Buf,
			"%s"
			"<div align=\"center\">"
			"<form action=\"./fr.cgi\" accept-charset=\"utf-8\" method=\"get\">"
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
			"<a href=\"./fr.cgi?list=%d\"><button> Next</button></a><br>"
//			"<a href=\"./fr.cgi?upload_page=%d\"><button> Upload </button></a>"
			"</div>"
			, opt-1, 1 ,opt+1
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

		printf("<table>");
		// Print Picture
//		printf("<img src=\"../img/img.jpg\"><br>");
		printf("<td>");
		sprintf(Buf, "<img src=\"../img/%d.jpg\"><br>",opt);
		printf("%s",Buf);
		printf("</td>");

		printf("<td>");
		sprintf(Buf, "<h2>Name: %s</h2>Age: %d<br>Phone: %s<br>E-mail: %s<br>Address: %s<br>Favorite: %d<br><br>"
				, fr.name, fr.age, fr.phone, fr.email,fr.address, fr.flag);
		printf("%s\n", Buf);
		printf("</td> </table>");
		
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
			"<a href=\"./fr.cgi?addValue=%d\">"
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
	char buf[MAX], temp[MAX], *ptrTemp;
	char *menu[5]={"name", "age", "phone", "email", "address"};
	char value[5][MAX];
	FRIEND_T fr;

	strcpy(buf, option);
	decode_url(buf);

	if((frifd=open(DATA, O_WRONLY))==-1){
		printf("rdwr open failed\n");
		return -1;
	}

	sprintf(buf,"%s",header);
	printf("%s", buf);
	
	
	// 1 add form 
	if(select==1){
		opt = atoi(option);
		th = lseek(frifd, 0, SEEK_END)/sizeof(fr)+1;

		sprintf(buf,
				"<h5 align=\"center\"> #%d &nbsp </h5>"
				"<form action=\"./fr.cgi\" accept-charset=\"utf-8\" method=\"get\">"
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
		printf("<br>");
		
		sprintf(buf, "<input type=\"submit\" value=\"submit\"> </form>");
		printf("%s", buf);
		/*
		// 사진 업로드 PHP
		sprintf(buf,
				"<form action=\"./upload.php\" method=\"post\" enctype=\"multipart/form-data\">"
				"<input tpye=\"text\" name=\"option\" value=\"%s\" readonly<br>"
				"<input type=\"file\" name=\"file\" /> <br>"
				"<input type=\"submit\" value=\"submit\" /> &nbsp"
				"</form>"
				,option
			  );
		printf("%s", buf);
		*/

	// 2 add input
	}else if(select == 2){
		th = lseek(frifd, 0, SEEK_END)/sizeof(fr)+1;
		opt=th;

		lseek(frifd, 0, SEEK_END);
		read(frifd, &fr, sizeof(fr));

		for(int i=0;i<5;i++){
			strcpy(temp, option);
			ptrTemp = strtok(temp, "=");
			for(int j=0;j<i+1;j++){
				ptrTemp = strtok(NULL,"=");
			}
			ptrTemp = strtok(ptrTemp, "&");

			if(ptrTemp == NULL
					|| (strcmp(ptrTemp,"age")==0)
					|| (strcmp(ptrTemp,"phone")==0)
					|| (strcmp(ptrTemp,"email")==0)
					|| (strcmp(ptrTemp,"address")==0)
					){
				ptrTemp="NULL";
			}

			strcpy(value[i], ptrTemp);
		}

		for(int i=0;i<5;i++){
			decode_url(value[i]);
			printf("value[%d] : %s<br>",i,value[i]);
		}
		printf("<br>");

		strcpy(fr.name, value[0]);
		fr.age =atoi(value[1]);
		strcpy(fr.phone,value[2]);
		strcpy(fr.email, value[3]);
		strcpy(fr.address, value[4]);
	
		write(frifd, &fr, sizeof(fr));

		sprintf(buf,
				"<a href=\"./fr.cgi?upload_page=%d\">"
				"<button> ok  </button> <br>"
				"</a>"
				,opt);
		printf("%s",buf);
	}

	printf("%s\n", end);
	close(frifd);
	return 0;
}


int upload_page(char *option)
{
	char buf[MAX];

	sprintf(buf,
			"%s"
			"<div align=\"center\">"
			"<form action=\"./fr.cgi\" accept-charset=\"utf-8\" method=\"get\">"
			"<input type=\"search\" name=\"search\">"
			"<input type=\"submit\" value=\"Search\"> </form> </div>"
			, header
		   );
	printf("%s\n", buf);
	 
	sprintf(buf,
			"<form action=\"./upload.php\" method=\"post\" enctype=\"multipart/form-data\">"
			"<input tpye=\"text\" name=\"option\" value=\"%s\" readonly /><br>"
			"<input type=\"file\" name=\"file\" /> <br>"
			"<input type=\"submit\" value=\"submit\" /> &nbsp"
			"</form>"
			,option
		  );
	printf("%s", buf);


	printf("%s", end);

	return 0;

}

int upload()
{
	char buf[MAX*1000], *Len, *ptr;
	bzero(buf, sizeof(buf));

	Len = getenv("CONTENT_LENGTH");
	read(0, buf, atoi(Len));

	printf("%s", header);
	
//	printf("%s<br>", getenv("CONTENT_LENGTH"));
	printf("%s<br>",buf);
	printf("<br>");

	int i=0;
	ptr = buf;
	ptr = strtok(buf," ");
	while(i<5){
		ptr = strtok(NULL," ");
		printf("ptr : %s<br>", ptr);
		i++;
	}
	printf("<br>");

	ptr = strtok(NULL,"image/jpeg");
	printf("ptr : %s<br>", ptr);
	printf("ptr length : %ld<br>", strlen(ptr));

	printf("<p> hello </p>");
	printf("%s", end);

	return 0;
}

int decode_url(char *url)
{
	char *t;
	for(t=url;*url;t++){
		if(*url=='%'){
			char *eptr = url+3;
			*t=strtol(url+1, &eptr, 16);
			url+=3;
		}else if(*url =='+'){
			*t = ' ';
			url+=1;
		}else *t=*(url++);
	}
	*t=0l;

	return 0;
}		
