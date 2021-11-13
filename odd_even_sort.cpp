#include<bits/stdc++.h>
#include<mpi.h>
#include<stdlib.h>
#define ll long long
using namespace std;
void cmp_and_store(ll A[], ll B[],int size){
    vector<ll>tmp(size+size);
    merge(A, A+size, B, B+size,tmp.begin());
    for(int i=0; i<tmp.size(); i++){
        if(i<size){
            A[i] = tmp[i];
        }
        else{
            B[i-size] = tmp[i];
        }
    }
    tmp.clear();
}
void idle_phase(ll local_arr[],int local_n,int phase,int my_rank){
     MPI_Send(local_arr, local_n, MPI_LONG_LONG, my_rank-1, phase,MPI_COMM_WORLD);
     MPI_Recv(local_arr, local_n, MPI_LONG_LONG, my_rank-1, phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
void active_phase(ll local_arr[],ll tmp[], int local_n, int phase,int my_rank){
    MPI_Recv(tmp, local_n, MPI_LONG_LONG, my_rank+1, phase, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    cmp_and_store(local_arr,tmp,local_n);
    MPI_Send(tmp, local_n, MPI_LONG_LONG, my_rank+1, phase,MPI_COMM_WORLD);
}
int main(void)
{
    int my_rank, c_size,n=8,local_n,phase;
    vector <ll> arr;
    ll *result = NULL;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &c_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if(my_rank ==0){
        arr = {2,5,1,7,3,4,9,6};
        result = (ll*)malloc(sizeof(ll)*n);
    }
    local_n = n/c_size;
    ll local_arr[local_n];

    MPI_Scatter(arr.data(),local_n,MPI_LONG_LONG,local_arr,local_n,MPI_LONG_LONG,0,MPI_COMM_WORLD);
    sort(local_arr,local_arr+local_n);

    ll * tmp = new ll (local_n+2);

    for(phase =1;phase<= c_size;phase++){
        if(phase%2 == 1){
            if(my_rank%2==0){
                if(my_rank !=0){
                    idle_phase(local_arr,local_n,phase,my_rank);
                }
            }
            else if(my_rank != c_size-1){
                active_phase(local_arr,tmp,local_n,phase,my_rank);
            }
        }
        else{
            if(my_rank%2==0){
                if(my_rank != c_size-1){
                   active_phase(local_arr,tmp,local_n,phase,my_rank);
                }
            }
            else if(my_rank !=0){
                idle_phase(local_arr,local_n,phase,my_rank);
            }
        }
    }
    MPI_Gather(local_arr,local_n,MPI_LONG_LONG,result, local_n,MPI_LONG_LONG, 0, MPI_COMM_WORLD);
     if(my_rank==0){
        puts("Sorted data :");
        for(int i=0; i<n; i++){
            printf("%lld ",result[i]);
        }
        puts("");
        free(result);
    }
    delete(tmp);
    arr.clear();
    MPI_Finalize();
    return 0;
}
