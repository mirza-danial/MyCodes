#include <iostream>
#include<unistd.h>
#include <sys/shm.h>
#include <string>
#include<fstream>
#include <stdio.h>
#include <cstring>
using namespace std;

class Buffer
{
public:
	int check;
	char data[500];
};

int main(int args,char*argv[])
{
		pid_t pid;
		int k=215;

		int key=shmget(k, 1024, IPC_CREAT | IPC_EXCL | 0666); //4 is the key// 1024 is the bytes we want to use as shared memory 
		if(key==-1)
			cout<<"Not created"<<endl;

		Buffer* ptr= (Buffer*) shmat(key, NULL, 0); //this call will attach the shared region to this process's address space, and return the  pointer to it. the original pointer returned is void* we can typecast it to any kind of pointer.

		cout<<"shm created with id= "<<key<<endl;
		ptr[0].check=-1;

		cout<<"Waiting for the client process to send data.!"<<endl;
		while (ptr[0].check==-1); //busy wait

		cout<<endl;
		for (int i=1; i<= ptr[0].check; i++)
		{
			for(int j=0;ptr[i].data[j]!='\0';j++)
			{
				if(ptr[i].data[j]>='a' && ptr[i].data[j]<='z')
					ptr[i].data[j]=ptr[i].data[j]-32;
				else if(ptr[i].data[j]>='A' && ptr[i].data[j]<='Z')
					ptr[i].data[j]=ptr[i].data[j]+32;
				else if(ptr[i].data[j]>='0' && ptr[i].data[j]<='9')
					ptr[i].data[j]=' ';
			}
		}
		ptr[0].check=-1;

		//detach
		shmdt(ptr);

		shmctl(key, IPC_RMID, NULL); //mark the shared region for deletion
	
}