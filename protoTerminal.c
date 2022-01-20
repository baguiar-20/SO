#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // inclui o PATH_MAX
#include <string.h> 

//criando diretorio
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_RESET  "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"


typedef struct{
    char username[30];
    char computer[30];
    char local[255];
}User;



void command_treatment(char command[]){ // faz o tratamento da string passada no terminal
    size_t len = strlen(command);
    if (len > 0 && command[len-1] == '\n') {
        command[--len] = '\0';
    }
}

User * path_treatment(char path[]){
    User *user;


    return user;

}


void path_dir_terminal(){
    char path[PATH_MAX];
    char * pU = getenv("USER");
    char pH[HOST_NAME_MAX + 1];
    gethostname(pH, HOST_NAME_MAX + 1);;

    printf("%s%s@%s%s:%s~%s$ ", ANSI_COLOR_GREEN, pU, pH, ANSI_COLOR_RESET, ANSI_COLOR_BLUE, ANSI_COLOR_RESET);

//     if (getcwd(path, sizeof(path)) != NULL) { // pega p diretorio 
//     //    printf("%sfulano@ciclano:~/ ", ANSI_COLOR_GREEN);
//         // printf("%s\n", path);
        

//     } else {
//        perror("getcwd() error");
//    }
}

int main(){

    FILE *fp = fopen("user.txt", "r");
    char texto_str[20];

    char command[255];

    path_dir_terminal();
    
    while(fgets(command, sizeof command, stdin)){
        //printf("%s", command); // so pa teste
        
        command_treatment(command);

        if(strcmp(command, "ls") == 0){
            printf("abluble_das_ideia.cpp\n");
            path_dir_terminal();
            //continue;
        }
        else if(strcmp(command, "pwd") == 0){
            path_dir_terminal();
        }

        else if(strcmp(command, "exit") == 0){
            exit(1);
        }
        else{
            printf("command not found: %s\n", command);
            path_dir_terminal();
        }
    }
   

    return 0;

}
