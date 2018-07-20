       #include <sys/types.h>
       #include <sys/wait.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <string.h>
       #include<iostream>
       using namespace std;

       int
       main(int argc, char *argv[])
       {
           int pipe1[2];
	       int pipe2[2];
           pid_t cpid;
           char buf;
           if (argc != 2) {
               fprintf(stderr, "Usage: %s <string>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (pipe(pipe1) == -1) {
               perror("pipe");
               exit(EXIT_FAILURE);
           }

           if (pipe(pipe2) == -1) {
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
		       close(pipe2[0]);
               while (read(pipe1[0], &buf, 1) > 0)
               {
                   if(buf>='a' && buf<='z')
                   {
                       buf=buf-('a'-'A');
                   }
                   else if(buf>='A' && buf<='Z')
                   {
                       buf=buf+('a'-'A');
                   }
                   write(pipe2[1],&buf, 1);
               }
               close(pipe2[1]);
               close(pipe1[0]);
               _exit(EXIT_SUCCESS);

           } 
           else 
           {            /* Parent writes argv[1] to pipe */
               close(pipe1[0]);          /* Close unused read end */
               write(pipe1[1], argv[1], strlen(argv[1]));
               close(pipe1[1]);          /* Reader will see EOF */
               wait(NULL);                /* Wait for child */
	           close(pipe2[1]);
	           while (read(pipe2[0], &buf, 1) > 0)
               {
                   cout<<buf;
               }             
	           close(pipe2[0]); 
	           exit(EXIT_SUCCESS);
           }
       }