#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	if(argc == 3)
	{
		argv++;
		int fr;
		int fw;
		fr = open(*argv,O_RDONLY);
		argv++;
		fw = open(*argv,O_RDWR|O_CREAT,0777);
		char c;
		while(read(fr,&c,1))
			write(fw,&c,1);
		close(fr);
		close(fw);
	}
	else
	{
		printf("cuowu");
	}
}