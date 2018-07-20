#include <iostream>
using namespace std;
#include <semaphore.h>
#include <sys/shm.h>
#include <queue>
#include <string.h>

struct Student
{

 int rollNumber;
 char name[20];

};

int main()
{



   Student *buffer;

  int id_sem=shmget(990, 1024, 0666 | IPC_CREAT | IPC_EXCL);
  int id_cs= shmget(991, 1024,  0666| IPC_CREAT | IPC_EXCL);

  sem_t *semaphore;
 
  if (id_sem==-1 || id_cs==-1)
  {
   
    cout<<"ERROR!";
    return 1;
    
  }




  semaphore= (sem_t*) shmat(id_sem, NULL, 0);
   buffer= (Student*) shmat(id_cs, NULL, 0);

  sem_init(semaphore, 1, 1); //1 means semaphore is used for process synchronization, count is 1 (only one process will be allowed at a time)
 
  sem_wait(semaphore);


   buffer[0].rollNumber=10;
   strcpy(buffer[0].name, "abc");

 char a;
 cout<<"Press any key to continue: ";
 cin>>a;
 
 sem_post(semaphore); 
 

 cout<<"Press any key to continue: ";
 cin>>a;

  sem_destroy(semaphore);
  shmdt(semaphore);
  shmdt(buffer);
  shmctl(id_sem, IPC_RMID, NULL);
  shmctl(id_cs, IPC_RMID, NULL);
}
