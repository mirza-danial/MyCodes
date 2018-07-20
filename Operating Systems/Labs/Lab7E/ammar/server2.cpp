// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
int fd[2];

int x=pipe(fd);

pid_t pid;
pid_t pid2;
pid=fork();



if(pid==0)//child
{
dup2(fd[1],1);			//maps file descriptor 1 to fd[1] of pipe;
execlp("/bin/ls","ls",NULL);
}
else if(pid>0)//parent
{
close(fd[1]);

pid2=fork();

if(pid2==0)
{
dup2(fd[0],0);			//maps file descriptor 0 to fd[0] of pipe;

execlp("/usr/bin/sort","sort",NULL);		

}
else if(pid2>0)
{
wait(NULL);
}
else cout<<"error";





}
else 
cout<<"Error";




















	return 0;
}
