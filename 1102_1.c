#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int readline(int fd, char *buf, int bufsize);

int main(int argc, char **argv)
{
	char buf[1024],*ptr;
	int fd;
	struct stat st;

// argc check
	if(argc<2){
		printf("argc failed\n");
		exit(1);
	}
// READ
	if((fd=open(argv[1],O_RDONLY))==-1){
		perror("open failed");
		exit(1);
	}

// STAT
	if(stat(argv[1], &st)==-1){
		perror("stat failed");
		exit(1);
	}

	read(fd, buf,sizeof(buf));
	ptr=buf;
	for(int i=0;;i++){
		char *nullfinder=strchr(ptr,'\n');
		if(nullfinder)
			*nullfinder=0;
		else	break;
//		printf("%2d %s\n", i+1, ptr);
//		split_word(i,ptr);
		for(int j=0;;j++){
			char *spaceFinder=strchr(ptr,' ');
			if(spaceFinder){
				*spaceFinder=0;
			}
			/*
			   *ptr == 0일때 file 한줄이 비어있으면 segmentation오류를 발생시키므로
			   && spaceFiner를 추가하여 정상작동하게 하였다.
			*/
			if(*ptr==0 && spaceFinder){
				ptr=spaceFinder+1;
				j--;
				continue;
			}
			


//			printf("SpaceFinder : %c\n",*(spaceFinder+1));

			printf("%2d_%d[%s]\t",i+1,j+1,ptr);
			if(spaceFinder){
				ptr=spaceFinder+1;
			}
			else{
				printf("\n");
				break;
			}
		}
		if(nullfinder)
			ptr=nullfinder+1;
		else
			break;
	}

	close(fd);
	printf("sol\n");
	exit(0);

}



int readline(int fd, char *buf, int bufsize)
{
	char c;
	int i, rc;

	bzero(buf, bufsize);

	for(i=0;;i++){
		rc = read(fd, &c, 1);
		if(rc<=0||c=='\n')
			break;
		if(i<(bufsize-1))
			*(buf+i)=c;
	}
	return i;
}
