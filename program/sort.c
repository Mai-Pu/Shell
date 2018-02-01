#include<stdio.h>
#include<pthread.h>

#define num_length 10
int num[num_length] = {10,2,3,5,4,2,8,55,20,10};

void* worker(void *arg)
{
	int i;
	int j;
	for(i = 0;i < num_length-1-num_length/2;i++)
		for(j = num_length/2;j < num_length-1-i ;j++)
			if(num[j] > num[j+1])
			{
				int mid = num[j+1];
				num[j+1]=num[j];
				num[j]=mid;
			}
	return NULL;
}

int main()
{
	pthread_t worker_tid;
	pthread_create(&worker_tid,NULL,&worker,NULL);
	int i;
	int j;
	for(i = 0;i < num_length/2-1;i++)
		for(j = 0;j < num_length/2-1-i ;j++)
			if(num[j] > num[j+1])
			{
				int mid = num[j+1];
				num[j+1]=num[j];
				num[j]=mid;
			}
			
	pthread_join(worker_tid,NULL);
	//归并排序
	int tem[num_length];
	i = 0;
	j = num_length/2;
	int k = 0;
	

	for(;j<num_length&&i<num_length/2;)
	{
		if(num[i] > num[j])
		{
			tem[k]=num[j];
			j++;
			k++;
		}else{
			tem[k]=num[i];
			i++;
			k++;
		}
	}
	while(i<num_length/2)
	{
		tem[k]=num[i];
		i++;
		k++;
	}
	while(j<num_length)
	{
		tem[k]=num[j];
		j++;
		k++;
	}
	for(k=0;k<num_length;k++)
	{
		num[k]=tem[k];
		printf("%d ",num[k]);
	}
	puts("");
	return 0;
}