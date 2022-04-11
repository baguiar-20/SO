#include <bits/stdc++.h>
#include "aloca.h"
#include <cstring>
#include <iostream>


using namespace std;
int numMagico;   
int numMagico2;

typedef struct{

	int inicio;
	int tam;

}livre;

vector <livre> lista_de_livres(10000);

char *tamMemoria;
int politicaMemoria;


char *novoinicio;


Meualoc::Meualoc(int tamanhoMemoria,int politicaMem){
    tamMemoria = (char*) malloc (tamanhoMemoria * sizeof(char));
	politicaMemoria = politicaMem;
	
}



char *bestfit(int tam){
	int melhor_bloco = 0;
	int cont;
	int aux = 0;
   
	for (int i = 0; i < lista_de_livres.size(); ++i){
       if(lista_de_livres.at(i).tam > tam  && lista_de_livres.at(i).tam <= lista_de_livres.at(melhor_bloco).tam){
          melhor_bloco = i;
		  aux = 1;

        }
		else if(lista_de_livres.at(i).tam == tam  && lista_de_livres.at(i).tam <= lista_de_livres.at(melhor_bloco).tam ){
			melhor_bloco = i;
			aux = 2;
		}
		else{
			aux = 3;
		}
    }

        
    if(aux == 1){
        
        novoinicio = &tamMemoria[lista_de_livres.at(melhor_bloco).inicio];
        int p = 0;
        for(int p = 0 ; p <tam; p++ ){
            if(p >= 0 && p < 2){
			    numMagico = rand() % 100;
          	    tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = numMagico;
            }else if(p >= 2 && p <4){
                tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = tam;
            }else{
                tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = '0';
            }
        
        }

        lista_de_livres.at(melhor_bloco).tam = lista_de_livres.at(melhor_bloco).tam - tam;
		lista_de_livres.at(melhor_bloco).inicio  =  ((lista_de_livres.at(melhor_bloco).inicio) + tam);
        return novoinicio;

        
    }else if(aux == 2){
        int p = 0;
        novoinicio = &tamMemoria[lista_de_livres.at(melhor_bloco).inicio];
        for(int p = 0 ; p <tam; p++ ){
            if(p >= 0 && p < 2){
			    numMagico = rand() % 100;
          	    tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = numMagico;
            }else if(p >= 2 && p <4){
                tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = tam;
            }else{
                tamMemoria[lista_de_livres.at(melhor_bloco).inicio + p ] = '0';
            }
            
        }
        lista_de_livres.erase(lista_de_livres.begin()+melhor_bloco);
        
    }
	else if(aux ==3){
		cout<< "nao foi possivel alocar"<<endl;
		return NULL;
	}
	return novoinicio;

}




char * firstfit(int tam){

	for (int i = 0; i < lista_de_livres.size(); ++i){
		if(lista_de_livres.at(i).tam > tam){ // pega o primeiro espaço que seja maior que o processo
			novoinicio = &tamMemoria[lista_de_livres.at(i).inicio]; // recebe o novo inicio do bloco

			for(int p=0;p<tam;p++){
				if(p == i and i < 3){
					numMagico = rand() % 100;
					tamMemoria[lista_de_livres.at(i).inicio + p] = numMagico;
				}
				else if(p == i and i == 2 and i == 3){
					tamMemoria[lista_de_livres.at(i).inicio + p ] = tam;
				}
				else{
					tamMemoria[lista_de_livres.at(i).inicio + p ] = '0';
				}
			}

			lista_de_livres.at(i).tam = lista_de_livres.at(i).tam - tam;
			lista_de_livres.at(i).inicio = ((lista_de_livres.at(i).inicio) + tam);
	
		}
		else if(lista_de_livres.at(i).tam == tam){ // pega o espaço que seja igual ao processo
			novoinicio = &tamMemoria[lista_de_livres.at(i).inicio]; // recebe o novo inicio do bloco

			for(int p=0;p<tam;p++){
				if(p == i and i < 3){
					numMagico = rand() % 100;
					tamMemoria[lista_de_livres.at(i).inicio + p] = numMagico;
				}
				else if(p == i and i == 2 and i == 3){
					tamMemoria[lista_de_livres.at(i).inicio + p ] = tam;
				}
				else{
					tamMemoria[lista_de_livres.at(i).inicio + p ] = 'j';
				}
			}

			lista_de_livres.erase(lista_de_livres.begin()+i);
		}
	}
	return novoinicio;
}



