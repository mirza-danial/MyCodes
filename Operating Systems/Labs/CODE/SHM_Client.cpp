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