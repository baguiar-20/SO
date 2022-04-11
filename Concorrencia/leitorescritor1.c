#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include<semaphore.h>

#define MAX 100000

typedef struct _rwlock_t {
   sem_t escrita;
   sem_t lock;
   int leitores;
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
   lock->leitores = 0;
   sem_init(&lock->lock, 0,1); 
   sem_init(&lock->escrita,0, 1); 
}

int nescritas,counter;
pthread_mutex_t mutex;

rwlock_t lock;

void *leitor(void *arg) {
   
   pthread_mutex_lock(&mutex);
   int local;
   lock.leitores++;
   if (lock.leitores == 1)
      sem_wait(&lock.escrita);
   pthread_mutex_unlock(&mutex);
   
   local = counter; //Leitura
   printf("Leitor %d leu %d\n", *((int*)arg),local);

   pthread_mutex_lock(&mutex);
   lock.leitores--;
   if (lock.leitores == 0)
      sem_post(&lock.escrita);
   pthread_mutex_unlock(&mutex);
}

void *escritor(void *arg) {
   int i;
   for (i = 0; i < nescritas; i++) {
      sem_wait(&lock.escrita);
      counter++; //Escrita
      printf("Escreveu %d\n",counter);
      sem_post(&lock.escrita);

      usleep(rand()%10000);
   }
   printf("Escritor Acabou\n");
   return NULL;
}

int main(int argc, char *argv[]) {
   int leitores,i;
   pthread_mutex_init(&mutex, NULL);
   
   if (argc != 3) {
      fprintf(stderr, "uso: %s leitores nescritas\n",argv[0]);
      exit(1);
   }
   leitores = atoi(argv[1]);
   nescritas = atoi(argv[2]);

   rwlock_init(&lock); 

   pthread_t esc, lei[MAX];

   pthread_create(&esc, NULL, escritor, NULL);
   
   for(i=0;i<leitores;i++){
      pthread_create(&lei[i], NULL, leitor, &i);
//      usleep(rand()%100000);
   }
   pthread_join(esc, NULL);
   for(i=0;i<leitores;i++){
      pthread_join(lei[i], NULL);
   }
   printf("Acabou!\n");

   pthread_mutex_destroy(&mutex);
   sem_destroy(&lock.escrita);
   return 0;
}


