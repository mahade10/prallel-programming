#include<stdio.h>
#include<omp.h>

int main()
{
    int total_thread, id;
    #pragma omp parallel
    {
        total_thread = omp_get_num_threads();
        id = omp_get_thread_num();
        printf("Hello world from thread %d out of %d thread\n",id,total_thread);

    }

    printf("program exits");
    return 0;
}
