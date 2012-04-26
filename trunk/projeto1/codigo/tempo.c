/*
 * =====================================================================================
 *
 *       Filename:  tempo.c
 *
 *    Description:  Implementação das funções de tempo descritas na biblioteca
 *    "tempo.h"
 *
 *        Version:  1.0
 *        Created:  04/12/2012 11:11:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gabriel Coutinho Natucci, Luiz Cláudio Carvalho 
 *        Company:  MC823 - Laboratório de Redes
 *
 * =====================================================================================
 */

#include "tempo.h"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que calcula o tempo transcorrido entra dois intervalos
 *
 * @Param startTime - inicio do intervalo de tempo
 * @Param endTime - fim do intervalo de tempo
 *
 * @Returns   um double contendo a variação do tempo
 */
/* ----------------------------------------------------------------------------*/
double calculaTempo(struct timeval startTime, struct timeval endTime)
{
    double inicio, fim;

    //Converte os tempos para milisegundos
    inicio = startTime.tv_sec*1000000 + (startTime.tv_usec);
    fim = endTime.tv_sec*1000000 + (endTime.tv_usec);

    return (fim - inicio);
}

