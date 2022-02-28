//gettimeofday basado en el codigo de la practica 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define iteraciones 2000000000

int main(){
    long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;

    int i;
    double result = 0;
    double uno;            //numerador de todas las iteraciones en la sumatoria

    gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec; // Tiempo inicial

    for(i = 0 ; i < iteraciones ; i++){
        if(i%2 == 1){
            uno = -1;
        }else{
            uno = 1;
        }
        result += uno/((2*i)+1);
    }

    gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;

    printf("Valor de pi leibniz serial: %f\n", result*4);
    printf("Tiempo: %lld segundos\n", elapsed_time);
}