char * nextfit(int tam){
	char* ultimaalocacao;
	int co = 0;
	
	if(co == 0){ 
		ultimaalocacao = &tamMemoria[lista_de_livres.at(0).inicio];
		co = 1;
	}
	if( ultimaalocacao == &tamMemoria[lista_de_livres.at(lista_de_livres.size()-1).inicio]){
		ultimaalocacao = &tamMemoria[lista_de_livres.at(0).inicio];
	}

	for (int i = 0; i < lista_de_livres.size(); ++i){


		if(lista_de_livres.at(i).tam > tam and (&tamMemoria[lista_de_livres.at(i).inicio] > ultimaalocacao) ){		
			
			novoinicio = &tamMemoria[lista_de_livres.at(i).inicio];
			ultimaalocacao = &*novoinicio;

			//arrumar
			int p;
				for(int p=0;p<tam;p++){
				if(p == i and i < 3){
					numMagico = rand() % 100;
					tamMemoria[lista_de_livres.at(i).inicio + p] = numMagico;
				}
				else if(p == i and i == 2 and i == 3){
					tamMemoria[lista_de_livres.at(i).inicio + p ] = tam;
				}
				else{
					tamMemoria[lista_de_livres.at(i).inicio + p ] = '0';
				}
			}

			lista_de_livres.at(i).tam = lista_de_livres.at(i).tam - tam;
			lista_de_livres.at(i).inicio  =  ((lista_de_livres.at(i).inicio) + tam);

			return novoinicio;
			
		} 
		else if(lista_de_livres.at(i).tam == tam and (&tamMemoria[lista_de_livres.at(i).inicio] > ultimaalocacao) ){
			
			
			novoinicio = &tamMemoria[lista_de_livres.at(i).inicio];
			ultimaalocacao = &*novoinicio;
			
			int p;
			for(int p=0;p<tam;p++){
				if(p == i and i < 3){
					numMagico = rand() % 100;
					tamMemoria[lista_de_livres.at(i).inicio + p] = numMagico;
				}
				else if(p == i and i == 2 and i == 3){
					tamMemoria[lista_de_livres.at(i).inicio + p ] = tam;
				}
				else{
					tamMemoria[lista_de_livres.at(i).inicio + p ] = '0';
				}
			}
			lista_de_livres.erase(lista_de_livres.begin()+i);

		}
	}
	return novoinicio;
}
	




 char* verifica(char* ponteiro,int posicao){

    if(ponteiro != NULL){
		return ponteiro;
    }else{
        return NULL;
    }
  }




int libera(char* ponteiro){
    
	int tamanho = *(ponteiro+2);
    
	for(int p=0;p<tamanho;p++){
      *(ponteiro+p) = ' ';
    }

    for (int i = 0; i < lista_de_livres.size(); ++i){

      if( lista_de_livres.at(i).inicio ==  ((&*ponteiro - &tamMemoria[0]) +  tamanho) ){
        lista_de_livres.at(i).inicio = &*ponteiro - &tamMemoria[0];
        lista_de_livres.at(i).tam = lista_de_livres.at(i).tam + tamanho;
        break;
        
      }else if(lista_de_livres.at(i).inicio + lista_de_livres.at(i).tam == (&*ponteiro - &tamMemoria[0])){
        lista_de_livres.at(i).tam = lista_de_livres.at(i).tam + tamanho;
        break;
        
      }else{
        livre novo;
		novo.inicio = &*ponteiro - &tamMemoria[0] ;
		novo.tam = tamanho;
		lista_de_livres.push_back(novo);
        break;
        
      }
      
    }
    return 1;
  }


