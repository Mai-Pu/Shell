#include<stdio.h>
#include<pthread.h>

#define length 4

char buffer1[length];
char buffer2[length];
int in1=0;
int out1=0;
int size1=0;
int in2=0;
int out2=0;
int size2=0;

pthread_mutex_t mutex1;
pthread_cond_t wait_empty_buffer1;
pthread_cond_t wait_full_buffer1;

pthread_mutex_t mutex2;
pthread_cond_t wait_empty_buffer2;
pthread_cond_t wait_full_buffer2;


void* producer(void *arg)
{
	int i;
    char item;
    for (i = 0; i < length*2; i++) {
       pthread_mutex_lock(&mutex1);
        while (size1==length) 
            pthread_cond_wait(&wait_empty_buffer1, &mutex1);
        item = i + 'a';
		buffer1[in1] = item;
		in1 = (in1+1) % length;
		size1++;
        pthread_cond_signal(&wait_full_buffer1);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

void* calculator(void *arg)
{
	int i;
    for (i = 0; i < length*2; i++) {
       pthread_mutex_lock(&mutex1);
	   pthread_mutex_lock(&mutex2);
	   while(size1==0)
			pthread_cond_wait(&wait_full_buffer1, &mutex1);
       while(size2 == length)
			pthread_cond_wait(&wait_empty_buffer2, &mutex2);
		buffer2[in2] = buffer1[out1]-32;
		out1 = (out1+1) % length;
		in2 = (in2+1) % length;
		size2++;
		size1--;
        pthread_cond_signal(&wait_full_buffer2);
		pthread_cond_signal(&wait_empty_buffer1);
        pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void* consumer(void *arg)
{
	int i;
    char item;
    for (i = 0; i < length*2; i++) {
        pthread_mutex_lock(&mutex2);
        while (size2==0)
            pthread_cond_wait(&wait_full_buffer2, &mutex2);

        item = buffer2[out2];
		out2 = (out2+1)%length;
		size2--;
        printf("consume item: %c\n", item);
        pthread_cond_signal(&wait_empty_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

int main()
{
	pthread_t producer_tid;
	pthread_t calculator_tid;
    pthread_t consumer_tid;
	

    pthread_mutex_init(&mutex1, NULL);
    pthread_cond_init(&wait_empty_buffer1, NULL);
    pthread_cond_init(&wait_full_buffer1, NULL);
	
	pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&wait_empty_buffer2, NULL);
    pthread_cond_init(&wait_full_buffer2, NULL);
	
	pthread_create(&consumer_tid, NULL, consumer, NULL);
	pthread_create(&calculator_tid, NULL, calculator, NULL);
	pthread_create(&producer_tid, NULL, producer, NULL);

	pthread_join(consumer_tid, NULL);
	pthread_join(calculator_tid, NULL);
	pthread_join(producer_tid, NULL);
	
	pthread_mutex_destroy(&mutex1);
	pthread_cond_destroy(&wait_empty_buffer1);
	pthread_cond_destroy(&wait_full_buffer1);
	pthread_mutex_destroy(&mutex2);
	pthread_cond_destroy(&wait_empty_buffer2);
	pthread_cond_destroy(&wait_full_buffer2);
    return 0;
}
 
