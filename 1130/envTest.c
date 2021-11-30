#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *local_url;
	printf("Content-type: text/html\n\n");

	printf("<!DOCTYPE html> <html> <head> <title> Env Test </title> </head>"
			"<body> <h1> Env Test </h1> <p>");

	local_url = getenv("QUERY_STRING");
	printf("local url : %s\n",local_url);

	printf("</p> </body> </html>\n");

	return 0;
}
