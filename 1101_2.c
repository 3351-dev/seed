#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 64

void readLine(int fd, char *buf, int bufsize);
//void spaceFinder();


int main()
{
	char first[SIZE], second[SIZE], third[SIZE];
	char buf[256];
//	int *ptr[3];


	while(1){
		int i=0,j=0;
		readLine(0,buf,sizeof(buf));

		bzero(first,sizeof(first));
		bzero(second, sizeof(second));
		bzero(third, sizeof(third));

		printf("readLine : %s\n", buf);
//FIRST
		for(;buf[i]==' ';i++);
		for(j=0;buf[i];i++){
			if(buf[i]!=' '){
				first[j] = buf[i];
				j++;
			}else
				break;
		}
		if(!strcmp(first, "quit"))
			exit(0);
//SECOND
		for(;buf[i]==' ';i++);
		for(j=0;buf[i];i++){
			if(buf[i]!=' '){
				second[j]=buf[i];
				j++;
			}else
				break;
		}
//THIRD
		for(;buf[i]==' ';i++);
		for(j=0;buf[i];i++){
			if(buf[i]!=' '){
				third[j]=buf[i];
				j++;
			}else break;
		}

		printf("1:[%s], 2:[%s], 3:[%s]\n", first, second, third);
	}
}

void readLine(int fd, char *buf, int bufsize)
{
	char c;

	bzero(buf, bufsize);

	for(int i=0;;i++){
		read(fd, &c, 1);
		if(c=='\n')
			break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
}

/*
int spaceFinder(int i,char *buf, char *arr[])
{
	int j=0;
	for(;buf[i];i++){
		if(buf[i]!=' ');
		arr[j] = buf[i];
		j++;
	}else{
		break;
	}
	return *arr;
}
*/
