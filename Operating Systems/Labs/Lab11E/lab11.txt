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
int count;
sem_t sem1;
int size=0;
char * line;
int exists=0;
void *Writer(void * param)
{
	char * arr=(char*) param;
	 char *str = arr;
	int k=0;
	sem_wait(&sem1);
	int counter=0;
	for(int i=0;i<size/2;i++)
	{
		for(int j=i;j<i+count;j++)
		{
			if(str[j]==line[k])
			{
				counter++;
				k++;
			}	
		}
		k=0;
		if(counter==count)
		exists++;
		counter=0;
		//if(strstr(str, line) != NULL)
		//{
			
		//	exists++;

		//}
	}
}


void* Reader (void *param)
{  
  	 char * arr=(char*) param;
  	 char *str = arr;
  	 int k=0;
  	 int counter=0;
	for(int i=(size/2)+1;i<size;i++)
	{
	
		for(int j=i;j<i+count;j++)
		{
			if(str[j]==line[k])
			{
				counter++;
				k++;
			}	
		}
		k=0;
		if(counter==count)
		exists++;
		counter=0;
	  	// if(strstr(str, line) != NULL)
		//{
			
			//exists++;
		//	
		//}
	}
	sem_post(&sem1);

}
int main(int argc,char * argv[])
{
	int fd;
	pthread_t id1, id2;
  	sem_init(&sem1, 0, 0);
	fd=open(argv[1],O_RDONLY);
	data=mmap(NULL,getpagesize(),PROT_READ,MAP_SHARED,fd,0);
	cout<<(char*) data<<endl;
	char * arr=(char*) data;
	line=argv[2];
	for(int i=0;line[i] != '\0';i++)
	{
		count++;
	}
	for(int i=0;arr[i] != '\0';i++)
	{
		size++;
	}
	 pthread_create(&id1, NULL, &Writer, data);
 	 pthread_create(&id2, NULL, &Reader, data);
 
  	pthread_join(id1, NULL);
  	pthread_join(id2, NULL);
  	cout<<exists<<endl;
	return 0;
	
}