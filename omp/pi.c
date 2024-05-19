#include <stdio.h>
#include <omp.h>

long long num_passos = 1000000000;
double passo;

int main(){
   long long i;
   double x, pi, soma=0.0;
   passo = 1.0/(double)num_passos;

   //#pragma omp parallel for num_threads(2) private(x) reduction(+:soma)
   #pragma omp parallel for private(x) reduction(+:soma)
   //#pragma omp parallel for private(x)
   for(i=0; i < num_passos; i++){
      x = (i + 0.5)*passo;
      //#pragma omp critical // iniciar sessão critica para parar todas as threads e checar o valor
      //#pragma omp atomic // Apenas faz essa linha atomica sem criar uma sessão critica
      soma = soma + 4.0/(1.0 + x*x);
   }

   pi = soma*passo;
	
   printf("O valor de PI é: %f\n", pi);
   return 0;
}