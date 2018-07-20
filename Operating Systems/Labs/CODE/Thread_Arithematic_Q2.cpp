
 #include <iostream>
#include<stdlib.h>
using namespace std;
#include <string.h>
#include<vector>
#include<pthread.h>


void* max(void* param)
{
	
vector<int> a=*(vector<int>*) param;
	int *result=new int;
	
	int r=a[0];
	for (int i = 0; i < a.size(); ++i)
	{
		if(r<a[i])
			r=a[i];
	}
	*result=r;

	pthread_exit( (void*) result);
  
  //do not use exit routine, it will terminate the whole process


}
void* min(void* param)
{
	

	vector<int> a=*(vector<int>*) param;
	int *result=new int;
	
	int r=a[0];
	for (int i = 0; i < a.size(); ++i)
	{
		if(r>a[i])
			r=a[i];
	}
	*result=r;
	pthread_exit( (void*) result);
  
  //do not use exit routine, it will terminate the whole process


}

void* avg(void* param)
{
	

	vector<int> a=*(vector<int>*) param;
	float *result=new float;
	float sum=0;
	for (int i = 0; i < a.size(); ++i)
	{
		sum=sum+a[i];
	}
	*result=sum/(float)a.size();

	pthread_exit( (void*) result);
  
  //do not use exit routine, it will terminate the whole process


}

int main(int args,char* argv[])
{
	if(args<2)
	{
		cout<<"Incompatible arguments :( ";
		return 0;
	}
	vector<int> v;
	for (int i = 1; i < args; i++)
	{
		v.push_back(atoi(argv[i]));	
	}


	pthread_t * id = new pthread_t [3];
	int index=0;
	
	if (pthread_create(&id[index++], NULL, max, &v)==-1)
	{
		cout<<"Thread Creation Failed!"<<endl;
		return 1;
	}
  	int *ptr1;
	pthread_join(id[0], (void**) &ptr1);
	cout<<"maximum value is:" <<*ptr1<<endl;


	if (pthread_create(&id[index++], NULL, min, &v)==-1)
	{
		cout<<"Thread Creation Failed!"<<endl;
		return 1;
	}
  	int *ptr2;
	pthread_join(id[1], (void**) &ptr2);
	cout<<"minimum value is:" <<*ptr2<<endl;


	if (pthread_create(&id[index++], NULL, avg, &v)==-1)
	{
		cout<<"Thread Creation Failed!"<<endl;
		return 1;
	}
  	float *ptr3;
	pthread_join(id[2], (void**) &ptr3);
	cout<<"average is:" <<*ptr3<<endl;
	
	


  
}