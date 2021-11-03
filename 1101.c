#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int readline(int fd, char *buf, int bufsize);

int main()
{
	char buf[256];

	for(;;){
		readline(0,buf,sizeof(buf));
		printf("%s\n", buf);
		if(!strcmp(buf,"quit")){
			break;
		}
	}
}

int readline(int fd, char *buf, int bufsize)
{
	char c;
	int i, rc;

	bzero(buf,bufsize);

	for(i=0;;i++){
		rc=read(fd,&c,1);
		if(rc<=0 || c=='\n')
			break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
	return i;
}

