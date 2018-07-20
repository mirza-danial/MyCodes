#include<iostream>     // For cout
#include <fcntl.h>    // For O_RDWR 
#include <unistd.h>   // For open(), creat() 
#include <stdio.h>    // For fflush(stdout)
using namespace std;
         
int main()
 {
    //in = open("input",O_RDONLY);
    //dup2(in,STDIN_FILENO);
    //close(in);
    
    int stdoutCopy = dup(1);	
    int out = open("output.txt",O_WRONLY|O_CREAT,0666); // Should also be symbolic values for access rights
    if(out < 0)
	return 1;
    int status = dup2(out,1);
    if(status < 0)
	return 1;
    cout << "Output on file\n";
    close(out);
    fflush(stdout);  
     
    status = dup2(stdoutCopy,1);
    if(status < 0)
	return 1;
    cout << "Output on screen\n";
    close(stdoutCopy); 
    return 0;
}

