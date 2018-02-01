#include<stdio.h>
#include<pthread.h>
#define length 200000

float worker_output;
float master_output;

void *worker(void *arg)
{
	worker_output = 0;
	int i;
	for(i=length/2;i<length;i++)
	{
		if(i%2==0)
			worker_output += 1.0/(2*i+1);
		else
			worker_output -= 1.0/(2*i+1);
	}
}
int main()
{
	pthread_t worker_tid;
	float sum;
	
	pthread_create(&worker_tid,NULL,worker,NULL);
	master_output = 0;
	int i;
	for(i=0;i<length/2;i++)
	{
		if(i%2==0)
			master_output += 1.0/(2*i+1);
		else
			master_output -= 1.0/(2*i+1);
	}
	pthread_join(worker_tid,NULL);
	sum = master_output + worker_output;
	
	printf("master = %f , worker = %f , sum = %f",master_output,worker_output,sum);
}