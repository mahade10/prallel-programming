#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
long thread_count;
int mat[10][10], vec[10],res[10],i,m,n,j,local_m,local_n;

void* mul(void* rank){
    long my_rank = (long)rank;
    long my_first_row = my_rank*local_m;
    long my_last_row = (my_rank+1) * local_m -1;

    for(i= my_first_row; i<=my_last_row;i++){
        res[i] =0.0;
        for(j=0;j<n;j++){
            res[i] += mat[i][j] * vec[j];
        }
    }
     return NULL;
}
int main(int argc, char* argv[])
{
    long thread;
    pthread_t* lp;
    thread_count = strtol(argv[1],NULL,10);

    lp = (pthread_t*)malloc(thread_count *sizeof(pthread_t));

    printf("enter matrix size\n");
    scanf("%d %d",&m,&n);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&mat[i][j]);
        }
    }
    for(j=0;j<n;j++)
        scanf("%d",&vec[j]);

     local_m = m/thread_count;
     clock_t  begin= clock();
    for(thread =0;thread<thread_count;thread++){
        pthread_create(&lp[thread],NULL, mul,(void*) thread);
    }
    for(thread =0; thread<thread_count;thread++){
        pthread_join(lp[thread],NULL);
    }
    clock_t end= clock();

    free(lp);
    double spent = (double)(end -begin)/CLOCKS_PER_SEC;
    for(j=0;j<n;j++)
        printf("%d \n",res[j]);

    printf("Total time: %.8lf\n", spent * 1000.0);
    return 0;
}

