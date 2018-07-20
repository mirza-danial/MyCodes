#include<sys/socket.h>
#include<netinet/in.h>	
#include<error.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
#include<netdb.h>
#include<pthread.h>
using namespace std;
int no_of_threads=0;
bool flag=true;

struct param{
	int newsockfd;
	int sockfd;
};

/*
	This thread is created by Server thread to 
	when a connection request is accepted 
	this thread opens a chatting program in xterm
	and send it the socket file discriptor through 
	fifo.
*/
void*thread(void *para)
{
	param obj=*(param*) para;

	char * myfifo = "/tmp/myfifo"; 
    mkfifo(myfifo, 0666);
	
	pid_t pid;
	no_of_threads++;

	pid=fork();
	
	if(pid==0)
	{ 
		system("/usr/bin/xterm -e ./q.out");
	}	
	else if(pid>0)
	{
		int fd=open(myfifo,O_WRONLY);
		write(fd,&obj.sockfd,4);
		write(fd,&obj.newsockfd,4);
		close(fd);
		wait(NULL);
	}

	no_of_threads--;


	pthread_exit(NULL);
}


/*
	This thread is created by main in the start.
	It is responsible for opening 7788 socket 
	binding socket,listening from socket and accepting 
	connection requests. After accepting a request it creates 
	a separate thread for communication.
*/
void* ServerThread(void *para)
{
	
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0)
		perror("ERROR opening socket");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = 7788;
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		pthread_exit(NULL);		
	}

	int index=0;
	vector<param> sockfd_arr;	//Creating vector for parameter and id because in loop variables are overwriten and the parameter value of threads also changes due to this overwriting.
	vector<pthread_t> id;
	listen(sockfd,5);
		

	fd_set rfds;
    struct timeval tv;
    int retval;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

	while(no_of_threads<5 && flag)
	{
		 tv.tv_sec = 20;			//Timeout 
         tv.tv_usec = 0;
		 FD_ZERO(&rfds);
         FD_SET(sockfd, &rfds);

		clilen = sizeof(cli_addr);
		retval = select(sockfd+1, &rfds, NULL, NULL, &tv);		//Waiting for connection request untill timeout
		if(retval)
		{
			
			newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
			if (newsockfd < 0)
				perror("ERROR on accept");
			param var;
			var.sockfd=sockfd;
			var.newsockfd=newsockfd;

			sockfd_arr.push_back(var);
			id.push_back(0);

			pthread_create(&id[index],NULL,&thread,(void*)&sockfd_arr[index]);
			index++;
			
		}
		else if(retval==-1)
		{
			perror("select");
		}
		else 
		{
		//	cout<<"timeout occured\n";
		}
	}	

	for(int i=0;i<index;i++)	//Joining all created threads
	{
		pthread_join(id[i],NULL);
	}

	pthread_exit(NULL);
}
 
int main()
{

	cout<<"The Program may have to wait about 20 sec to exit after giving quit statement because  of the timeout for thread to quit accepting connection request.\n";
	char * quit = "/tmp/quit"; 
    mkfifo(quit, 0666);

	pthread_t pt;
	pthread_create(&pt,NULL,&ServerThread,NULL);
	char command[100];

	while(1)
	{

		cout<<">";
		bzero((void*)command,100);
		cin.getline(command,100);

		if(strncmp(command,"connect",7)==0)
		{ 
			char* ip=strtok(command," ");
			ip=strtok(NULL," ");
			char add[100]="/usr/bin/xterm -e ./client.out ";
			strcat(add,ip);

			pid_t p1;
			p1=fork();
			if(p1==0)
			{
				system(add);
				_exit(EXIT_SUCCESS);
			}		
		}
		else if(strncmp(command,"quit",4)==0)
		{
			if(no_of_threads>0)
			{
				int qfd=open(quit,O_WRONLY);
				char buf='q';
				for(int i=0;i<no_of_threads;i++)		//Giving Call to quit to all executing chats
				{
					write(qfd,&buf,1);
					write(qfd,&buf,1);
				}
				close(qfd);
			}
			flag=false;
			break;
			
		}
	}
		pthread_join(pt,NULL);
		return 0;
}
