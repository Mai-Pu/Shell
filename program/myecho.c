#include <stdio.h>
void main(int argc,char *argv[])
{
	while(argc > 1)
	{
		argv++;
		printf("%s",*argv);
		argc--;
		if(argc == 1)
			printf("\n");
		else
			printf(" ");
	}
}