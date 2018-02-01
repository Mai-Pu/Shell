#include<stdio.h>
#include<pthread.h>

#define length 4

typedef struct{
	int value;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}sema_t;

void sema_init(sema_t *sema,int value)
{
	sema->value = value;
	pthread_mutex_init(&sema->mutex,NULL);
	pthread_cond_init(&sema->cond,NULL);
}

void sema_wait(sema_t *sema)
{
	pthread_mutex_lock(&sema->mutex);
    sema->value--;
    while (sema->value < 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    pthread_mutex_unlock(&sema->mutex);;
}

void sema_signal(sema_t *sema)
{
	pthread_mutex_lock(&sema->mutex);
    sema->value++;
	if(sema->value <= 0)
		pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

char buffer1[length];
char buffer2[length];
int in1=0;
int out1=0;
int size1=0;
int in2=0;
int out2=0;
int size2=0;


sema_t mutex1_sema;
sema_t empty_buffer1_sema;
sema_t full_buffer1_sema;

sema_t mutex2_sema;
sema_t empty_buffer2_sema;
sema_t full_buffer2_sema;


void* producer(void *arg)
{
	int i;
    char item;
    for (i = 0; i < length*2; i++) {
		sema_wait(&empty_buffer1_sema);
		sema_wait(&mutex1_sema);
        item = i + 'a';
		buffer1[in1] = item;
		in1 = (in1+1) % length;
        sema_signal(&mutex1_sema);
		sema_signal(&full_buffer1_sema);
    }
    return NULL;
}


void* calculator(void *arg)
{
	int i;
    for (i = 0; i < length*2; i++) {
        sema_wait(&full_buffer1_sema);
		sema_wait(&empty_buffer2_sema);
		sema_wait(&mutex1_sema);
		sema_wait(&mutex2_sema);
		buffer2[in2] = buffer1[out1]-32;
		out1 = (out1+1) % length;
		in2 = (in2+1) % length;
		sema_signal(&mutex2_sema);
		sema_signal(&mutex1_sema);
		sema_signal(&full_buffer2_sema);
		sema_signal(&empty_buffer1_sema);
    }
    return NULL;
}

void* consumer(void *arg)
{
	int i;
    char item;
    for (i = 0; i < length*2; i++) {
		sema_wait(&full_buffer2_sema);
		sema_wait(&mutex2_sema);
        item = buffer2[out2];
		out2 = (out2+1) % length;

		sema_signal(&mutex2_sema);
		sema_signal(&empty_buffer2_sema);
		printf("consumer:%c\n",item);
    }
    return NULL;
}


int main()
{
	pthread_t producer_tid;
	pthread_t calculator_tid;
    pthread_t consumer_tid;

    sema_init(&mutex1_sema,1);
    sema_init(&empty_buffer1_sema,length);
    sema_init(&full_buffer1_sema,0);
	sema_init(&mutex2_sema,1);
    sema_init(&empty_buffer2_sema,length);
    sema_init(&full_buffer2_sema,0);
	
	pthread_create(&consumer_tid, NULL, consumer, NULL);
	pthread_create(&calculator_tid, NULL, calculator, NULL);
	pthread_create(&producer_tid, NULL, producer, NULL);

	pthread_join(consumer_tid, NULL);
	pthread_join(calculator_tid, NULL);
	pthread_join(producer_tid, NULL);

    return 0;
}
 
