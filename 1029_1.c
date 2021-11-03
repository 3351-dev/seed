#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	char *ptr, *buff;
	struct stat st;

	//OPEN
	if((fd=open(argv[1], O_RDONLY))==-1){
		perror("ERR : ");
		exit(1);
	}

	//STAT
	if(stat(argv[1], &st)==-1){
		perror("ERR : ");
		exit(1);
	}

	// SIZE : st.st_size
	printf("file size : %ld\n",st.st_size);
	buff=(char *)malloc(st.st_size);
	ptr=buff;


	//READ
	read(fd, ptr, st.st_size-1);
	
	//PRINT
	for(int i=0;;i++){
		char *nullFinder= strchr(ptr,'\n');
		if(nullFinder)
			*nullFinder=0;
		printf("%2d %s\n",i+1,ptr);
		if(nullFinder)
			ptr=nullFinder+1;
		else 
			break;

	}

	close(fd);
	free(buff);
	printf("sol\n");
	exit(0);

}

