// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<iostream>
using namespace std;
int main()
{
    int fd1;
 
    // FIFO file path
    char myfifo[20] = "/tmp/myfifo";
 
    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);
 
    int str1,str2;
 	char oprt=' ';
 
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);

        read(fd1, &oprt, 1);
 		read(fd1, &str1,4);
 		read(fd1, &str2,4);
        close(fd1);
        
        
        float result;
        
		if(oprt=='+')
		result=str1+str2;
		else if(oprt=='*')	
		result=str1*str2;
        else if(oprt=='/')
        result=(str1/str2);
        else if(oprt=='-')
        result=(str1-str2);
        else
        cout<<"incorrect operator";
        
        
 
        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo,O_WRONLY);
	
        write(fd1, &result, sizeof(result));
        close(fd1);
    
    
    
    
    return 0;
}
