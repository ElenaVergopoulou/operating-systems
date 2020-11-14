/*THIS PROGRAM TAKES AS ARGUMENTS THE NUMBER OF CHILDREN A FATHER GENERATES TO COMPUTE THE 
FACTORIAL OF A NUMBER GIVEN AS SECOND ARGUMENT. FATHER PASSES NUMBER 1 TO FIRST CHILD AND
THEN THIS PASSES 1*2 TO THE SECOND AND SO ON TILL THE FACTORIAL IS COMPUTED. 
EXECUTE WITH eg ./a.out 5 9 (find 9! using 5 children).

THIS IMPLEMENTATION IS MADE WITH MULTIPLE PIPES. 
COMMUNICATION BETWEEN CHILDREN IS ACHIEVED WITH DIFFERENT PIPES AND COMMUNICATION 
FATHER-FIRST CHILD AND LAST CHILD-FIRST CHILD SHARE A PIPE. 

This program is the third exercise of Operating Systems in ECE NTUA in 2019. There is 
another implementation using one pipe in this repository with the name
"multiple-processes-one-pipe.c".
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main (int argc, char **argv){

	//definition of variables
	int   chn = atoi(argv[1]), myn, size = 0, status, number;
	char fact[64];
	int k = atoi(argv[2]), child[chn], fd[chn+1][2];
	int parent = getpid();

	//Error checking
	if(chn <= 0 || chn > 10){
		printf("Error: value out of boundaries\n");
		exit(1);
	}
	if(k < 0){
		printf("Error:Imposible to calulate factorial for negative number\n");
		exit(2);
	}
        if (argc!=3){
		printf("Error:Invalid number of arguments\n");
		exit(3);
	}

        //create pipes
	for(int i = 0; i <= chn; i++){
		pipe(fd[i]);
		if(pipe(fd[i]) < 0){
			printf("Error at creating pipe\n");
			exit(4);
		}
	}

	//creating processes
	for (int i = 0; i < chn; i++){
		if (getpid() == parent){
			child[i]=fork();
			if(child[i]==0){
				myn = i+1;
				size = myn;
			}
			else if(child[i] < 0){
				printf("Error at creating a child\n");
				exit(5);
			}
		}
	}

	//father sending the number 1
	if(getpid()==parent){
		fact[0] ='1';
		close(fd[0][0]);
		write(fd[0][1],fact,sizeof(fact));
		wait(&status);
		//father closing the pipes
		for(int i = 0;i <= chn; i++){
			close(fd[i][0]);
			close(fd[i][1]);
		}
		exit(0);
	}

	//first child receiving number 1
	if(myn == 1){
		read(fd[0][0],fact,sizeof(fact));
		number = atoi(fact);
		sprintf(fact,"%d", number); // int to string
		if(k == 0 || k == 1)
			printf("result = %d\n",number);
		else{
			write(fd[1][1],fact,sizeof(fact));
			size+=chn;
		}
	}

        if(getpid() != parent){
	while(k > 1){
			if(myn!=1){
				read(fd[myn-1][0],fact,sizeof(fact));

			}
			else{
				read(fd[chn][0],fact,sizeof(fact));
			}
			number = atoi(fact);
			number *= size;
			sprintf(fact, "%d", number);
			size+=chn;
			write(fd[myn][1],fact,sizeof(fact));
			if(size == chn+k ){
				printf("result = %d \n",number);
				break;
			}
			if(size > k ){
				break;
			}
		}
		exit(0);
	}
}
