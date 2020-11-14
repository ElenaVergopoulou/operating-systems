/*THIS PROGRAM IMPLEMENTS A TREE OF FORKED PROCESSES AS SHOWN BELOW AND EACH PROCESS PRINTS ITS STATUS
------------F---------------
----------/---\-------------
--------CH1---CH2-----------
-------/---\----\-----------
-----CH3--CH4---CH5---------
This is the first exercise of Operating Systems lecture in ECE NTUA in 2019.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	int status;
	pid_t p,c;
	pid_t child[5];
	child[0]=fork();
	if (child[0]<0) {
		printf ("Error");
	}
	else if(child[0]==0) {
		child[2]=fork();
		if (child[2]<0) {
			printf ("Error");
		}
		else if (child[2]==0) {
			c=getpid();
			p=getppid();
			for (unsigned int i=0; i<10; i++) {
				printf ("Process %d is executed, my father is %d \n", c,p);
				sleep(1);
			}
			exit(0);
		}
		else {
			child[3]=fork();
			if (child[3]<0){
				printf ("Error");
			}
			else if (child[3]==0){
				c=getpid();
				p=getppid();
				for (unsigned int i=0; i<10; i++) {
					printf ("Process %d is executed, my father is %d \n", c,p);
					sleep(1);
				}
				exit(0);
			}
			else  {
				c=getpid();
				p=getppid();
				for (unsigned int i=0; i<10; i++) {
					printf ("Process %d is executed, my father is %d \n", c,p);
					sleep(1);
				}
                                wait (&status);
				exit(0);
		       }
                        wait(&status);
			exit(0);
		}
		exit(0);
	}
	else {
		child[1]=fork();
		if (child[1]<0) {
			printf ("Error");
		}
		else if (child[1]==0) {
			child[4]=fork();
			if (child[4]<0){
				printf ("Error");
			}
			else if (child[4]==0){
				c=getpid();
				p=getppid();
				for (unsigned int i=0; i<10; i++) {
					printf ("Process %d is executed, my father is %d \n", c,p);
					sleep(1);
				}
				exit(0);
			}
			else  {
				c=getpid();
				p=getppid();
				for (unsigned int i=0; i<10; i++) {
					printf ("Process %d is executed, my father is %d \n", c,p);
					sleep(1);
				}
                                wait (&status);
				exit(0);
			}
			exit(0);
		}
		else {
		wait (&status);	      
		exit(0);
		}
          wait (&status);
          exit(0);
	}
	return 0;
}





