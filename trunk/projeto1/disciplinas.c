/*
 * =====================================================================================
 *
 *       Filename:  disciplinas.c
 *
 *    Description:  Funções para obter informações sobre as disciplinas
 *    cadastradas.
 *
 *        Version:  1.0
 *        Created:  04/06/2012 02:47:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gabriel Coutinho Natucci, Luiz Cláudio Carvalho 
 *        Company:  MC823
 *
 * =====================================================================================
 */

#include "disciplinas.h"

string *codigo_disc(){

    FILE *fd;
    string *str;
    int i=0;
    /* Inicializa um vetor de strings, para conter as disciplinas */
    str = (string*)xmalloc(10*sizeof(struct str));
    for (i = 0; i < 10; i++) {
        str[i] = str_initialize(((size_t)120));
    }

    /*Abre o arquivo de codigos das disciplinas*/
    fd = fopen("codigo_disciplinas.txt", "r");

    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo com codigos das disciplinas.\n");
        exit(-1);
    }
    else{
        char temp[120], *w;
        i=0;
        int r;
        /*Arquivo aberto com sucesso*/
        while(fgets(temp, sizeof(temp), fd) != NULL){
            
            
            /*Passa a string lida para a estrutura de strings*/
            str_concat_chararr(str[i], temp, strlen(temp)-1);
            i++;
            

        }
        fclose(fd);
    }
    return str; 
}

void programa(char* disc){
    
    FILE *fd;
    char texto[10];


    /* Normaliza e obtem o nome do arquivo correspondente
     * a disciplina passada como parametro*/
    uppercase(disc);
    strcpy(texto, disc);
    strcat(texto, ".txt");

    fd = fopen(texto, "r");
    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo com codigos das disciplinas.\n");
        exit(-1);
    }
    else{
        char tmp[200];
        char *pch;
        
        /* Le o titulo da disciplina */
        fgets(tmp, sizeof(tmp), fd);
        printf("%s\n", tmp);
        
        /* Le o resto do arquivo */
        while(fgets(tmp, sizeof(tmp), fd)!=NULL){
            /* Separa a linha lida */
            pch = strtok(tmp, "\n");
            /* Imprime a linha lida */
            while(pch !=NULL){
                /* Para a impressao caso se depare com a palavra "Horário:" */
                if(!strcmp(pch, "Horário:")){
                    fclose(fd);
                    return;
                }
                printf("%s\n", pch);
                pch = strtok(NULL, "\n");
            }

        }
        fclose(fd);
    }
}


void detalhes_disc(char* disc){
    
    FILE *fd;
    char texto[10];


    /* Normaliza e obtem o nome do arquivo correspondente
     * a disciplina passada como parametro*/
    uppercase(disc);
    strcpy(texto, disc);
    strcat(texto, ".txt");

    fd = fopen(texto, "r");
    /* Verifica se a abertura do arquivo foi bem sucedida */
    if(fd == NULL){
        printf("Erro ao abrir o arquivo com codigos das disciplinas.\n");
        exit(-1);
    }
    else{
        char tmp[200];
        char *pch;
        
        /* Le o titulo da disciplina */
        fgets(tmp, sizeof(tmp), fd);
        printf("%s\n", tmp);
        
        /* Le o resto do arquivo */
        while(fgets(tmp, sizeof(tmp), fd)!=NULL){
            /* Separa a linha lida */
            pch = strtok(tmp, "\n");
            /* Imprime a linha lida */
            while(pch !=NULL){

                if(!strcmp(pch, "Horário:") || !strcmp(pch, "Sala de Aula:") || !strcmp(pch, "Professor:")){
                    printf("\n");
                }
                printf("%s\n", pch);
                pch = strtok(NULL, "\n");
            }

        }
        fclose(fd);
    }
}

void imprime_codigo(string *disc){
    int i;

    for (i = 0; i < 10; i++) {
        printf("%s\n", disc[i]->s);
    }
}


void uppercase(char* sPtr){
    int i=0;
    while (sPtr[i]) {
        sPtr[i] = toupper((unsigned char)sPtr[i]);
        i++;
    }
}
