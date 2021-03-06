#include <cstdio>
#include <cstdlib>
#include <omp.h>

int main(){
  	const int n=3000; // This problem scales as n^3. 
                    // This value may need to be adjusted

  	double * A = (double*) malloc(sizeof(double)*n*n);
  	double * B = (double*) malloc(sizeof(double)*n*n);
  	double * C = (double*) malloc(sizeof(double)*n*n);
  
  	printf("Carrying out matrix-matrix multiplication\n");

 
 	int i,j,k;

	for (i = 0 ; i < n; i++) {
		for(j = 0; j < n; j++) {
	      A[i*n+j]=(double)i/(double)n;
	      B[i*n+j]=(double)j/(double)n;
	    }
	}

	C[0:n*n] = 0.0;

	double time = omp_get_wtime();
        #pragma omp parallel for 	
	for ( i = 0 ; i < n ; i++){
	    for ( j = 0 ; j < n ; j++) {
	    	#pragma omp simd
	      	for ( k = 0 ; k < n ; k++) {
				C[i*n+k] += A[i*n+j]*B[j*n+k];
	      	}
	    }
	}
	  time = omp_get_wtime() - time;
	  
	  printf("Checking the results...\n");
	  double norm = 0.0;
	  for ( i = 0 ; i < n ; i++)
	    for ( j = 0 ; j < n ; j++)
	      norm += (C[i*n+j]-(double)(i*j)/(double)n)*(C[i*n+j]-(double)(i*j)/(double)n);
	  
	  if (norm > 1e-10)
	    printf("Something is wrong... Norm is equal to %f\n", norm);
	  else
	    printf("Yup, we're good!\n");

	  printf("Computing time: %f\n", time);  
}
