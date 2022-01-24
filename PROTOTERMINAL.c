#include<stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>




char *lerlinha(){
	char p; 
	int x;
	int posicao = 0;
	int tamanho = 1000;
	char *args = malloc(sizeof(char)* tamanho);
	
	while(x){
		p = getchar();
		if(p == EOF || p == '\n'){
			args[posicao] = '\0';
			return args;
		}else{
			args[posicao] = p;
		}
		posicao++; 
		
		if(posicao >= tamanho){
			tamanho = tamanho * 2; 
			args = realloc(args,tamanho);
		}
	}
	
}


// 1. implementar o comando 
void comando(char ** args){

	//printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();
	if (rc < 0) {// fork falhou
	    fprintf(stderr, "fork falhou\n");
	    exit(1);
	} else if (rc == 0) { // filho
	   
	    execvp(args[0], args); // roda wc		
	    printf("Comando não encontrado\n");
	} else {// Pai vem por aqui
		
	    int wc = wait(NULL);
	}
}

char** separalinha(char* linha){
	int tamanho = 100;
	int i = 0;
	char *args2  = malloc(tamanho * sizeof(char*));
	char **argfinal = malloc(tamanho * sizeof(char*));
	char modificacoes[4] = " \n";
	
	args2 = strtok(linha,modificacoes);	
	while(args2 != NULL){
		argfinal[i] = args2;
		i++;
			
		if(i >= tamanho){
			tamanho = tamanho*2;
			argfinal = realloc(argfinal , tamanho *sizeof(char));
		}
		args2 = strtok(NULL,modificacoes);
	}
	
	argfinal[i] = NULL;
	
	return argfinal;
}

int separapipe(char* linha , char** pi){
	int i  = 4;
	for(i=0 ; i<2 ; i++){
		pi[i] = strsep(&linha , "|");	
	}
	
	if(pi[1] == NULL){
		i=0;
		return i;//não é pipe
	}else{
		return 1;//é pipe
	}
}


int main(){


	int x = 1; 
	int i = 0;
	char* cd[1];
	cd[0] = "cd";
	int comp = 1 ;
	int tamanho = 100;
	char* pi[2];
	int identifica = 0;
	char *args = malloc(tamanho * sizeof(char*));
	char **pipe = malloc(tamanho * sizeof(char*));
	char **argfinal = malloc(tamanho * sizeof(char*)) ;
	int pipes;

	while(x){
		// ler uma linha 
    
		args = lerlinha();	 // LINHA LENDO 
			// tentando criar um vetor de vetores com tokens 
		
		
		// verificar se é pipe e separa. 		
		
		identifica = separapipe(args , pi ); // verificando se te | na linha 
		if(identifica == 1 ){
			argfinal = separalinha(pi[0]);
			pipe = separalinha(pi[1]);
		}else{
			argfinal = separalinha(args);
		}
		//salva o identifica pipe se for 1 é pipe se for 0 é normal;
		if(identifica == 0){
			comp = strcmp(argfinal[0],cd[0]);
			if(comp == 0){
				chdir(argfinal[1]);
			}else{
				comando(argfinal);
			}
		}else{
			printf("eu sou um pipe\n");
		}
	
			/*agora tenho que entender o que é pipe, e como usar isso nos comando */
			/* criar um separador que diz se a entrada é pipe ou não, se não for pipe, chama comando. se for pipe, crio outro comando para esse pipe*/
		//}
	
		free(args);
		free(argfinal);
	}
	
	return 0;
		//printf("%s",argfinal[0]); // teste de separação da string. funcionando. 
		// cada posição de argfinal é uma palavra. a separação é feita por espaços. 
		//mas vou adicionar < > | & ??ou isso é um argumento ?
		
	// so saio daqui quando deu separar essa string. 
	
	/*1. tentar implementar o comando ls como na aula*/ 
		//comando(argfinal);
		//free(args);
	
	/*-----------------------------------------------------------*/

	// separar essa linha
	// executar um comando 
}

