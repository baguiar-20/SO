#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>


int max;
int loops;
int *buffer1,*buffer2;

int consome1  = 0;
int produz1 = 0;
int consome2  = 0;
int produz2= 0;


#define MAX (10)
int consumidores = 1;
int produtores = 1;
int nambos = 1;
int count = 0;

pthread_cond_t  vBuffer1, vBuffer2,vBuffer3, cheioBuf1, cheioBuf2, cheioBuf3;
pthread_mutex_t mutex1, mutex2, mutex3;

void Pthread_mutex_lock(pthread_mutex_t *mutex){
   int rc =  pthread_mutex_lock( mutex);
   assert(rc == 0);
}

void Pthread_mutex_unlock(pthread_mutex_t *mutex){
   int rc =  pthread_mutex_unlock( mutex);
   assert(rc == 0);
}

void Pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex){
   int rc =  pthread_cond_wait(cond, mutex);
   assert(rc == 0);
}

void Pthread_cond_signal(pthread_cond_t *cond){
   int rc =  pthread_cond_signal(cond);
   assert(rc == 0);
}

void Pthread_cond_broadcast(pthread_cond_t *cond){
   int rc =  pthread_cond_broadcast(cond);
   assert(rc == 0);
}


void produz(int valor,int buf) {
   if(buf==1){
      buffer1[produz1] = valor;
      produz1 = (produz1+1) % max;
   }else{
      buffer2[produz2] = valor;
      produz2 = (produz2+1) % max;
   }
}

int consome(int buf) {
   int tmp; 
   if(buf==1){
      tmp = buffer1[consome1];
      consome1 = (consome1+1) %max;
   }else{
      tmp = buffer2[consome2];
      consome2 = (consome2+1) %max;
   }

   return tmp;
}

void *produtor(void *arg) {
   int i;
   for (i = 0; i < loops; i++) {
      Pthread_mutex_lock(&mutex1);
      while (count == MAX) Pthread_cond_wait(&vBuffer1, &mutex1);
      produz(i,1);
      printf("Produtor %lld produziu %d\n em 1", (long long int) arg, i);
      Pthread_cond_signal(&cheioBuf1);
      pthread_cond_broadcast(&cheioBuf1);
      Pthread_mutex_unlock(&mutex1); 
   }
   printf("Produtor %d finalizado\n",*((int*)arg));
   return NULL;
}

void *consumidor(void *arg) {
   int tmp = 0;
   while (1) {
      Pthread_mutex_lock(&mutex2);
      while (count == MAX) Pthread_cond_wait(&vBuffer2, &mutex2);
      tmp = consome(2);
      printf("Consumidor %lld consumiu %d de 2\n", (long long int) arg, tmp);
      Pthread_cond_signal(&cheioBuf2);
      pthread_cond_broadcast(&cheioBuf2);
      Pthread_mutex_unlock(&mutex2); 
   }
   return NULL;
}

void *ambos(void *arg) {
   int tmp = 0;
   while (1) {
      Pthread_mutex_lock(&mutex3);
      while (count == MAX) Pthread_cond_wait(&vBuffer3, &mutex3);
      tmp = consome(1);
      printf("Ambos %lld consumiu %d em 1\n", (long long int) arg, tmp);
      produz(tmp,2);
      printf("Ambos %lld produziu %d em 2\n", (long long int) arg, tmp);
      Pthread_cond_signal(&cheioBuf3);
      pthread_cond_broadcast(&cheioBuf3);
      Pthread_mutex_unlock(&mutex3); 
   }
   return NULL;
}

int main(int argc, char *argv[]) {
   if (argc != 6) {
      fprintf(stderr, "uso: %s <tambuffer> <loops> <produtores> <consumidores> <ambos>\n", argv[0]);
      exit(1);
   }
   max   = atoi(argv[1]);
   loops = atoi(argv[2]);
   produtores = atoi(argv[3]);
   consumidores = atoi(argv[4]);
   nambos = atoi(argv[5]);
   assert(consumidores <= MAX);

   buffer1 = (int *) malloc(max * sizeof(int));
   buffer2 = (int *) malloc(max * sizeof(int));
   int i;
   for (i = 0; i < max; i++) {
      buffer1[i] = 0;
      buffer2[i] = 0;
   }


   pthread_t pid[MAX], cid[MAX],aid[MAX];
   for (i = 0; i < consumidores; i++) {
      pthread_create(&cid[i], NULL, consumidor, (void *) (long long int) i); 
   }
   for (i = 0; i < nambos; i++) {
      pthread_create(&aid[i], NULL, ambos, NULL);
   }
   for (i = 0; i < produtores; i++) {
      pthread_create(&pid[i], NULL, produtor, NULL);
   }
   for (i = 0; i < consumidores; i++) {
      pthread_join(pid[i], NULL); 
      pthread_join(aid[i], NULL); 
      pthread_join(cid[i], NULL); 
   }

   free(buffer1);
   free(buffer2);

   return 0;
}