char *Meualoc::aloca(unsigned short int tamanho){
    
	int tam = tamanho ;
	// printf("endereco do tam: %p\n",&tam);
	
	if(politicaMemoria == 1){
		novoinicio = bestfit(tam);
	}
	else if(politicaMemoria == 0){ //bestfit
		// cout<<"teste"<<endl;
		novoinicio = firstfit(tam);

	}else if(politicaMemoria == 2){ //bestfit
		// cout<<"teste"<<endl;
		novoinicio = nextfit(tam);

	}
	

	return novoinicio;
		
}



void imprimeDados(int mediaTamanhos[], int qtdOperacoes){

	int numelementos = 0;
	int maior = 0;
	int somatamanhos = 0;
	

	for(int t=0;t<lista_de_livres.size();t++){

		numelementos++;
		if(lista_de_livres.at(t).tam > maior){ maior =  lista_de_livres.at(t).tam; }
		// somatamanhos += lista_de_livres.at(t).tam;

		// cout << "Tamanho dos tamanhos"<< lista_de_livres.at(t).tam<<endl;

		cout<<"espaco: "<<t<<endl;
		cout<<"inicio: "<<lista_de_livres.at(t).inicio<<endl;
		cout<<"tam: "<<lista_de_livres.at(t).tam<<endl;
		
	}
	



	cout<<"Espacos livres:      "<<numelementos<<endl;
	cout<<"Maior espaco livre:  "<<maior<<endl;

	if(numelementos>0){
		cout<<"Media de tamanhos:   "<<somatamanhos/numelementos<<endl;
	}
	cout<<"\n";


}

Meualoc::~Meualoc() {
    free(tamMemoria);
    lista_de_livres.clear();
}
	



int main(){

    
    FILE *arq; 
    // arq = fopen("workloadMem0", "rt");
	arq = fopen("ArqTeste.txt", "rt");
    
    int politica;
    int n;
	int operacoes;

    fscanf(arq, "%d\t%d", &n , &politica );
    fscanf(arq, "%d", &operacoes );

	char* lista_de_processos[operacoes];
    int id, tamanho;
    char tarefa[1];
    
    Meualoc *meualoc;
    numMagico =  rand() % 100;

    

	Meualoc(n, politica);

    livre inicio;
	inicio.inicio = 0;
	inicio.tam = n;
	lista_de_livres.push_back(inicio);

	

    for(int i =0;i < lista_de_livres.size(); i++){
		lista_de_livres[i].inicio = i*n; 	// 0, 10
		lista_de_livres[i].tam = n + lista_de_livres[i].inicio; 	// 10, 20

		// cout << "Inicio do bloco: " << lista_de_livres[i].inicio <<"\n";
		// cout << "Tam do bloco: " << lista_de_livres[i].tam <<"\n";
	}
	
   // vector <char*> lista_de_processos(operacoes);

   int mediaTamanhos[operacoes];
   int soma = 0;
    
    for(int i = 0 ; i < operacoes ; i++){

        //scanf( "%s", tarefa);
        fscanf(arq, "%s\t%d\t%d", tarefa , &id ,&tamanho);
       
		mediaTamanhos[id]  = tamanho;

        int result = strcmp(tarefa, "A");
        if(result == 0){
			
            lista_de_processos[id] = meualoc->aloca(tamanho);
			cout << "aaaa"<<endl;
			// mediaTamanhos[id]  = tamanho;
			
        }else{
			if(verifica(lista_de_processos[id], id) !=NULL){
				libera(lista_de_processos[id]);
			}
	        
        }
        
    }
	
	// size_t len = sizeof(mediaTamanhos)/sizeof(mediaTamanhos[0]);
	
	// for(int i=0; i< len; i++){
	// 	somatamanhos += mediaTamanhos[i];
	// 	cout<<"tamanhos:   "<<mediaTamanhos[i]<<endl;
	// }
    

	 imprimeDados(mediaTamanhos, operacoes);
	
	
}
