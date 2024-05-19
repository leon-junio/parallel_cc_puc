/**
Tempos de execução
Sequencial: 
test passed

real    0m4.517s
user    0m4.517s
sys     0m0.001s

Paralelo:
test passed

real    0m3.345s
user    0m12.880s
sys     0m0.000s

*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() 
{
	int i, j, n = 30000; 

	// Allocate input, output and position arrays
	int *in = (int*) calloc(n, sizeof(int));
	int *pos = (int*) calloc(n, sizeof(int));   
	int *out = (int*) calloc(n, sizeof(int));   

	// Initialize input array in the reverse order
	for(i=0; i < n; i++)
		in[i] = n-i;  

	// Print input array
	//   for(i=0; i < n; i++) 
	//      printf("%d ",in[i]);

#pragma omp parallel for private(j)
	for(i=0; i < n; i++) 
		for(j=0; j < n; j++)
			if(in[i] > in[j]) {
#pragma omp atomic
				pos[i]++;	
			}

	// Move elements to final position
	for(i=0; i < n; i++) 
		out[pos[i]] = in[i];

	// print output array
	//   for(i=0; i < n; i++) 
	//      printf("%d ",out[i]);

	// Check if answer is correct
	for(i=0; i < n; i++)
		if(i+1 != out[i]) 
		{
			printf("test failed\n");
			exit(0);
		}

	printf("test passed\n"); 
}  
