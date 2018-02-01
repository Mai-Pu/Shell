#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

#define MAX_ARG 1024
#define NUM_ARG 5

char path[1024];
int out_f = -1;
int in_f = -1;

char** read_command(char *cmd){
	int num_a = NUM_ARG;
	char **arglist = (char**)malloc(num_a * sizeof(char*));
	int i = 0;
	int j = 0;
	int now = 0;
	while(i < strlen(cmd))
	{
		if(cmd[i] == ' ')
		{
			i++;
			continue;
		}
		if(cmd[i] == '"')
		{
			for(j =i+1; j < strlen(cmd);j++)
			{
				if(cmd[j] == '"')
					break;
			}
			if(j<strlen(cmd))
			{
				if(j==(i+1))
					arglist[now] = "";
				else
				{
					arglist[now] = (char*)malloc((j-i)*sizeof(char));
					int mi_1;
					for(mi_1 = i+1;mi_1 < j;mi_1++)
					{
						arglist[now][mi_1-i-1] = cmd[mi_1];
					}
					arglist[now][j-i-1] = '\0';
					now++;
				}
			}
			else
			{
				puts("the lack of right quote!");
				exit(0);
			}
		}
		else
		{
			for(j = i; j < strlen(cmd);j++)
			{
				if(cmd[j] == ' ')
					break;
				if(cmd[j] == '>')
					break;
				if(cmd[j] == '<')
					break;
			}
			if(j>i)
			{
				arglist[now] = (char*)malloc((j-i+1)*sizeof(char));
				int mi_2;
				for(mi_2 = i;mi_2 < j;mi_2++)
				{
					arglist[now][mi_2-i] = cmd[mi_2];
				}
				arglist[now][j-i] = '\0';
				now++;
			}
			if(cmd[j] == '>')
			{
				char* out_file;
				i=j+1;
				for(;i<strlen(cmd);i++)
					if(cmd[i]!=' ')
						break;
						
				for(j=i;j < strlen(cmd);j++)
					if(cmd[j] == ' ')
						break;
				if(j == i)
				{
					puts("error:>");
					exit(0);
				}
				out_file = (char*)malloc((j-i+1)*sizeof(char));
				int mi_4 = 0;
				for(mi_4 = i;mi_4<j;mi_4++)
					out_file[mi_4-i] = cmd[mi_4];
				out_file[mi_4] = '\0';
				out_f = open(out_file,O_CREAT|O_RDWR|O_APPEND,0666);
				free(out_file);
			}
			if(cmd[j] == '<')
			{
				char* in_file;
				i=j+1;
				for(;i<strlen(cmd);i++)
					if(cmd[i] != ' ')
						break;
						
				for(j=i;j<strlen(cmd);j++)
					if(cmd[j] == ' ')
						break;
				if(j == i)
				{
					puts("error:<");
					exit(0);
				}
				in_file = (char*)malloc((j-i+1)*sizeof(char));
				int mi_5=0;
				for(mi_5 = i;mi_5<j;mi_5++)
					in_file[mi_5-i] = cmd[mi_5];
				in_file[mi_5] = '\0';
				in_f = open(in_file,O_CREAT|O_RDWR|O_APPEND,0666);
				free(in_file);
			}
		}
		
		i = j+1;
		if(now >= num_a)
		{
			char **mid = arglist;
			num_a +=NUM_ARG;
			arglist = (char**)malloc(num_a *sizeof(char*));
			int mi_3;
			for(mi_3 = 0;mi_3 < now ; mi_3++)
			{
				arglist[mi_3] = (char*)malloc((strlen(mid[mi_3])+1)*sizeof(char));
				strcpy(arglist[mi_3],mid[mi_3]);
			}
			free(mid);
		}
	}
	arglist[now] = NULL;
	return arglist;
}

