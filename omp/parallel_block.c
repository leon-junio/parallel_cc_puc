#include <stdio.h>
#include <omp.h>

int main(){
	int i = 0;
	#pragma omp parallel firstprivate(i)
	{
		i = omp_get_thread_num();
		printf("Thread #%d \n",i);
	}
	printf("Acabou! Total de i %d\n:", i);
}
