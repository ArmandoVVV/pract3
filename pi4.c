#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <signal.h>
#include <sched.h>
#include <sys/shm.h>

#define SIZE 2000000000

int cores;
double result = 0;
double *sharedmem;

int fork_proc(int args) {
    int NPROC = args;
	int inicio = NPROC * (SIZE/cores);
	int fin = inicio + (SIZE/cores);
    double calc, result_hilo = 0;

   	for(int i = inicio; i < fin; i++){
        	if(i % 2 == 0){
            		calc = (double)4 / ((2 * i) + 1);
            		result_hilo += calc;
			}
        	else{
           		calc = (double)-4 / ((2 * i) + 1);
            		result_hilo += calc;
        	}
    	}
	sharedmem[args] = result_hilo;

	exit(0);
}


int main(){
	long long start_ts;
    long long stop_ts;
    long long elapsed_time;
    long lElapsedTime;
    struct timeval ts;
	int status;
	int i;
	pid_t pid;
	int shmid;

	cores = get_nprocs();
    pid = malloc(cores * sizeof(pid_t));

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec;
    shmid=shmget(0x1234,cores*sizeof(int),IPC_CREAT|0666);

	if(shmid < 0)
	{
		fprintf(stderr,"Error al obtener memoria compartida\n");
		exit(1);
	}
	
	sharedmem=shmat(shmid,NULL,0);
	
	for(i = 0; i < cores; i++) {
		pid = fork();
		if (pid == 0)
			fork_proc(i);
	}

	for(i = 0; i < cores; i++) {
		wait(NULL);
	}
	
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; 
	elapsed_time = stop_ts - start_ts;

	int l = sizeof sharedmem / sizeof sharedmem[0];
	double total = 0;
	
	for (int i = 0; i < l; i++) {
        	double val = sharedmem[i];
        	total+=val;
	}

	result = total;

  	printf("Valor de pi leibniz con forks: %f\n", result);
    printf("Tiempo: %lld segundos\n", elapsed_time);
	shmdt(sharedmem);	
	shmctl(shmid,IPC_RMID,NULL);
        
	return 0;
}