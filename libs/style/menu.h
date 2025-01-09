#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../env/student.h"
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


//MENUS SECUNDÁRIOS

//permite ao utilizador escolher qual o campo a alterar
int menu_opcoes_field();

//efetua a obtencao de uma pesquisa válida fornecida pelo utilizador
char * menu_obter_pesquisa();

//efetua a obtencao de uma nacionalidade válida fornecida pelo utilizdor
char * menu_obter_nacionalidade();

//determina se o utilizador pretende guardar o resultado obtido, e se sim em .txt ou .cvs
char * tipo_de_guardar();

//obtem um valor float positivo do utilizador
float menu_obter_float();

//obtem o codigo do student a remover
int escolher_codigo(STUDENT * base_dados);

#endif


