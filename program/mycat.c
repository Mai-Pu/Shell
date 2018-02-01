#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	int txt = -1;
	int i;
	char st;
	while(argc>1)
	{
		argv++;
		argc--;
		txt = open(*argv,O_RDONLY|O_CREAT);
		if(txt != -1)
		{
			while(read(txt,&st,1))
				printf("%c",st);
			close(txt);
		}
		else
			printf("wenjianbucunzai");
	}
	return 0;
}