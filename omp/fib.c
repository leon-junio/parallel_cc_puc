/* -*- mode: c -*-
 * $Id: fib2.c 36673 2007-05-03 16:55:46Z laurov $
 * http://www.bagley.org/~doug/shootout/
 */

int atoi(char *);
#include <stdio.h>

// Use omp task to avoid parallel errors
unsigned long
fib(unsigned long n) {
    if (n <= 2)
    	return(1);
    else{
        int sum1, sum2;
        #pragma omp task shared(sum1)
        sum1 = fib(n-2);
        #pragma omp task shared(sum2)
        sum2 = fib(n-1);
	    return (sum1 + sum2);
    }
}

int
main(int argc, char *argv[]) {

#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 40
#else
#define LENGTH 30
#endif

    int N = ((argc == 2) ? atoi(argv[1]) : LENGTH);
    printf("%ld\n", fib(N));
    return(0);
}