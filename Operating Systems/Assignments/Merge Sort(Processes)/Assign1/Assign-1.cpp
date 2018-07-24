  #include <sys/types.h>
  #include <sys/wait.h>
  #include <stdio.h>
  #include<vector>
  #include<fstream>
  #include <stdlib.h>
  #include <unistd.h>
  #include <string.h>
  #include<iostream>
  using namespace std;

  //********************************StringToInt*******************************************
  //Take a string as an argument and convert it into a integer vector and return 
  vector<int> stringToInt(string s)
  {
    char*array=new char[s.size()+1];
    for (int i = 0; i < s.size(); ++i)
    {
    	array[i]=s[i];
    }
    array[s.size()]='\0';

    char * pch;
    pch = strtok (array,",");
    vector<int> numbers;
    while (pch != NULL)
    {
       int num=atoi(pch);
       numbers.push_back(num);
       pch = strtok (NULL, ",");
    }

    return numbers;
  }
   //********************************intToString*******************************************
  /*Take a integer type vector, start index and end index as an argument and convert
    part of vector i.e. from start to end int a string and return*/ 
  string intToString(vector<int>numbers,int s,int e)
  {
  	char buffer[33];
  	string a;
  	string b;
  	for(int i=s;i<numbers.size() && i<e+1;i++)
  	{
  		
  		sprintf(buffer,"%d",numbers[i]);
  		a=a+(string)buffer;
  		if(i!=numbers.size()-1 &&i!=e)
  			a=a+",";
  	}	
  	
  	return a;
  }

    //********************************merger*******************************************
  /*This fuction takes two integer vectors and return merged integer vector */ 
  vector<int> merger(vector<int> l,vector<int> r)
  {
    vector<int>arr;
    int n1=l.size();
    int n2=r.size();
    int i,j,k;
       
       i=0;j=0;k=0;
       while(i<n1 && j<n2)
       {
              if(l[i]<=r[j])
              {
                     arr.push_back(l[i++]);
              }
              else
              {
                     arr.push_back(r[j++]);              
              }
       }
       while(i<n1)
              arr.push_back(l[i++]);
       while(j<n2)
              arr.push_back(r[j++]); 
    return arr;
  }
    //********************************intToString*******************************************
  /*
    This function takes a filename and a integer vector as argument 
    It is a recurrsive function on it first call from main it creates P proccess
    than P process creates child processes and pass substrings to them through pipes
    child accept these substrings and call this function again depending on the size of array provided
    on back tracking child process return sorted array to parent and parent merges them
   */ 
  void mergeSort(string filename,vector<int> &numbers)
  {
     
    	pid_t pid;
    	char buf;
    	int p1[2],p2[2];                                         //Pipes for communcation with left child

    	if (pipe(p1) == -1)                                      //Error in creating pipe p1
      {
       perror("pipe");
       exit(EXIT_FAILURE);
      }
      if (pipe(p2) == -1)                                      //Error in creating pipe p2
      {
       perror("pipe");
       exit(EXIT_FAILURE);
      }
      pid=fork();
      if(pid==0)			                                         // Left Child Process
      {
      	string buffer;
      	string name;

      close(p1[1]);
        
      if(read(p1[0],&buf,1)>0)                                //reading information about its heritage i.e. either it is left or right 
         name=filename+"."+buf;
         

       while(read(p1[0],&buf,1)>0)                              //reading sub array send to it 
       {
         buffer=buffer+buf;
       }
       
       close(p1[0]);
       
       vector<int>nums=stringToInt(buffer);                     //Converting string into integer vector
       int size=nums.size();

       if(size>1)                                               //Recursive call if vector has more than 1 elements in it
         mergeSort(name,nums);
                                                                //On return nums array will be sorted as it is sent by refernce
       


       string sendstring1=intToString(nums,0,nums.size()-1);    //converting vector int string
       
      

       char* ss1=new char[sendstring1.size()+1];                //converting string in char array
       for(int i=0;i<sendstring1.size();i++)
          ss1[i]=sendstring1[i];
       ss1[sendstring1.size()]='\0';
       
       close(p2[0]);  
    
       write(p2[1],ss1,strlen(ss1));                            //writing char array to parent
       close(p2[1]);
      


      _exit(EXIT_SUCCESS);

    }
      else if(pid>0)		//Parent Process
      {	
      	string array=intToString(numbers,0,numbers.size()-1);

      	string extension=".txt";
      	string name=filename+extension;
      	
        ofstream fout(name);                                      //Writing input string to respective files
      	fout<<"Input :";
        fout<<array<<endl;
      	
      	int end=numbers.size()-1;
      	int start=0;
      	int mid=(start+end)/2;

      	string message1=intToString(numbers,start,mid);

      	char* buffer=new char[message1.size()+1];
      	for(int i=0;i<message1.size();i++)
      		buffer[i]=message1[i];
      	
      	buffer[message1.size()]='\0';
      	
        close(p1[0]);
        write(p1[1],"l",1);
        write(p1[1],buffer,strlen(buffer));                       //writing sub array to child
        close(p1[1]);

        wait(NULL);                                               //wait for child to complete process      

        close(p2[1]);
        string rec1;
        while(read(p2[0],&buf,1)>0)
          rec1=rec1+buf;                                          //reading sorted array from child
        close(p2[0]);  
       
        vector<int>r1=stringToInt(rec1);
    
     
       
        int p3[2];                                                //initialzing for second child process
        int p4[2];
        if (pipe(p3) == -1) {
         perror("pipe");
         exit(EXIT_FAILURE);
        }
        if (pipe(p4) == -1) {
          perror("pipe");
          exit(EXIT_FAILURE);
        }
        pid=fork();

        if(pid==0)			                                           //Right Child Process
        {
          string container;
          string fname;
          char buff;
          close(p3[1]);
          if(read(p3[0],&buff,1)>0)
            fname=filename+"."+buff;
       
          while(read(p3[0],&buff,1)>0)
          {

            container=container+buff;
            
          }
       
          close(p3[0]);
          vector<int>nums=stringToInt(container);
          int size=nums.size();


          if(size>1)
            mergeSort(fname,nums);
          
        

          string sendstring2=intToString(nums,0,nums.size()-1);
          
          char* ss2=new char[sendstring2.size()+1];
          for(int i=0;i<sendstring2.size();i++)
            ss2[i]=sendstring2[i];
          ss2[sendstring2.size()]='\0';
         
          close(p4[0]);
    
          write(p4[1],ss2,strlen(ss2));

          close(p4[1]);
          _exit(EXIT_SUCCESS);
        }
      	else if(pid>0)		                                             //Parent Process Part for right child
      	{	
          string message2=intToString(numbers,mid+1,end);

          char* buffer1=new char[message2.size()+1];
          for(int i=0;i<message2.size();i++)
            buffer1[i]=message2[i];

          buffer1[message2.size()]='\0';
          close(p3[0]);
          write(p3[1],"r",1);
          write(p3[1],buffer1,strlen(buffer1));
          close(p3[1]);
          wait(NULL);  

          close(p4[1]);
          string rec2;
          while(read(p4[0],&buf,1)>0)
            rec2=rec2+buf;
          close(p2[0]);
          vector<int>r2=stringToInt(rec2);

        
          vector<int> merged=merger(r1,r2);                         //Merging outuput of right and left children

          numbers=merged;
         
          string mergeString=intToString(merged,0,merged.size()-1);
          fout<<"Output : ";
          fout<<mergeString<<endl;
          fout.close();

      
        }
        else
        {
          cout<<"error"<<endl;
        }

      }
      else
      {
      	cout<<"error";
      }
    }


    int main(int argc,char *argv[])
    {
     ifstream in("InputAssign-1.txt");
     string input;
     in>>input;
     in.close();
     vector<int>a=stringToInt(input);
     string name="P";
     mergeSort(name,a);
   }

