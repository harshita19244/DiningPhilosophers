#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdbool.h>

typedef struct my_semaphore{
	pthread_mutex_t lock;
    pthread_cond_t cond_var;
    int value;
    
    
}my_semaphore;

struct arg_struct {
    int index;
    int num;
};

void pthread_sem_init(struct my_semaphore *s, int count);
void P_wait(struct my_semaphore *s);
void V_signal(struct my_semaphore *s);

void pthread_sem_init(struct my_semaphore *s, int count)
{
        
        s->value = count;
        pthread_cond_init(&(s->cond_var),NULL);
        pthread_mutex_init(&(s->lock),NULL);
        return;

  }      

void wait(struct my_semaphore *s)
{
        pthread_mutex_lock(&(s->lock));
        s->value--;
        if(s->value <= 0) {
			pthread_cond_wait(&(s->cond_var),&(s->lock));
        }
        pthread_mutex_unlock(&(s->lock));
        return;
}

void signal(struct my_semaphore *s)
{

        pthread_mutex_lock(&(s->lock));
        s->value++;
        if(s->value <= 0) {
                pthread_cond_signal(&(s->cond_var));
        }
        pthread_mutex_unlock(&(s->lock));
}

void signal_print(struct my_semaphore *s){
	    pthread_mutex_lock(&(s->lock));
        printf("Semaphore value:%d\n",s->value);
        pthread_mutex_unlock(&(s->lock));
}

sem_t resources[20];
struct my_semaphore entry;

int max(int num1,int num2);
int min(int num1,int num2);


bool flag=true;

void philo_decide(int d,int num){
  wait(&entry);
  //signal_print(&entry);
  int a=min(d,(d+1)%num);
  int b=max(d,(d+1)%num);
  printf("Philosopher %d has entered room\n",d+1);
  sem_wait(&resources[a]);
  sem_wait(&resources[b]);
  
  printf("Philosopher%d eats using forks F%d,F%d\n",d+1,a,b);
  printf("P%d receives pair of bowls\n",d+1);
  
  sleep(2);
  
  sem_post(&resources[b]);
  sem_post(&resources[a]);
  
  signal(&entry);
  
}


void* philo (void* ptr){
	struct arg_struct *args = (struct arg_struct *)ptr;
	int i = args->index;
	int num= args->num; 
 	sleep(1); 
  	philo_decide(i,num); 
 }

int max(int num1,int num2){
	if(num1>num2){
		return num1;
	}
	else{
		return num2;
	}
}

int min(int num1,int num2){
	if(num1<num2){
		return num1;
	}
	else{
		return num2;
	}
}


int main(){

	int i,num;
	struct arg_struct args;
	printf("Enter number of philosophers: ");
	scanf("%d",&num);
	pthread_t id[num];
	args.num=num;
	int phil_index[num];

	for(i=0;i<num;i++){
		sem_init(&resources[i],0,1);
		phil_index[i]=i;
	}


    pthread_sem_init(&entry,num);
    while(1){
    	for(i=0;i<num;i++){
    	args.index=i;	
		pthread_create(&id[i],NULL,philo,&args);
	}
    }
	

	for(i=0;i<num;i++){
		pthread_join(id[i],NULL);
	}

	
}