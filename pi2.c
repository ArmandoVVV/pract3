//gettimeofday basado en el codigo de la practica 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define iteraciones 2000000000
#define NTHREADS 4

pthread_mutex_t candado;
double result = 0;


void *func_hilos(void *args){
    int nthread = *((int *) args);
    int i;
    int inicio = nthread*(iteraciones/NTHREADS);
    int fin = (nthread+1)*(iteraciones/NTHREADS);

    double uno;      //numerador de todas las iteraciones en la sumatoria
    double result_hilo = 0;

    for (i = inicio ; i < fin ; i++){
        if(i%2 == 1){
            uno = -1;
        }else{
            uno = 1;
        }
        result_hilo += uno/((2*i)+1);
    }
    pthread_mutex_lock(&candado);
    result += result_hilo;
    pthread_mutex_unlock(&candado);
}

int main(){
    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    int i;
    pthread_t mat_hilos[NTHREADS];
    int args[NTHREADS];

    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    pthread_mutex_init(&candado,NULL); 

    //creacion de los hilos
    for(i=0 ; i<NTHREADS ; i++){
        args[i] = i;
        pthread_create(&mat_hilos[i],NULL,func_hilos,(void *) &args[i]);
    }

    //esperar a que terminen los hilos
    for(i=0 ; i < NTHREADS ; i++){
        pthread_join(mat_hilos[i],NULL);
    }
    
    pthread_mutex_destroy(&candado);

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("Valor de pi leibniz con hilos: %f\n", result*4);
    printf("Tiempo: %lld segundos\n", elapsed_time);
}