#define _GNU_SOURCE
#ifndef USE_GNU
#define USE_GNU
#endif
#include <sched.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>  



void q1(int npags, int interacoes){
    clock_t inicio,fim;
    double tempo_sec;
    int salto = 4096/sizeof(int);
    int v[npags*salto];
    double media = 0.0;
    

    for(int j=0; j< interacoes; j++){
        inicio = clock();

        for(int i=0; i < npags*salto;i+=salto){
            v[i]+=1;
        }

        fim = clock();
        tempo_sec = (double)(fim-inicio)/CLOCKS_PER_SEC;
        media += tempo_sec;
    }
    printf("%d %f \n", npags, media/interacoes);
    // printf("Numero de Paginas %d\n", npags);
    // printf("Tempo medio %f s\n", media/interacoes);
}





int main(int argc, char const *argv[]){
    int npags = atoi(argv[1]);
    int interacoes =  atoi(argv[2]);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    q1(npags, interacoes);
    
    return 0;
}












