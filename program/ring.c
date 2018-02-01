#include<stdio.h>
#include<pthread.h>

#define cpu 20

int count;
pthread_cond_t cond;
pthread_mutex_t mutex;
void *ring(void *arg)
{
	int *result = (int *)arg;
	pthread_t rings;
	*result += 1;
	count++;
	if(count == 1)
	{
		pthread_create(&rings, NULL, ring, result);
		pthread_cond_wait(&cond, &mutex);
	}
	else if(count < cpu)
	{
		pthread_create(&rings, NULL, ring, result);
		
	}		
	else if(count == cpu)
	{
		pthread_cond_signal(&cond);
	}
	return result;
}

int main()
{
	int *result = (int *)malloc(sizeof(int));
	*result = 0;
	pthread_t rings_1;
    int i;

	count=0;
	pthread_create(&rings_1, NULL, &ring, result); 
	pthread_join(rings_1,(void**)&result);
    printf("result = %d\n", *result); 
    return 0;
}