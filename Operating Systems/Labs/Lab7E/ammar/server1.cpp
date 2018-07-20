// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
	int fd;

	// FIFO file path
	char myfifo[20] = "/tmp/myfifo";

	// Creating the named file(FIFO)
	// mkfifo(<pathname>, <permission>)
	mkfifo(myfifo, 0666);

	int oprnd1, oprnd2;
	char operat;

		// Open FIFO for write only
		fd = open(myfifo, O_WRONLY);

		// Take an input arr2ing from user.
		// 80 is maximum length

		cin >>operat>>oprnd1>>oprnd2;

	
		// Write the input arr2ing on FIFO
		// and close it
		write(fd , &operat , 1);
		write(fd,&oprnd1,4);
		write(fd,&oprnd2,4);
	
		close(fd);

		// Open FIFO for Read only
		fd = open(myfifo, O_RDONLY);

		float output=0;

		// Read from FIFO
		read(fd, &output, sizeof(output));
		close(fd);
		// Print the read message
		cout<<"Result : "<<output<<endl; 
	
	return 0;
}
