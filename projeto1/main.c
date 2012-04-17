/* MC823 - Laboratório de Teleprocessamento e Redes
   Unicamp - 1o semestre 2012
   Professor Edmundo Madeira
   Projeto 1: Servidor concorrente sobre TCP
   Grupo:
         Gabriel Coutinho Natucci  091247
         Luiz Claudio Carvalho     800578
   Data de entrega: 19/04/2012
   */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplinas.h"


/*uso:
    823project1 [conexão] [comando] [param] 
    
    conexão: arquivo com parâmetros de acesso ao servidor (a definir)
    
    comandos:
        -l : lista os códigos e nomes das disciplinas cadastradas
        -p [param] : retorna o programa da disciplina [param]
        -i [param] : retorna  todas as informações sobre a disciplina [param]
                     se [param] não for fornecido, retorna todas as informações
                     de todas as disciplinas cadastradas
        -w [param] : recebe e armazena o texto de um comentário sobre a próxima
                     aula da disciplina [param]
        -c [param] : retorna o comentário armazenado sobre a próxima aula da
                     disciplina [param]
*/

void printUsage() {
    printf("\n823project1 [conexao] [comando] [param]\n");
    
    printf("\nconexao: arquivo com parametros de acesso ao servidor (a definir)\n");
    
    printf("\ncomandos:\n");
    printf("\n    -l : lista os codigos e nomes das disciplinas cadastradas");
    printf("\n    -p [param] : retorna o programa da disciplina [param]");
    printf("\n    -i [param] : retorna  todas as informacoes sobre a disciplina [param]");
    printf("\n                 se [param] nao for fornecido, retorna todas as informacoes");
    printf("\n                 de todas as disciplinas cadastradas");
    printf("\n    -w [param] : recebe e armazena o texto de um comentario sobre a proxima");
    printf("\n                 aula da disciplina [param]");
    printf("\n    -c [param] : retorna o comentario armazenado sobre a proxima aula da");
    printf("\n                 disciplina [param]\n");
} 

int main(int argc, char *argv[])
{
   if(!strcmp(argv[2],"-l")) {       //argv[2] = -l
       //printf("\nTODO: Imprimir codigos e titulos de todas as disciplinas\n");
       string *str;
       str = codigo_disc();
       imprime_codigo(str);
       return 0;
   }
   if(!strcmp(argv[2],"-p")) {       
       if(argc == 4) {
           //printf("\nTODO: Imprimir o programa de %s\n", argv[3]);
           programa(argv[3]);
           return 0;
       } else {
           printUsage();
           return 0;
       }
   }
   if(!strcmp(argv[2],"-i")) {       
       if(argc == 4) {
           //printf("\nTODO: Imprimir as informacoes de %s\n", argv[3]);
           detalhes_disc(argv[3]);
           return 0;
       } else {
           printf("\nTODO: Imprimir as informacoes de todas as disciplinas\n");
           return 0;
       }
   }
   if(!strcmp(argv[2],"-w")) {       
       if(argc == 4) {
           printf("\nTODO: Receber comentario prox. aula de %s\n", argv[3]);
           return 0;
       } else {
           printUsage();
           return 0;
       }
   }
   if(!strcmp(argv[2],"-c")) {       
       if(argc == 4) {
           printf("\nTODO: Imprimir comentario prox. aula de %s\n", argv[3]);
           return 0;
       } else {
           printUsage();
           return 0;
       }
   }
   printUsage();
   return 0;
}
