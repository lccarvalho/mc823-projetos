/*
 * resposta.h - prepara as respostas a serem enviadas pelo servidor de disciplinas
 */


#include "str.h"

char * preparaResposta(char *buf);

char * listaDisciplinas();

char * infoDisciplinas();

char * infoDisciplina(char * disc);

char * programaDisciplina(char* disc); 

void uppercase(char* sPtr);

char * retiraSubstring(char* str, int lenstr, char* sub, int lensub);

int verificaSubstring(char* str, int lenstr, char* sub, int lensub);

