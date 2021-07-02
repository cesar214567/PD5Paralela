#include<omp.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h> 
#define N 4

/* Enrique Sobrados, Stephano Wurttele, Cesar Madera */

void normaliza(double A[N][N]){
    int i,j; 
    double suma = 0.0 , factor = 1.0;
    int tid;

    #pragma omp parallel for private(i) reduction(+:suma)
    for(i=0; i < N; i++){
        tid = omp_get_thread_num();
        printf("1. En %d se hace iteracion %d\n", tid, i);
        for(j=0; j < N; j++){
            suma = suma + A[i][j]* A[i][j];
        }
    }

    factor = 1.0/sqrt(suma);
    #pragma omp parallel for private(i)
    for(i=0; i < N; i++){
        tid = omp_get_thread_num();
        printf("2. En %d se hace iteracion %d\n", tid, i);
        for(j=0; j < N; j++){
            A[i][j] = factor*A[i][j];
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