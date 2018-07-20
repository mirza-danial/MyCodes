
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<errno.h>
#include<iostream>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
using namespace std;
void * data;
int substring_size;
sem_t sem1;
int memory_size=0;
char * substring;
int substring_count=0;
void *First_Half(void * param)
{
	char * arr=(char*) param;
	 char *str = arr;
	int k=0;
	sem_wait(&sem1);
	int counter=0;
	for(int i=0;i<memory_size/2;i++)
	{
		for(int j=i;j<i+substring_size;j++)
		{
			if(str[j]==substring[k])
			{
				counter++;
				k++;
			}	
		}
		k=0;
		if(counter==substring_size)
		substring_count++;
		counter=0;
		
	}
}


void* Second_Half (void *param)
{  
  	 char * arr=(char*) param;
  	 char *str = arr;
  	 int k=0;
  	 int counter=0;
	for(int i=(memory_size/2)+1;i<memory_size;i++)
	{
	
		for(int j=i;j<i+substring_size;j++)
		{
			if(str[j]==substring[k])
			{
				counter++;
				k++;
			}	
		}
		k=0;
		if(counter==substring_size)
		substring_count++;
		counter=0;
	  	
	}
	sem_post(&sem1);

}
int main(int argc,char * argv[])
{
	if(argc!=3)
	{
		cout<<"Invalid arguments!"<<endl;
		return 1;
	}
	int fd;
	pthread_t id1, id2;
  	sem_init(&sem1, 0, 0);
	fd=open(argv[1],O_RDONLY);
	data=mmap(NULL,getpagesize(),PROT_READ,MAP_SHARED,fd,0);

	char * arr=(char*) data;
	substring=argv[2];
	
	substring_size=strlen(substring);
	memory_size=strlen(arr);
	
	 pthread_create(&id1, NULL, &First_Half, data);
 	 pthread_create(&id2, NULL, &Second_Half, data);
 
  	pthread_join(id1, NULL);
  	pthread_join(id2, NULL);
  	cout<<"Substring repeatetions:"<<substring_count<<endl;
	return 0;
	
}