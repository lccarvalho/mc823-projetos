/*
 * =====================================================================================
 *
 *       Filename:  tempo.h
 *
 *    Description:  Biblioteca de funções para o cálculo de tempo
 *
 *        Version:  1.0
 *        Created:  04/12/2012 11:06:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gabriel Coutinho Natucci, Luiz Cláudio Carvalho 
 *        Company:  MC823 - Laboratório de Redes
 *
 * =====================================================================================
 */

#include<sys/time.h>


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  Função que realiza o cálculo do tempo percorrido em
 * microsegundos, dado um tempo de início e um tempo de fim.
 *
 * @Param startTime - tempo de início da contagem
 * @Param endTime - tempo de fim da contagem
 *
 * @Returns   tempo percorrido em microsegundos
 */
/* ----------------------------------------------------------------------------*/
double calculaTempo(struct timeval startTime, struct timeval endTime);

