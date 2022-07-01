#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <semaphore.h>
#define NTHREADS 50

// Alunos: Brenda aguiar e joão victor brandao


char fechado = 0;
int dentistaDis = 0; // 0 disponivel, 1 ocupado

int numCliente=0, ncadeiras;

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

int max = 1;
int c1 = 0;
int c2 = 0;

pthread_cond_t  vazio1, cheio2, vBuffer1, cheio1, vazio2, cheioBuf2;
pthread_mutex_t mutex1, mutex2, mutex3;
sem_t vazio;
sem_t cheio;
sem_t mutex;



void* dentista(void* arg){
   int i;
   
   // 
   int *n = (int*)arg;

   
   for(i=0;i<*n;i++){
      
      printf("Dentista eguando\n");
      sem_wait(&cheio);
      sem_wait(&mutex);
      
      //Cliente Chegou
      dentistaDis = 1;
      printf("Dentista atendendo cliente %d\n", numCliente);
      usleep(100);
       
      //Acabou o atendimento
      sem_post(&mutex);
      printf("Acabou o atendimento do dentista\n");

      sem_post(&vazio);
   }
}

void* cliente(void* arg){

   // while (count2 == 0) Pthread_cond_wait(&cheio2, &mutex2);
   int n = *((int *)arg);
   
   sem_wait(&vazio);
   sem_wait(&mutex);
   

   if(dentistaDis == 1){// ALTERE ESTA CONDICAO: DENTISTA OCUPADO
      if(ncadeiras > numCliente){ // ALTERAR ESTA CONDICAO: Se existem cadeiras livres
         printf("Cliente %d sentando na cadeira %d da fila de espera\n", n, ncadeiras--);
      }
      else{
         printf("Consultorio lotado. Cliente %d ficou puto e foi embora\n",n);
         // Vai embora
      }
   }
   
   numCliente = n;
   
   
   
   // Acabou o Atendimento
   sem_post(&mutex);
   printf("Cliente %d sendo atendido\n",n);

   sem_post(&cheio);
   printf("Cliente %d indo embora\n",n);
   
   dentistaDis = 0; 
   return NULL;
}

int main(int argc,char* argv[]){
   pthread_t tdentista,clientes[NTHREADS];
   int ids[NTHREADS],i,ncli;
   sem_init(&vazio,0,1);
   sem_init(&cheio,0,1);
   sem_init(&mutex,0,1);
   
   if(argc<3){
      fprintf(stderr,"Uso %s <nclientes> <ncadeiras>\n",argv[0]);
      return 1;
   }
   ncli = atoi(argv[1]);
   ncadeiras = atoi(argv[2]);

   pthread_create(&tdentista, NULL, dentista, &ncli);
   
   for(i=0;i<atoi(argv[1]);i++){
      ids[i]=i;
      pthread_create(&clientes[i],NULL,cliente,&ids[i]);
      usleep(100);
   }

   for(i=0;i<atoi(argv[1]);i++){
      pthread_join(clientes[i],NULL);
   }
   pthread_join(tdentista,NULL);
   return 0;
}
