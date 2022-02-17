#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int encode(char *url)
{
	char *ptr;
	char buf[1024];
	
	bzero(buf, sizeof(buf));

	for(ptr=url; *ptr; ptr++){
		if(isalpha(*ptr) || isdigit(*ptr)){
			*(buf+strlen(buf))=*ptr;
//			*(url+strlen(url)) = *ptr;
		}else{
			sprintf(buf+strlen(buf),"%%%02X", *ptr);
//			sprintf(url, "%%%02X", *ptr);
		}

	}

	return 0;

}

int main(int argc, char **argv)
{
	char *string;
	char buf[1024];

	if(argc<2) return -1;

	bzero(buf, sizeof(buf));
	string = argv[1];
	strcpy(buf, string);

	encode(buf);

	printf("%s ---> %s\n", string, buf);

	return 0;

}
