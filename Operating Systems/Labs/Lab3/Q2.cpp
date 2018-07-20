#include<iostream>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;


int main(int argc, char*arg[])
{

	char*array;
	int size=argc;
	int*numbers=new int [size];	
	for(int i=0;i<size;i++)
	{
		numbers[i]=atoi(arg[i]);
	}	
	
	pid_t pid=0;
	pid=fork();
	
	if(pid==0)
	{
		int sum=0;
		for(int i=0;i<size;i++)
		{
			sum=sum+numbers[i];	
		}
		cout<<"Sum is "<<sum<<endl;
	}
	else if(pid>0)
	{
		wait(NULL);
		pid=0;
		pid=fork();
		if(pid==0)
		{
			float sum=0.0;
			for(int i=0;i<size;i++)
			{
				sum=sum+numbers[i];	
			}
			float average=sum/float(size);
			cout<<"The average is "<<average<<endl;
		}
		else if(pid>0)
		{
			wait(NULL);
			pid=0;
			pid=fork();
			if(pid==0)
			{
				int max=numbers[0];
				for(int i=0;i<size;i++)
				{	
					if(numbers[i]>max)
						max=numbers[i];
				}
				cout<<"The Maximum number is "<<max<<endl;
			}
			else if(pid>0)
			{	
				wait(NULL);
				cout<<"this is parent"<<endl;				
			}
			else
				cout<<"error3"<<endl;
			
		}
		else
			cout<<"Error2"<<endl;
	}
	else
	{
		cout<<"Error1"<<endl;
	}
	return 0;
}
