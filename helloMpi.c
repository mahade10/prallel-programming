#include <stdio.h>
#include<string.h>
#include "mpi.h"
int main()
{
    int size,rank,i;
    char arr[1000];
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank!=0){
        sprintf(arr, "Greetings from process %d of %d!", size,rank);
        MPI_Send(arr,strlen(arr)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }
    else{
        printf("Greetings from process %d of %d!\n",size,rank);
        for(i=1;i<size;i++){
            MPI_Recv(arr,1000,MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("%s\n",arr);
        }
    }
    MPI_Finalize();
    return 0;
}
