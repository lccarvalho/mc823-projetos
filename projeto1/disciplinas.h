/*
 * =====================================================================================
 *
 *       Filename:  disciplinas.h
 *
 *    Description: Biblioteca das funções de disciplinas cadastradas
 *
 *        Version:  1.0
 *        Created:  04/06/2012 03:26:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gabriel Coutinho Natucci, Luiz Cláudio Carvalho
 *        Company:  MC823
 *
 * =====================================================================================
 */


#include "str.h"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que busca o código e nomes das disciplinas no arquivo
 * "codigo_disciplinas.txt"
 *
 * @Returns str - vetor de strings com nomes e códigos das disciplinas   
 */
/* ----------------------------------------------------------------------------*/
string *codigo_disc();

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função que imprime os códigos e nomes das disciplinas cadastradas
 *
 * @Param disc - Estrutura com as disciplinas.
 */
/* ----------------------------------------------------------------------------*/
void imprime_codigo(string *disc);

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *Função que converte os caracteres de uma string para maiúscula.
 *
 * @Param sPtr - string a ser normalizada
 */
/* ----------------------------------------------------------------------------*/
void uppercase(char *sPtr);


void programa(char* disc);

void detalhes_disc(char* disc);
