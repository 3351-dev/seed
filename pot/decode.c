#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decode(char *url)
{
	char *t;
	for(t=url; *url; t++){
		if(*url=='%'){
			char *eptr = url+3;
			*t=strtol(url+1, &eptr, 16);
			url+=3;
		}else *t=*(url++);
	}
	*t=0l;

	return 0;
}


int main(int argc, char **argv)
{
//	char *string="%26%2344032%3B%26%2345208%3B%26%2345796%3B%26%2346972%3B";	
//	char *string = "%EA%B9%80%EC%84%9C%EC%98%81";	//김서영
	char *string ="%26%2351312%3B%26%2344228%3B%26%2354788%3B";	//조계현
	char buf[1024];

	bzero(buf, sizeof(buf));
	strcpy(buf, string);
	decode(buf);

	printf("%s --> %s\n", string, buf);	
	return 0;
}
