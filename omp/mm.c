#include <stdio.h>
#include <stdlib.h>

void mm(double* a, double* b, double* c, int width) 
{
// cada laço pode escrever paralelamente em uma linha de c
// pragma
 #pragma omp parallel for
 for (int i = 0; i < width; i++) {
    // pragma
    #pragma omp parallel for 
    for (int j = 0; j < width; j++) {
      double sum = 0;
      //pragma to reduction of sum
      #pragma omp parallel for reduction(+:sum)
      for (int k = 0; k < width; k++) {
	    double x = a[i * width + k];
	    double y = b[k * width + j];
        // redução
	    sum += x * y;
      }
      // independente de ponteiros para escrita
      c[i * width + j] = sum;
    }
  }
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

  //  for(int i = 0; i < width; i++) {
  //  for(int j = 0; j < width; j++) {
  //    printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
  //  }
  // }
}