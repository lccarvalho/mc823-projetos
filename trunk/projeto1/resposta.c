


#include "resposta.h"
#include<string.h>

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


char* leComentario(char* disc){
    char *info, *resposta;
    int i, sub, cont=0, j=0;
    char *com = "Comentário:";
    //Retorna uma string com todas as informações da disciplina
    info = infoDisciplina(disc);
    sub = strlen(com);
    for (i = 0; i < strlen(info); i++) {
         if((info[i] == com[j]) && (com[j] != '\0')){
             printf("%c\n", info[i]);
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
char * escreveComentario( char *disc, char *comentario){
    FILE *fd;
    char *text;
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


char* retiraSubstring( char* str, int lenstr, char* sub, int lensub){
    int i, cont=0, j=0;
    char *novastr;

    for (i = 0; i < lenstr; i++) {
        if((str[i]==sub[j]) && (sub[j] != '\0')){
            cont++;
            j++;
            if(cont == (lensub-1)){
                novastr = strndup(str, i - j);
                return novastr;
            }
        }
        else if(sub[j] != '\0'){
            cont=0;
            j=0;
        }
    }
    return "";
}
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
        //printf("%s\n", tmp);
        str_concat_chararr(str, tmp, sizeof(tmp) -1);

        /* Le o resto do arquivo */
        while(fgets(tmp, sizeof(tmp), fd)!=NULL){
            /* Separa a linha lida */
            pch = strtok(tmp, " ");
            /* Imprime a linha lida */
            while(pch !=NULL){
                /* Para a impressao caso se depare com a palavra "Horário:" */
                /*  if(!verificaSubstring(pch, strlen(pch), "Horário:", strlen("Horário:"))){
                    fclose(fd);
                    char *substr = retiraSubstring(pch, strlen(pch), "Horário:", strlen("Horário:"));
                    str_concat_chararr(str, substr, strlen(substr));
                    str_concat_chararr(str,"\n", sizeof(char));
                    return str->s;
                }*/
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
        //printf("%s\n", tmp);
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

void uppercase(char* sPtr){
    int i=0;
    while (sPtr[i]) {
        sPtr[i] = toupper((unsigned char)sPtr[i]);
        i++;
    }
}

int verificaSubstring( char* str, int lenstr, char* sub, int lensub){
    int i, j=0, cont=0;


    for (i = 0; i < lenstr; i++) {
         if((str[i] == sub[j]) && (sub[j] != '\0')){
             cont++;
             j++;
             if(cont == (lensub-1)){
                return 0;
             }
         }
         else if(sub[j] != '\0'){
             cont =0;
             j = 0;
         }
    }
    return 1;
}

