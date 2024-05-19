#include <stdio.h>

// kernel function
__global__
void add(float* a, float* b){
	int index = threadIdx.x + blockIdx.x + blockDim.x;
	a[index] = a[index] + b[index];
}

int main(){
	
	int N = 2 << 10;
	float *a, *b, *a_gpu, *b_gpu;
	
	// Malloc vectors at CPU
	a = (float*) malloc(sizeof(float)*N);
	b = (float*) malloc(sizeof(float)*N);
	
	// Malloc vectors at GPU
	cudaMalloc(&a_gpu, sizeof(float)*N);
	cudaMalloc(&b_gpu, sizeof(float)*N);

	for(int i=0;i<N;i++){
		a[i] = 1.0f;
		b[i] = 1.0003f;
	}

	// copy vectors to GPU
	cudaMemcpy(a_gpu,a,sizeof(float)*N,cudaMemcpyHostToDevice);
	cudaMemcpy(b_gpu,b,sizeof(float)*N,cudaMemcpyHostToDevice);

	// call the kernel and choose the number of threads
	add <<< 1, N>>>(a_gpu,b_gpu);
	
	// copy results to CPU
	cudaMemcpy(a,a_gpu,sizeof(float)*N,cudaMemcpyDeviceToHost);

	// print the results
	for(int i=0;i<N;i++){
		printf("[%d]:%.4f", i, a[i]);
	}

	cudaFree(a_gpu);
	cudaFree(b_gpu);
	free(a);
	free(b);
}
