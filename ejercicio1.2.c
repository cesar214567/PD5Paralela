#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h> 
#define N 2
#define NUM_THREADS 2 

/* Enrique Sobrados, Stephano Wurttele, Cesar Madera */

void normaliza(double A[N][N]){
    int i,j; 
    double suma_final=0;
    double suma = 0.0 , factor = 1.0;
    int tid;
    double rows_per_process = N/NUM_THREADS;

    #pragma omp parallel private(suma) num_threads(NUM_THREADS) private(i,tid)
    {
        tid = omp_get_thread_num();
        for(i=tid*rows_per_process; i < (tid+1)*rows_per_process; i++){
            printf("1. En %d se hace iteracion %d\n", tid, i);
            for(j=0; j < N; j++){
                suma = suma + A[i][j]* A[i][j];
            }
        }
        #pragma omp critical
        {
            suma_final+= suma;
        }
        #pragma omp barrier
        #pragma omp master
        {
            factor = 1.0/sqrt(suma_final);
        }
        
        for(i=tid*rows_per_process; i < (tid+1)*rows_per_process; i++){
            //tid = omp_get_thread_num();
            printf("2. En %d se hace iteracion %d\n", tid, i);
            for(j=0; j < N; j++){
                A[i][j] = factor*A[i][j];
            }
        }
    }
}

int main(){
    srand(time(NULL)); 
    double A[N][N];
    int i,j;
    for (i =0;i<N;i++){
        for(j = 0; j<N;j++){
            A[i][j] = rand()%10;
            printf("%f ",A[i][j]);            
        }printf("\n");
    }
    
    normaliza(A);
    for (i =0;i<N;i++){
        for(j = 0; j<N;j++){
            printf("%f ",A[i][j]);
        }
        printf("\n");
    }
}