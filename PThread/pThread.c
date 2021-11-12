#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int thread_count;
void* Hello(void* rank){
    long my_rank = (long)rank;
    printf("printing from: %ld \n",my_rank);
    return NULL;
}
int main(int argc, char* argv[]){
    long thread;
    pthread_t* thread_handles;
    thread_count = strtol(argv[1],NULL,10);

    thread_handles = (pthread_t*)malloc(thread_count* sizeof(pthread_t));
    for(thread =0;thread<thread_count;thread++){
        pthread_create(&thread_handles[thread],NULL, Hello, (void*) thread);
    }
    printf("hello from the main thread\n");
    for(thread =0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);
    }
    free(thread_handles);

}