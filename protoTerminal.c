#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // inclui o PATH_MAX
#include <string.h> 

//criando diretorio
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_RESET  "\x1b[0m"
#define ANSI_COLOR_BLUE   "\x1b[34m"

#define BUFFER_INSTR 255 // quantidade de instruçoes


/*
Sistemas Operacionais -2021/1
Data: 01/02/2022
Trabalho 1 - Proto-terminal
Equipe: Brenda Aguiar, Elizamara Almeida, Jessica Brito

/*

Funciona:
- cd, ls, pwd
- gcc 
- ./teste
- cat coelho.c
- enter nao da segment fault
- ./prog1 arg1 arg2 // passar argumentos no terminal

Tratar
- execução do arquivo de saída do compilador
ex: teste
-  prog1

- ./prog1 & 
- ./prog1 > saída 


Falta testar
-  cat, more, head e afins
- >, <, | e &.


*/





char ** command_treatment(char command[]){ // faz o tratamento da string passada no terminal
    size_t len = strlen(command);
    int count = 0;
    char **instr;
    instr = malloc((len+1)*sizeof(char));

    char *token = strtok(command, " \n");// cd downloads/

    while(token) {
        instr[count] = token;
        count++;
        if(count >= len){
			len = len * 2; 
			instr = realloc(instr,len*sizeof(char));
		}

        token = strtok(NULL, " \n");
    }

    return instr; // retorna uma matriz de instrução
}




void path_dir_terminal(){ // mostra o diretorio 
    DIR *dp;
    struct dirent *dir;
    char * username = getenv("USER");
    char hostname[HOST_NAME_MAX + 1];
    char PATH[BUFFER_INSTR];

    gethostname(hostname, HOST_NAME_MAX + 1);   
    getcwd(PATH, sizeof(PATH));
    printf("%s%s$%s ", PATH, ANSI_COLOR_GREEN, ANSI_COLOR_RESET);

     
}






void commands(char ** args){

	int rc = fork();
	if (rc < 0) {
	    fprintf(stderr, "fork falhou\n");
	    exit(1);
	} 
    else if (rc == 0) {
	    execvp(args[0], args);		
	    printf("Comando não encontrado\n");
	} 
    else{
	    int wc = wait(NULL);
	}
}

int main(int argc, char *argv[]){

    char command[255];
    
    char ** matrix_instr = malloc(BUFFER_INSTR * sizeof(char*));

    
    path_dir_terminal();

    
    while(fgets(command, sizeof command, stdin) ){
        

        if(strcmp(command, "\n") == 0){
            strcpy(command, "\0");
            path_dir_terminal();
        }

        else{
            matrix_instr = command_treatment(command);

            if(strcmp(matrix_instr[0], "exit") == 0){
                exit(1);
            }
            else if(strcmp(matrix_instr[0], "cd") == 0){
                if(matrix_instr[1] != NULL){
                    chdir(matrix_instr[1]);
                }
                path_dir_terminal();
            }
            else{
                commands(matrix_instr);
                path_dir_terminal();
            } 

            free(matrix_instr);
        }
        
    }

    return 0;

}
