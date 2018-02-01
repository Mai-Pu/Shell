#include<stdio.h>
#include<pthread.h>

#define length 20000
#define cpu 5

struct task{
	int start;
	int end;
};

void *compute(void *arg)
{
	struct task *task;
	float* result;
	result = malloc(sizeof(float));
	*result = 0;
	int i;
	task = (struct task *)arg;
	for(i=task->start;i<task->end;i++)
	{
		if(i%2==0)
			*result += 1.0/(2*i+1);
		else
			*result -= 1.0/(2*i+1);
	}
	return result;
}

int main()
{
	pthread_t workers[cpu];
    struct task tasks[cpu];
    int i;

    for (i = 0; i < cpu; i++) { 
        struct task *task;
        task = &tasks[i]; 
        task->start = i * length/cpu;	
        task->end = (i + 1) * length/cpu;
        pthread_create(&workers[i], NULL, compute, task); 
    }

    float sum = 0;
    for (i = 0; i < cpu; i++) { 
        float *result;
        pthread_join(workers[i], (void **)&result); 
        sum += *result; 
		free(result);
    }

    printf("sum = %f\n", sum); 
    return 0;
}