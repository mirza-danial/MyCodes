#include <iostream>
using namespace std;
#include <semaphore.h>
#include <pthread.h>
#include<string.h>

sem_t semaphore1;
sem_t semaphore2;
sem_t semaphore3;
int i = 0, j = 0, k = 0;
int count=5;
void *a(void *)
{
 while (i < count)
 {
  sem_wait(&semaphore1);
  cout<<"a";
  sem_post(&semaphore3);
  i++;
 }

}

void* b(void *)
{  
   while (j < count)
    {
    	j++;
      sem_wait(&semaphore2);
      cout<<"b";
      sem_post(&semaphore1);
    }

}

void* c(void *)
{  
   while (k < count)
    {
    	k++;
      sem_wait(&semaphore3);
      cout<<"c";
      sem_post(&semaphore2);
    }

}

int main()
{

	pthread_t id1, id2, id3;
  sem_init(&semaphore1, 0, 0);
  sem_init(&semaphore2, 0, 0);
  sem_init(&semaphore3, 0, 1);
  
  pthread_create(&id1, NULL, &a, NULL);
  pthread_create(&id2, NULL, &b, NULL);
  pthread_create(&id3, NULL, &c, NULL);
  
  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
  pthread_join(id3, NULL);
  cout<<endl;

}