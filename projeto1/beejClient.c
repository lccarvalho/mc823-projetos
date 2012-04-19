/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include "tempo.h"

#define PORT "39410" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 


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



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
	int sockfd, numbytes;  
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];

    struct timeval startTime; //Estrutura contendo o tempo de início de execução
    struct timeval endTime; //Estrutura contendo o tempo final de execução
    double time;
    char parametro[7];//Parametro a ser enviado para o servidor

	if (argc < 3 || argc > 4) {
	    printUsage();
        return 0;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo); // all done with this structure

    //Inicia a contagem de tempo, antes do write (send)
    gettimeofday(&startTime, NULL);

    if(argc == 4){

        strcpy(parametro, argv[2]);
        strcat(parametro, argv[3]); 
    }
    else{

        strcpy(parametro, argv[2]);
    }
	if (send(sockfd, parametro, strlen(parametro), 0) == -1){
		perror("send");
		close(sockfd);
		exit(0);
	}
				
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}

    //Termina a contagem de tempo, após o read (recv)
    gettimeofday(&endTime, NULL);

    time = calculaTempo(startTime, endTime);

	buf[numbytes] = '\0';

	printf("client: received '%s'\n",buf);
    
    printf("\nTotal time: %.2lf microseconds\n", time);

	close(sockfd);

	return 0;
}

