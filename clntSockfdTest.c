#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int argc);


int main(int argc, char **argv)
{
	int fds[256] = {-1, };

	// fds init
	for(int i=0;i<256;i++){
		fds[i] = -1;
	}
	
	// atoi
	for(int i=0;i<argc-1;i++){
		fds[i] = atoi(argv[i+1]);
	}

	print_array(fds, argc);

	for(int i=0;i<argc-1;i++){
		for(int j=i+1;j<argc-1;j++){
			if(fds[i]==fds[j]){
				fds[i] = -1;
				fds[j] = -1;
			}
		}
	}

	for(int i=0;i<argc-1;i++){
		if(fds[i] == -1){
			for(int j=i;j<sizeof(fds)/sizeof(int)-1;j++){
				fds[j] = fds[j+1];
			}
		}
		if(fds[0] == -1)
			i--;
	}
	print_array(fds, argc);
}

void print_array(int *arr, int argc)
{
	for(int i=0;i<argc;i++){
		printf("%2d ",arr[i]);
		if(arr[i]==-1){
			break;
		}
	}
	printf("\n");
}
