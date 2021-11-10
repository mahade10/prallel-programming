
#include<stdio.h>
//#include<mpi.h>
#include "mpi.h"

double func(double x){
    return x*x;
}
    double trap(double local_a, double local_b, double local_n, double h){
    double segmentArea, tmp;
    int i;
    segmentArea = (func(local_a)+func(local_b))/2.0;
    for(i=1;i<local_n;i++){
        segmentArea = segmentArea + func(local_a+i*h);
    }
    segmentArea =segmentArea*h;
    return segmentArea;
}
int main()
{
    int my_rank,c_size,n=1024,local_n;
    double a =0.0, b= 3.0, h,local_a,local_b;
    double local_int, total_int;
    int source;

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&c_size);

    h = (b-a)/n;
    local_n = (double)n/c_size;
    local_a = a + my_rank*local_n*h;
    local_b = a+ local_n*h;
    local_int = trap(local_a,local_b,local_n,h);

     if(my_rank != 0){
        MPI_Send(&local_int,1, MPI_DOUBLE,0,0,MPI_COMM_WORLD);

     }
     else{
        total_int = local_int;
        for(source =1 ; source<c_size; source++){
           MPI_Recv(&local_int,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            total_int = total_int + local_int;
        }
        printf("with n = %d trapezoid, our integral from %f to %f = %.20f \n", n,a,b, total_int);

     }
   MPI_Finalize();
   return 0;

}

