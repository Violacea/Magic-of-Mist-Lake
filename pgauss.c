#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void test_mat_gen(int n, double *a, double *b);
int main(){
        int n;
        scanf("%d",&n);
        double A[n*n];
        int i,j,k;
        int max;
        double b[n+1]; 
        for(i = 0; i<n*n; i++){
                A[i] = 0.0;
        }
        for(i = 0; i<n+1; i++){
                b[i] = 0.0;
        }
        test_mat_gen(n, A, b);
        /*
        for(i = 0; i<n; i++){
        	for(j = 0; j<n; j++){
        		scanf("%lf", &A[i*n + j]);
			} 
            scanf("%lf", &b[i]);
        }
        */
        double q[n];
        double c;
        for(k = 0; k<n; k++){//
                for(j = k+1; j<n; j++){//
                q[j] =(double) A[j*n + k]/ A[k*n + k];
                max = j;
                    for(i = j+1; i< n; i++){
                    	q[i] = (double) A[i*n + k]/ A[k*n + k];
                    	if(fabs(q[i]) > fabs(q[j])){
							q[j] = q[i];
							max = i;
						}
					}
                	for(i = 0; i< n; i++){
						c = A[j*n + i];
						A[j*n + i] = A[max*n + i];
		                A[max*n + i] = c;
	                }
	                c = b[j];
				    b[j] = b[max];
	                b[max] = c;
                //if(q)printf("%f\n", q);
                        for(i = 0; i<n; i++){//
                            A[j*n + i] -= q[j] * A[k*n + i];
                        }
                        b[j] -= q[j]* b[k];
                }
        }
 
         for(i = n-1; i>=0; i--){
                 for(j = n-1; j>i; j--){
                 b[i] -= b[j]*A[i*n + j];//     
                 }
                 b[i] /= A[i * n + i];
         }
 
         for(i = 0; i<n; i++){
                printf("%.1f\n", b[i]); 
        }
return 0;        
} 

void test_mat_gen(int n, double *a, double *b){
        int i;
        for(i = 0; i<n; i++){
                a[i * n + i] = 6;
                if(i < n - 1){
                        a[(i+1)*n + i] = 1;
                }
                if(i){
                        a[(i-1)*n + i] = 8;
                }
                if(i == 0){
                        b[i] = 14;
                }else if(i == n-1){
                        b[i] = 7;
                }else{
                        b[i] = 15;
                }
        }
 
}
