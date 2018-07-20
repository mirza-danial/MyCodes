#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;


int main(int args,char*arg[])
{
	pid_t pid=0;
	pid=fork();
	
	if(pid==0)	//1ST accepts 2 args
	{
		execlp(arg[1],arg[1],NULL);	
	}	
	else if(pid>0)
	{
		wait(NULL);
		pid=0;
		pid=fork();
		
		if(pid==0)
		{	
			execlp(arg[2],arg[2],NULL);
		}
		else if(pid>0)//2nd accepts 2 args
		{
			wait(NULL);
			pid=0;
			pid=fork();
			
			if(pid==0)
			{	
				execlp(arg[3],arg[3],arg[4],NULL);
			}
			else if(pid>0)//3rd accepts 3 args
			{
				wait(NULL);
				pid=0;
				pid=fork();
				
				if(pid==0)
				{	
					execlp(arg[5],arg[5],arg[6],NULL);
				}
				else if(pid>0)//4th accepts 3 args
				{
					wait(NULL);
					cout<<"This is Parent"<<endl;
				}
				else
				{
					cout<<"Error";
				}
			}
			else
			{
				cout<<"Error";
			}
		}
		else
		{
			cout<<"Error";
		}
	}
	else
	{
		cout<<"Error";
	}
	
	return 0;
}