void command_run(char **com_list)
{
		if(com_list[0] == NULL)
			return;
		else if(strcmp(com_list[0],"pwd")==0)
		{
			if(out_f != -1)
			{
				dup2(out_f,fileno(stdout));
				close(out_f);
			}
			puts(path);
			exit(0);
		}
		else if(strcmp(com_list[0],"cd") == 0)
		{
			if(com_list[1][0] == '~')
			{
					if(strlen(com_list[1])==1)
					{
						free(com_list[1]);
						com_list[1] = getenv("HOME");
					}
					else
					{
						char *p = (char*)malloc(strlen(com_list[1])*sizeof(char));
						int mid = 1;
						for(;mid < strlen(com_list[1]);mid++)
						{
							p[mid-1] = com_list[1][mid];
						}
						p[mid-1] = '\0';
						free(com_list[1]);
						com_list[1] = strcat(getenv("HOME"),p);
						free(p);
					}
			}
			chdir(com_list[1]);
		}
		else
		{
			if(out_f != -1)
			{
				dup2(out_f,fileno(stdout));
				close(out_f);
			}
			if(in_f != -1)
			{
				dup2(in_f,fileno(stdin));
				close(in_f);
			}
			execvp(com_list[0],com_list);
		}
}

char** read_command_1(char*cmd){
	int num_a = NUM_ARG;
	char **arglist = (char**)malloc(num_a * sizeof(char*));
	int i = 0;
	int j = 0;
	int now = 0;
	while(i < strlen(cmd))
	{
		for(j =i+1; j < strlen(cmd);j++)
		{
			if(cmd[j] == '|')
				break;
		}
		if(j>i)
		{
			arglist[now] = (char*)malloc((j-i+1)*sizeof(char));
			int mi_2;
			for(mi_2 = i;mi_2 < j;mi_2++)
			{
				arglist[now][mi_2-i] = cmd[mi_2];
			}
			arglist[now][j-i] = '\0';
			now++;		
		}
		
		i = j+1;
		if(now >= num_a)
		{
			char **mid = arglist;
			num_a +=NUM_ARG;
			arglist = (char**)malloc(num_a *sizeof(char*));
			int mi_3;
			for(mi_3 = 0;mi_3 < now ; mi_3++)
			{
				arglist[mi_3] = (char*)malloc((strlen(mid[mi_3])+1)*sizeof(char));
				strcpy(arglist[mi_3],mid[mi_3]);
			}
			free(mid);
		}
	}
	arglist[now] = NULL;
	return arglist;
}

int main()
{
	char **com_list;
	char buf[1024];
	while(1)
	{
		getcwd(path,1024);
		printf("my-shell:%s ",path);
		char cmd[MAX_ARG];
		int i = 0;
		char c;
		scanf("%c",&c);
		for(;i<1023&&c!='\n';i++){
			cmd[i]=c;
			scanf("%c",&c);
		}
		cmd[i] = '\0';
		com_list = read_command_1(cmd);
		if(strstr(com_list[0],"exit")!=NULL)
		{
			char **com_list_0 = read_command(com_list[0]);
			if(strcmp(com_list_0[0],"exit")==0)
			{
				free(com_list_0);
				free(com_list);
				exit(0);
			}
			free(com_list_0);
		}
		else if(strstr(com_list[0],"cd")!=NULL){
			char **com_list_0 = read_command(com_list[0]);
			if(strcmp(com_list_0[0],"cd")==0)
			{
				command_run(com_list_0);
				free(com_list_0);
				free(com_list);
				continue;
			}
			free(com_list_0);
		}
		for(i=0;com_list[i]!=NULL;i++){
			int p[2];
			pipe(p);
			if(fork()==0){
				if(com_list[i+1]!=NULL)
					dup2(p[1],1);
				if(i>0){
					int fd[2];
					pipe(fd);
					if(fork()==0){
						close(fd[0]);
						write(fd[1],buf,sizeof(char)*strlen(buf));
						close(fd[1]);
						exit(0);
					}
					else
					{
						close(fd[1]);
						dup2(fd[0],0);
						close(fd[0]);
						char **com_list_0 = read_command(com_list[i]);
						command_run(com_list_0);
						free(com_list_0);
						close(p[0]);
						close(p[1]);
						exit(0);
					}
				}else{
					char **com_list_0 = read_command(com_list[i]);
					command_run(com_list_0);
					free(com_list_0);
					close(p[0]);
					close(p[1]);
					exit(0);
				}
			}
			else {
				int buf0 = 0;
				for(;buf0 < 1024;buf0++)
					buf[buf0] = '\0';
				if(com_list[i+1]!=NULL){
					read(p[0],buf,sizeof(buf));
				}
				close(p[0]);
				close(p[1]);
				wait(NULL);
			}
		}
		free(com_list);
		if(out_f != -1)
		{
			close(out_f);
			out_f = -1;
		}
		if(in_f != -1)
		{
			close(in_f);
			in_f = -1;
		}
	}
}