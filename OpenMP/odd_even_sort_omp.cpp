#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
int main(int argc, char* argv[])
{
    int a[1000],i,n=10,tmp,phase;
     //int thread_count = strtol(argv[1],NULL,10);
     int thread_count = omp_get_num_threads();
    for(i=0;i<n;i++){
        a[i] = rand()%100 +1;
    }
    # pragma omp parallel num_threads(thread_count)\
    default(none) shared(a,n) private(phase,i,tmp)
    for( phase =1;phase<=n;phase++){
        if(phase%2==0){
             #pragma omp for
            for(i=1;i<n;i+=2){
                if(a[i-1]>a[i]){
                    tmp = a[i-1];
                    a[i-1] = a[i];
                    a[i] =tmp;
                }
            }
        }
        else{
             #pragma omp for
             for(i=1;i<n-1;i+=2){
                if(a[i]>a[i+1]){
                    tmp = a[i];
                    a[i] = a[i+1];
                    a[i+1] =tmp;
                }
            }
        }
    }
     puts("Sorted array :");
    for(i=0; i < n; i++){
        cout<<a[i]<<" ";
    }
}
