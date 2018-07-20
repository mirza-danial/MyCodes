#include<iostream>     // For cout
#include <fcntl.h>    // For O_RDWR 
#include <unistd.h>   // For open(), creat() 
#include <stdio.h>    // For fflush(stdin)
using namespace std;
         
int main()
 {
    int a;
    int stdinCopy = dup(0);
    
    int in = open("input.txt",O_RDONLY);
    if(in < 0)
	return 1;
    int status = dup2(in,STDIN_FILENO);
    if(status < 0)
	return 1;
    close(in);
    
    cout << "Input from file\n";
    cin >> a;
    cout << "Value of input is: " << a << endl;
   
    fflush(stdin);  
     
    
    status = dup2(stdinCopy,0);
    if(status < 0)
	return 1;
    close(stdinCopy); 
 
    cout << "Input from keyboard/user\n";
    cin >> a;
    cout << "Value of input is: " << a << endl;
    
	
    return 0;
}

