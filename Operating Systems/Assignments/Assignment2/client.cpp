
#include <sys/socket.h>
#include <netinet/in.h>	
#include<error.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<vector>
#include<fstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
#include<netdb.h>
using namespace std;
bool flag=true;
int qfd;
/*
	This Thread reads a message sent
	to client socket by server and display it.
*/
void*readThread(void*para)
{
	char buffer[256];
	int sockfd=*(int*)para;
	while(flag)
	{		
		bzero(buffer,256);	
		int n = read(sockfd,buffer,255);
		if(n<0)
		{
			perror("ERROR reading from socket");
		}
		if(strncmp(buffer,"quit",4)==0)
		{
				flag=false;
				write(sockfd,buffer,strlen(buffer));

				char buf='q';
				write(qfd,&buf,1);
				break;
		}
		printf("\033[0;31m					%s\033[0m\n", buffer);
		
	}

	pthread_exit(NULL);

}

/*
	This Thread writes messages to server socket.
*/
void*writeThread(void*para)
{	
	int sockfd=*(int*)para;
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
			int n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) 
			{
				perror("ERROR writing to socket");
			}
			if(strcmp(buffer,"quit")==0)
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

				write(sockfd,"quit",4);
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


int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char * quit = "/tmp/quit"; 
	mkfifo(quit, 0666);
	qfd=open(quit,O_RDWR);

	char buffer[256];
	if (argc < 2) {

		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
	}
	
	portno = 7788;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
		perror("ERROR opening socket");
	 
	server = gethostbyname(argv[1]);
	
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr , server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		perror("Connection failed");
	printf("\033[0;32m YOU ARE CONNECTED\033[0m\n");
	pthread_t a,b,c;	
    pthread_create(&a,NULL,&readThread,&sockfd);
    pthread_create(&b,NULL,&writeThread,&sockfd);
    pthread_create(&c,NULL,&quitThread,NULL);

    pthread_join(b,NULL);
     
    pthread_join(a,NULL);

	pthread_join(c,NULL);   

	
	close(sockfd);
	
	return 0;
}
