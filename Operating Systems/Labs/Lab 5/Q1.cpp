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

	if(args!=2)
	{
		cout<<"Arguments error\n";
		_exit(EXIT_SUCCESS);
	}
	pid=fork();
	if(pid==0)             //Child
	{

		cout<<"Here\n";
		int key=shmget(k, 1024, 0 ); //We have not passed IPC_CREAT, this means that it will always use existing shared region. 
		if(key<0)
		{
			cout<<"Error Occured in Child\n";
		}

		Buffer* ptr= (Buffer*) shmat(key, NULL, 0); //this call will attach the shared region to this process's address space, and return the  pointer to it. the original pointer returned is void* we can typecast it to any kind of pointer.

		if(ptr==(Buffer*)-1)
			cout<<"Error assigning memory segment to child\n";

		ifstream in(argv[1]);
		if(!in.is_open())
			cout<<"Error loading file \n";
		char buff[500];
		int line=1;
		while(!in.eof())
		{
			in.getline(buff,500);
			strcpy(ptr[line++].data,buff);
		}
		in.close();

		cout<<"End\nLines:"<<line<<endl;
		ptr[0].check=line-1; //number of lines
		
		while (!(ptr[0].check==-1)); //busy wait
		ofstream out(argv[1]);
		for(int i=0;i<line;i++)
		{
			out<<ptr[i+1].data;
			out<<endl;
		}
		out.close();
		//detach
		shmdt(ptr);
	}
	else if(pid>0)			//Parent
	{
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
	else
	{
		cout<<"error in forking";
	}
}