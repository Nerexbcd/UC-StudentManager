#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


typedef struct menu_page
{
    char * title;
    char * option_1;
    char * option_2;
    char * option_3;
    char * option_4;
}MENU_PAGE;



//MENUS SECUNDÁRIOS

//permite ao utilizador escolher qual o campo a alterar
int menu_opcoes_field();

//efetua a obtencao de uma pesquisa válida fornecida pelo utilizdor
char * menu_obter_pesquisa(char * pesquisa);

//efetua a obtencao de uma nacionalidade válida fornecida pelo utilizdor
char * menu_obter_nacionalidade(char * nacio);

//determina se o utilizador pretende guardar o resultado obtido, e se sim em .txt ou .cvs
char * tipo_de_guardar();

//obtem um valor float positivo do utilizador
float menu_obter_float();

//obtem o codigo do aluno a remover
int escolher_codigo();

#endif


