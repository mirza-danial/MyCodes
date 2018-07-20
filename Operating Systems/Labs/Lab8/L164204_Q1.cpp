 #include <iostream>
#include<stdlib.h>
using namespace std;
#include <string.h>
#include<vector>
#include<pthread.h>


void* myFunc(void* param)
{

	int a=*(int*) param;
	vector<int>*fib=new vector<int>;
	fib->push_back(0);
	fib->push_back(1);
	int next;
	int i=1,j=2;
	for(next=1;next<=a;i++,j++)
	{
		
		fib->push_back(next);
		next=((fib->at(i)) + (fib->at(j)));

		
	}
	fib->push_back(next);
	

	pthread_exit( (void*) fib);
  
  //do not use exit routine, it will terminate the whole process


}


int main(int args,char* argv[])
{
	if(args<2)
	{
		cout<<"Incompatible arguments :( ";
		return 0;
	}
	
	pthread_t * id = new pthread_t [args-1];
	int index=0;
	int *arr=new int [args-1];
	for(int i=0;i<args-1;i++ )
	{
		arr[i]=atoi(argv[i+1]);
	}
	for(int i=1;i<args;i++,index++)
	{
	
		if (pthread_create(&id[index], NULL,myFunc,&arr[index]) ==-1)
		{
			cout<<"Thread Creation Failed!"<<endl;
			return 1;
		}

  
	}
	
	for(int i=0;i<args-1;i++)
	{
		vector<int> *ptr;
		
		pthread_join(id[i], (void**) &ptr);
		cout<<"Thread "<<i<<" :" ;
		for(int j=0;j < ptr->size();j++ )
		{
			cout<<ptr->at(j)<<" ";
		}
		cout<<endl;
	}
	


  
}