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
int menu_opcoes_field();

#endif

