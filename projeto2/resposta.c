#include "resposta.h"
#include<string.h>

#define NUM_MAX_DISCIPLINAS 10
#define TAM_MAX_NOME_DISCIPLINA 120

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que recebe um parâmetro do cliente e, a partir disso, executa
 * as rotinas apropriadas, preparando a resposta adequada a ser enviada ao
 * cliente.
 *
 * @Param buf - string recebida pelo cliente
 *
 * @Returns string com a resposta esperada pelo cliente
 */
/* ----------------------------------------------------------------------------*/
char * preparaResposta(char *buf) {
	char *resposta;
    char *disc;

	if(buf[0] == 'l'){
		return resposta = listaDisciplinas();
    }
    else if(buf[0] == 'p'){
        //Copia a disciplina
        disc= strndup(buf+1, 5);
		return resposta =  programaDisciplina(disc);
    }
    else if(buf[0] == 'i'){
        //Copia a disciplina
        disc = strndup(buf+1, 5);
        if(strcmp(disc, "") ==0){
            //lista as informações de todas as disciplinas
            return resposta = infoDisciplinas();
        }
        else{
            //lista as informações de disc
            return resposta = infoDisciplina(disc);
        }
    }
    else if(buf[0] == 'w'){
        char* comentario;
        //Copia a disciplina
        disc = strndup(buf+1, 5);
        comentario = strndup(buf+6, strlen(buf));
        return resposta = escreveComentario(disc, comentario);
    }
    else if(buf[0] == 'c'){
        //Copia a disciplina
        disc = strndup(buf+1, 5);
        return resposta = leComentario(disc);

    }
	else return resposta = "Algo errado...";
}


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que le os comentários escritos para uma certa disciplina,
 * retornando-os.
 *
 * @Param disc - a sigla da disciplina
 *
 * @Returns uma string com todos os comentários da disciplina
 */
/* ----------------------------------------------------------------------------*/
char* leComentario(char* disc){
    char *info, *resposta;
    int i, sub, cont=0, j=0;
    char *com = "Comentário:";
    //Retorna uma string com todas as informações da disciplina
    info = infoDisciplina(disc);
    sub = strlen(com);
    for (i = 0; i < strlen(info); i++) {
         if((info[i] == com[j]) && (com[j] != '\0')){
             
             cont++;
             j++;
             if(cont == (sub-1)){
                resposta = strndup(info+i+2, strlen(info));
                return resposta;
             }
         }
         else if(com[j] != '\0'){
             cont =0;
             j = 0;
         }
    }

    return "Houve um erro ao obter o comentário.\n";
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que escreve um comentário enviado pelo cliente para o servidor. 
 * A escrita do comentário se dá na disciplina passada pelo cliente, se
 * existir.
 *
 * @Param disc - sigla da disciplina
 * @Param comentario - comentário a ser escrito
 *
 * @Returns String com uma mensagem de sucesso, caso a escrita seja bem
 * sucedida.
 */
/* ----------------------------------------------------------------------------*/
char * escreveComentario( char *disc, char *comentario){
    FILE *fd;
    char text[10];
   /* Normaliza e obtem o nome do arquivo correspondente
     * a disciplina passada como parametro*/
    uppercase(disc);
    strcpy(text, disc);
    strcat(text, ".txt");

    fd = fopen(text, "a+");
    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo da disciplina %s.\n", disc);
        exit(-1);
    }
    else{ 
        fprintf(fd, "%s\n", comentario);
        fclose(fd);
        return "Comentário escrito com sucesso!\n";
    }
}
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que lista todas as disciplinas cadastradas no servidor.
 *
 * @Returns string com as siglas e nomes das disciplinas cadastradas.
 */
/* ----------------------------------------------------------------------------*/
char * listaDisciplinas(){
    FILE *fd;
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

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que retorna ao cliente o programa de uma determinada disciplina,
 * se essa existir.
 *
 * @Param disc - a sigla da disciplina requisitada
 *
 * @Returns   string com o programa da disciplina
 */
/* ----------------------------------------------------------------------------*/
char* programaDisciplina(char* disc){
    
    FILE *fd;
    char texto[10];
    string str;

    /* Normaliza e obtem o nome do arquivo correspondente
     * a disciplina passada como parametro*/
    uppercase(disc);
    strcpy(texto, disc);
    strcat(texto, ".txt");

    fd = fopen(texto, "r");
    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo da disciplina %s.\n", disc);
        exit(-1);
    }
    else{
        char tmp[200];
        char *pch;

        /* Inicializa um vetor contendo a resposta */
        str = str_initialize(((size_t)NUM_MAX_DISCIPLINAS * TAM_MAX_NOME_DISCIPLINA));
        
        /* Le o titulo da disciplina */
        fgets(tmp, sizeof(tmp), fd);

        str_concat_chararr(str, tmp, sizeof(tmp) -1);

        /* Le o resto do arquivo */
        while(fgets(tmp, sizeof(tmp), fd)!=NULL){
            /* Separa a linha lida */
            pch = strtok(tmp, " ");
            /* Imprime a linha lida */
            while(pch !=NULL){
                /* Para a impressao caso se depare com a palavra "Horário:" */
                
                if(strcmp(pch, "Horário:\n") ==0){
                    str_concat_chararr(str, "\n", sizeof(char));
                    fclose(fd);
                    return str->s;
                }
                else{
                    str_concat_chararr(str, pch, strlen(pch));
                    str_concat_chararr(str, " ", sizeof(char));
                }
                pch = strtok(NULL, " ");
                
                
            }
            

        }
        str_concat_chararr(str, "\n", sizeof(char));
        fclose(fd);

        return str->s;
    }
}



