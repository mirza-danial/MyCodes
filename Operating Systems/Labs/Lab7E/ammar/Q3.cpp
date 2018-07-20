#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include<stdlib.h>
#include<pthread.h>
using namespace std;



void* average(void* param)
{
float sum=0;
int* param2=(int*)param;

int vals=param2[0]+1;		//0th index contains number of values in the array


for(int i=1;i<vals;++i)
sum=sum+param2[i];

float* avg=new float;
*avg=sum/(vals-1);


pthread_exit(avg);

}


void* min(void* param)
{

int* param2=(int*)param;
int* min=new int;
*min=param2[1];




int vals=param2[0]+1;		//0th index contains number of values in the array


for(int i=1;i<vals;++i)
	if(param2[i]<*min)
	*min=param2[i];


pthread_exit(min);
}



void* max(void* param)
{
int* param2=(int*) param;

int* max=new int;
*max=param2[1];

int vals=param2[0]+1;		//0th index contains number of values in the array


for(int i=1;i<vals;++i)
	if(param2[i]>*max)
	*max=param2[i];


pthread_exit(max);
}






int main(int argc,char* argv[])
{
const int size=argc;


int nums[size];

pthread_t tid,tid1,tid2;

nums[0]=argc-1;

for(int i=1; i<size; ++i)
 nums[i]=atoi(argv[i]);


for(int i=0;i<size;++i)
cout<<nums[i];


pthread_create(&tid,NULL,&average,nums);
pthread_create(&tid1,NULL,&min,nums);
pthread_create(&tid2,NULL,&max,nums);


int* maxx,*minn;
float* avg;


pthread_join(tid,(void**)&avg);
pthread_join(tid1,(void**)&minn);
pthread_join(tid2,(void**)&maxx);



cout<<"Average :"<<*avg<<endl;
cout<<"Minimum :"<<*minn<<endl;
cout<<"Maximum :"<<*maxx<<endl;




return 0;
}
