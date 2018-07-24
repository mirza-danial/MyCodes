
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include<vector>
#include<fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
bool flag=true;
int qfd;
/*
	This Thread reads a message sent
	to server socket by client and display it.
*/
void*readThread(void*para)
{	
	int newsockfd=*(int*)para;
	char buffer[256];
	while(flag)
	{
		bzero(buffer,256);	
		int n = read(newsockfd,buffer,255);
		if(n<0)
		{
			perror("ERROR reading from socket");
		}
		if(strncmp(buffer,"quit",4)==0)
		{
				flag=false;
				write(newsockfd,buffer,strlen(buffer));
				char buf='q';
				write(qfd,&buf,1);
				break;
		}
		printf("\033[0;31m					%s\033[0m\n", buffer);	
	}

	pthread_exit(NULL);

}
/*
	This Thread writes messages to client socket.
*/
void*writeThread(void*para)
{	
	int newsockfd=*(int*)para;
	char buffer[256];
	fd_set rfds;
    struct timeval tv;
    int retval;
	tv.tv_sec = 5;
    tv.tv_usec = 0;	
	while(flag)
	{
		bzero(buffer,256);

		FD_ZERO(&rfds);
        FD_SET(0, &rfds);
		retval = select(1, &rfds, NULL, NULL, &tv);
		if(retval)
		{
			cin.getline(buffer,255);
			int n = write(newsockfd,buffer,strlen(buffer));
			if (n < 0) 
			{
				perror("ERROR writing to socket");
			}
			if(strncmp(buffer,"quit",4)==0)
			{
					flag=false;
					char buf='q';
					write(qfd,&buf,1);
					break;
			}
		}
		else if(retval==-1)
		{
			cout<<"error\n";
		}
		else
		{
			if(!flag)
			{
				write(newsockfd,"quit",4);
				break;
			}
		}
	}
	pthread_exit(NULL);
}
/*	
	This thread wait for main program
	to send quit command on fifo and terminates 
	the process accordingly.
*/
void*quitThread(void*para)
{
	char buf;
	read(qfd,&buf,1);
	close(qfd);
	if(buf=='q')
	{
		flag=false;
	}

	pthread_exit(NULL);
}

int main()
{
	char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666);

    char * quit = "/tmp/quit"; 
	mkfifo(quit, 0666);
	qfd=open(quit,O_RDWR);

    int sockfd,newsockfd;
    int fd=open(myfifo,O_RDONLY);
    read(fd,&sockfd,4);
    read(fd,&newsockfd,4);
    close(fd);
    	
    pthread_t a,b,c;	
    pthread_create(&a,NULL,&readThread,&newsockfd);
    pthread_create(&b,NULL,&writeThread,&newsockfd);
    pthread_create(&c,NULL,&quitThread,NULL);


    pthread_join(a,NULL);
    pthread_join(b,NULL);
    pthread_join(c,NULL);   

	close(newsockfd);
	close(sockfd);
}