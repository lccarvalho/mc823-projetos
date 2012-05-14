/*
** talker.c -- a datagram "client" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "str.h"

#define SERVERPORT "4950"    // the port users will be connecting to

#define MAXBUFLEN 1500



/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que imprime o modo de usar o programa
 */
/* ----------------------------------------------------------------------------*/
void printUsage() {
    printf("\nclient.o  [porta] [comando] [param] [texto]\n");
    
   
    printf("\ncomandos:\n");
    printf("\n    l : lista os codigos e nomes das disciplinas cadastradas");
    printf("\n    p [param] : retorna o programa da disciplina [param]");
    printf("\n    i [param] : retorna  todas as informacoes sobre a disciplina [param]");
    printf("\n                 se [param] nao for fornecido, retorna todas as informacoes");
    printf("\n                 de todas as disciplinas cadastradas");
    printf("\n    w [param] [texto] : recebe e armazena o texto de um comentario sobre a proxima");
    printf("\n                 aula da disciplina [param]");
    printf("\n    c [param] : retorna o comentario armazenado sobre a proxima aula da");
    printf("\n                 disciplina [param]\n");
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    char buf[MAXBUFLEN];
    char *resposta;
    string parametro;

    /* Estruturas para o calculo do tempo */
    struct timeval startTime;
    struct timeval endTime;
    double time;


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "talker: failed to bind socket\n");
        return 2;
    }

    //Inicializa a string a ser enviada ao servidor
    parametro = str_initialize(((size_t)MAXBUFLEN));
    //Funções envolvendo disciplinas específicas
    if(argc == 4){

        str_concat_chararr(parametro, argv[2], strlen(argv[2]));
        str_concat_chararr(parametro, argv[3], strlen(argv[3])); 
    }
    //Escrever comentário
    else if(argc == 5){
        str_concat_chararr(parametro, argv[2], strlen(argv[2]));
        str_concat_chararr(parametro, argv[3], strlen(argv[3]));
        str_concat_chararr(parametro, argv[4], strlen(argv[4]));
    }
    else{

        str_concat_chararr(parametro, argv[2], strlen(argv[2]));
    }

    /* Inicio do calculo do tempo, antes do send */
    gettimeofday(&startTime, NULL);

    if ((numbytes = sendto(sockfd, parametro->s, str_cur_size(parametro), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }

    //freeaddrinfo(servinfo);

    printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    
    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
                (struct sockaddr *)&p->ai_addr, &p->ai_addrlen)) == -1) {
            perror("recvfrom");
            exit(1);
        }
    /*Termino do calculo do tempo, apos o recv  */
    gettimeofday(&endTime, NULL);

    time = calculaTempo(startTime, endTime);
    resposta = strndup(buf, numbytes); 
    printf("Response contains \"%s\"\n", resposta);
    printf("\nTotal Time: %.2lf microseconds\n", time);
    close(sockfd);

    return 0;
}
