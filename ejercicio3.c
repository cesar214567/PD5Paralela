#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHIL 5
#define MEALS 100

omp_lock_t  forks[NUM_PHIL];

void philosofer(){
    #pragma omp barrier
    int left, right;
    int tid = omp_get_thread_num();
    int iter;
    right = tid<NUM_PHIL-1?tid:0;
    left = tid<NUM_PHIL-1?tid+1:tid;
    for (iter=0;iter<MEALS;iter++){
        omp_set_lock(&forks[left]);
        omp_set_lock(&forks[right]);

        printf("philosopher %d is eating\n", tid);
        usleep(100);

        omp_unset_lock(&forks[right]);
        omp_unset_lock(&forks[left]);
    }
}

int main(int argc, char ** argv) {
    int i;
    for( i = 0; i < NUM_PHIL; i++){
        omp_init_lock(&forks[i]);
    }
    #pragma omp parallel num_threads(NUM_PHIL)
    {
        philosofer();
    }
    for(i = 0; i < NUM_PHIL; i++)
        omp_destroy_lock(&forks[i]);

}

