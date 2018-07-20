#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;


int main()
{
	pid_t pid=0;
	pid=fork();
	
	if(pid==0)
	{
		for(int i=0;i<100;i++)
		{
			cout<<"I'm Child :("<<endl;	
		}
	}
	else if(pid>0)
	{
		wait(NULL);
		for(int i=0;i<100;i++)
		{
			cout<<"I'm Parent!"<<endl;
		}
	}
	else
	{
		cout<<"Error"<<endl;
	}
	return 0;
}
