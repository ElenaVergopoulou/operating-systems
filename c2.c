/*This program implements signal handling between processes. It is the second exercise
of Operating Systems lecture in ECE NTUA in 2019.
Run giving 5 arguments eg ./a.out 1 3 2 5 4. This is the order of the children explained
below:
The father generates 5 children and these pause. After that, the father process continues
child1, which types "Child1 PID is executed (number of iteration)" 3 times. Then father
pauses child1 and continues next child given in arguments, child3. This types 3 times
its status as well and then gets paused. Child 2 is then continued .......... When all 
children run one time, the same thing will have to be done another 3 times, meaning
4 total iterarions. We need exactly 5 arguments and no argument repetitions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void handler (int sig) {}
int main (int argc , char **argv){
        if (argc!=6) {
        printf ("%d arguments instead of 5 \n", argc-1);
        return 0;
        } 
     for(unsigned int i = 1; i < argc; i++) {  
	if (atoi(argv[i])<1 ||atoi(argv[i])>5)
	{printf ("%s is not a valid argument \n", argv[i]);
	return 0;}	
        for(unsigned int j = i+1; j < argc; j++) {
            if( strcmp(argv[i],argv[j])==0 ){
               printf ("%s is given more than once \n ", argv[i]);
               return 0;}
          }
        }
	int counter =1, p, k=1;
pid_t parent = getpid(), child[argc-1];

for (unsigned int i = 1; i <argc;i++){
	if(getpid() == parent){
		child[i] = fork();
		p = i;}
}

if(getppid()==parent){
	signal(SIGCONT, handler);
	signal(SIGSTOP, handler);
	signal(SIGTERM, handler);
        pause();	
        while(k == 1){
		printf("Child%d %d is executed (%d)\n", p, getpid(), counter);
		sleep(1);
		counter++;}
}
if(getpid() == parent){
        sleep (1);
	for(unsigned int i=0; i<4; i++){
		for(unsigned int j = 1; j<argc;j++){
			kill(child[atoi(argv[j])], SIGCONT);
			sleep(3);
			kill(child[atoi(argv[j])], SIGSTOP);
                        if (i==3){ kill(child[atoi(argv[j])], SIGTERM);}
		}
	}
}
return 0;
}
