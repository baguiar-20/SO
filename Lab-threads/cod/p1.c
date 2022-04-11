#include <pthread.h>
#include <stdio.h>
#include <time.h>


typedef struct __myarg_t {
	int a;
	int b;
	int c;
	int d;
} myarg_t;

void *mythread(void *arg) {
	myarg_t *m = (myarg_t *) arg;
	printf("%d %d\n", m->a, m->b);
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;

	int rc;

	myarg_t args;

	int fib1 = 0;
	int fib2 = 1;
	int soma = 0;

	for(int i=0; i<8;i++){
		soma = fib1+fib2;
		fib1 = fib2;                           
 		fib2 = soma; 
		printf(" %d %d ", i,  fib2);
	}

	args.a = 10;
	args.b = 20;
	rc = pthread_create(&p1, NULL, mythread, &args);




	sleep(3);


}


// for (i = 3; i <= n; i = i + 1)           
//    7   {                                        
//    8     soma = fib1 + fib2;                    
//    9     fib1 = fib2;                           
//   10     fib2 = soma;                           
//   11   } 