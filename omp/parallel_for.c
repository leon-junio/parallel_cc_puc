#include <stdio.h>
#include <omp.h>

int main(){
	int i = 0;
#pragma omp parallel for lastprivate(i)
	for(i = 0; i < 10; i++){
		printf("tid:%d -> i:%d \n",omp_get_thread_num(),i);
	}
	printf("Acabou! Total de i %d\n:", i);
}
