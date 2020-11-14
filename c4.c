/*
This program implements pipes use as semaphores for the critical section problem.
It is the fourth exercise of Operating Systems lecture in ECE NTUA in 2019.

The father generates three children and these three cgildren have a code
divided in 5 section as shown bellow:
CHILD1:				CHILD2:				CHILD3:
CRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
NONCRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION
NONCRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
CRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION
NONCRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
CRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION

A critical section uses printf to type a message 5 times and a noncritical
is a printf that executes 7 times. The point is that when a child process 
runs a critical section the other processes are not allowed to enter theirs'.
They are allowed though to enter a noncritical section.
This implementation uses the fact that when a read command commes up,
the process should wait for another one to write to the pipe.
So in fact i dont care about the value I am passing 
but about the passing itself.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	static int myn;
	int *number,a=1;
	int child[3],fd[2];
	number=&a;
	int parent = getpid();
	
	if(pipe(fd) < 0){
		printf("error creating pipe\n");
		exit(1);
	}

	for (int i = 0; i < 3; i++){
		if (getpid() == parent){
			child[i]=fork();
			if(child[i]==0){
				myn = i+1;
			}
			else if(child[i] < 0){
				printf("Error at creating a child\n");
				exit(2);
			}
		}
	}
       //Father writing in the pipe so the children can run
	if(getpid()==parent){
		close(fd[0]);
		write(fd[1],number,sizeof(number));
	}
   	//Childrens code
	if(getppid()==parent){
	for(unsigned int i = 1; i <= 6; i++)
	{	//Proc 1 critical 
		if(myn == 1 && (i == 1 || i == 4 || i == 6)){
			read(fd[0],number,sizeof(number));
			for(int k = 0; k < 5; k++)
			{ 			
				//sleep(1);
				printf("Child%d %d executes a critical section\n",myn,getpid());
			}
			number = &a;
			write(fd[1],number,sizeof(number));
		}
		//Proc 2 critical
		else if(myn == 2 && (i == 2 || i == 4 || i == 6)){
			read(fd[0],number,sizeof(number));
			for(int k = 0; k < 5; k++){					
				//sleep(1);
				printf("Child%d %d executes a critical section\n",myn,getpid());
			}
			number = &a;
			write(fd[1],number,sizeof(number));
		}
		//Proc 3 critical
		else if(myn == 3 && (i == 1 || i == 3 || i == 5)){
			read(fd[0],number,sizeof(number));
			for(int k= 0; k < 5; k++){			
				//sleep(1);
				printf("Child%d %d executes a critical section\n",myn,getpid());
			}
			number = &a;
			write(fd[1],number,sizeof(number));
		}
		//Non critical Sections
		else if(myn != 0){
			for(int k = 0; k < 7; k++){			
				//sleep(1);
				printf("Child%d %d executes a non critical section\n",myn,getpid());
			}
		}
		else 
			break;
	}
	}
	//Terminate the children
	if(myn != 0){
		close(fd[0]);
		close(fd[1]);
	}
	//Father waitng for children to end
	if(myn == 0){
		for(int m = 0; m < 3; m++)
			wait(0);
		close(fd[0]);
		close(fd[1]);
	} 
   return 0;
}

