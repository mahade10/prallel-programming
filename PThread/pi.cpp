#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;
int thread_count;
long n,flag;
double sum;
long long my_n;
void* Thread_sum(void* rank){
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i+my_n;
    double local_sum = 0.0;
    if(my_first_i%2==0){
        factor=1.0;
    }
    else{
        factor=-1.0;
    }
    for (i = my_first_i; i <= my_last_i; i++, factor=-factor){
        local_sum += factor/(2*i+1);
    }
    while(flag!=my_rank);
    sum+=local_sum;
    flag=(flag+1)%thread_count;
    return NULL;
}
int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;
    thread_count = strtol(argv[1], NULL, 10);
    n=1024;
    my_n = n/thread_count;
    sum=0.0;
    flag = 0;
    thread_handles = (pthread_t*) malloc (thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL,Thread_sum, (void*) thread);
    }
    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }
    printf("Value of PI is : %.8lf\n", 4.0*sum);
    free(thread_handles);
    return 0;
}
