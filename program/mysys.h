#ifndef MYSYS_H
#define MYSYS_H
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int mysys(char *args)
{
	int pid = fork();
	if(pid == 0){
		char c[10] = {'/','b','i','n','/','s','h','\0'};
		execl(c,"sh","-c",args,NULL);
		exit(100);
	}
	wait(NULL);
	return 0;
}
#endif