


#include "resposta.h"

#define NUM_MAX_DISCIPLINAS 10
#define TAM_MAX_NOME_DISCIPLINA 120

char * preparaResposta(char *buf) {
	char *resposta;
    char *disc;

	if(buf[0] == 'l'){
		return resposta = listaDisciplinas();
    }
    else if(buf[0] == 'p'){
        //Copia a disciplina
        disc= strndup(buf+1, 5);
		return resposta = disc;
    }
	else return resposta = "Algo errado...";
}

char * listaDisciplinas(){
    FILE *fd;
    //string *str;
	string str;
    int i=0;
    
    /* Inicializa uma string para conter as disciplinas */

    str = str_initialize(((size_t)NUM_MAX_DISCIPLINAS * TAM_MAX_NOME_DISCIPLINA));


    /*Abre o arquivo de codigos das disciplinas*/
    fd = fopen("codigo_disciplinas.txt", "r");

    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo com codigos das disciplinas.\n");
        exit(-1);
    }
    else{
        /*Arquivo aberto com sucesso*/ 
        char temp[120];
        i=0;
        
        while(fgets(temp, sizeof(temp), fd) != NULL){
                    
            /*Passa a string lida para a estrutura de strings*/
            str_concat_chararr(str, temp, strlen(temp)-1);
			str_concat_chararr(str, "\n", sizeof(char));
            i++;
        }
        fclose(fd);
    }
    return str->s; 
}

