#include<iostream>
#include<semaphore.h>
#include<pthread.h>
using namespace std;
const int buffersize =10;


char buffer[buffersize];

int i=0,j=0;
sem_t sem1;
sem_t sem2;
int total=0;

void *writer(void *)
{
	while(true)
	{
		sem_wait(&sem1);
		int k=i;
		cin>>buffer[i];
		if(i==0 && k!=i)
		{
			buffer[0]=buffer[k];
		}
		
		/*
		The Purpose of above if statement:
			when a user enters an array each character that user entered
			is placed in array in an iteration.Suppose user entered 5 
			characters at first after placing 5 characters value of i will be 6
			as it is incremented after inserting character.Meanwhile writer will 
			signal reader to start reading wheres it will stay at line#21 to take
			input where value of i=6 so no matter reader decrements value of i
			it will read first character of user next input and store it on buffer[6].

			That's why i have placed that value where it should be means at 0 index.:) 
		*/
		i++;
		j=0;
		sem_post(&sem2);
	}
	
}
void *reader(void *)
{
	
	while(true)
	{
		sem_wait(&sem2);
 		
		cout<<buffer[j];
	
		j++;
		i--;
		
		if(i==0)
		{
			cout<<endl;
			i=0;
		}
		
		sem_post(&sem1);
	}
	
}
int main()
{
	
	
	pthread_t id1,id2;
	sem_init(&sem1,0,buffersize);
	sem_init(&sem2,0,0);

	
	pthread_create(&id1,NULL,&writer,NULL);
	pthread_create(&id2,NULL,&reader,NULL);
	
	
	
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
}	