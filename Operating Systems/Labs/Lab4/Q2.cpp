       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
	#include<fstream>
	using namespace std;
       int
       main(int argc, char *argv[])
       {
           int pipe1[2];
           pid_t cpid;
           char buf;

           if (argc != 3) {
               fprintf(stderr, "Usage: %s <string>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (pipe(pipe1) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }
	   
		
           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {    /* Child reads from pipe */
               close(pipe1[1]);          /* Close unused write end */
		
		ofstream out(argv[2]);
               while (read(pipe1[0], &buf, 1) > 0)
                   out<<buf;
		out.close();
 
               close(pipe1[0]);
               _exit(EXIT_SUCCESS);

           } else {            /* Parent writes argv[1] to pipe */
               close(pipe1[0]);          /* Close unused read end */
               char buffer[1000];
		ifstream in(argv[1]);
		while(in.getline(buffer,1000))
		{
			write(pipe1[1], buffer, strlen(buffer));
			write(pipe1[1], "\n", 1);
		}
		
               close(pipe1[1]);          /* Reader will see EOF */
               wait(NULL);                /* Wait for child */
               exit(EXIT_SUCCESS);
           }
       }