/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que retorna as informações de todas as disciplinas cadastradas no
 * servidor.
 *
 * @Returns Uma string com as informações de todas as disciplinas  
 */
/* ----------------------------------------------------------------------------*/
char* infoDisciplinas(){
    
    FILE *fd, *nomefd;
    char *texto;
    string str;
    char nomedisc[200];

    nomefd = fopen("codigo_disciplinas.txt", "r");
    if(nomefd == NULL){
        printf("Erro ao abrir o arquivo com nome das disciplinas.\n");
        exit(-1);
    }
    else{

            /* Inicializa um vetor contendo a resposta */
            str = str_initialize(((size_t)NUM_MAX_DISCIPLINAS * TAM_MAX_NOME_DISCIPLINA));
            while(fgets(nomedisc, sizeof(nomedisc), nomefd) !=NULL){
                /* Normaliza e obtem o nome do arquivo correspondente
                * a disciplina passada como parametro*/
                uppercase(nomedisc);
                texto = strndup(nomedisc, 5);
                strcat(texto, ".txt");

                fd = fopen(texto, "r");
                /* Verifica se a abertura do arquivo foi bem sucedida */
                if(fd == NULL){
                    printf("Erro ao abrir o arquivo da disciplina %s.\n", nomedisc);
                    exit(-1);
                }
                else{
                    char tmp[200];
                    char *pch;

                    /* Le o titulo da disciplina */
                    fgets(tmp, sizeof(tmp), fd);
                    str_concat_chararr(str, tmp, sizeof(tmp) -1);

                    /* Le o resto do arquivo */
                    while(fgets(tmp, sizeof(tmp), fd)!=NULL){
                        /* Separa a linha lida */
                        pch = strtok(tmp, " ");
                        /* Imprime a linha lida */
                        while(pch !=NULL){
                            str_concat_chararr(str, pch, strlen(pch));
                            str_concat_chararr(str, " ", sizeof(char));
                            pch = strtok(NULL, " ");
                
                
                        }
            

                    }
                    str_concat_chararr(str, "\n", sizeof(char));
                    fclose(fd);
            }

        }
            return str->s;

    }
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que retorna ao cliente todas as informações de uma disciplina
 * requisitada, se essa existir.
 *
 * @Param disc - a sigla da disciplina
 *
 * @Returns   string com todas as informações sobre a disciplina
 */
/* ----------------------------------------------------------------------------*/
char* infoDisciplina(char* disc){
    
    FILE *fd;
    char texto[10];
    string str;

    /* Normaliza e obtem o nome do arquivo correspondente
     * a disciplina passada como parametro*/
    uppercase(disc);
    strcpy(texto, disc);
    strcat(texto, ".txt");

    fd = fopen(texto, "r");
    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo da disciplina %s.\n", disc);
        exit(-1);
    }
    else{
        char tmp[200];
        char *pch;

        /* Inicializa um vetor contendo a resposta */
        str = str_initialize(((size_t)NUM_MAX_DISCIPLINAS * TAM_MAX_NOME_DISCIPLINA));
        
        /* Le o titulo da disciplina */
        fgets(tmp, sizeof(tmp), fd);

        str_concat_chararr(str, tmp, sizeof(tmp) -1);

        /* Le o resto do arquivo */
        while(fgets(tmp, sizeof(tmp), fd)!=NULL){
            /* Separa a linha lida */
            pch = strtok(tmp, " ");
            /* Imprime a linha lida */
            while(pch !=NULL){
                str_concat_chararr(str, pch, strlen(pch));
                str_concat_chararr(str, " ", sizeof(char));
                pch = strtok(NULL, " ");
                
                
            }
            

        }
        str_concat_chararr(str, "\n", sizeof(char));
        fclose(fd);
        return str->s;
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que converte todos os caracteres de uma string para letra
 * maiúscula.
 *
 * @Param sPtr - String a ser padronizada
 */
/* ----------------------------------------------------------------------------*/
void uppercase(char* sPtr){
    int i=0;
    while (sPtr[i]) {
        sPtr[i] = toupper((unsigned char)sPtr[i]);
        i++;
    }
}
