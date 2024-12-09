#include "menu.h"

void menu_header() {

}

/***
 *    ██╗   ██╗ ██████╗      ███████╗████████╗██╗   ██╗██████╗ ███████╗███╗   ██╗████████╗███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗ 
 *    ██║   ██║██╔════╝      ██╔════╝╚══██╔══╝██║   ██║██╔══██╗██╔════╝████╗  ██║╚══██╔══╝████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗
 *    ██║   ██║██║     █████╗███████╗   ██║   ██║   ██║██║  ██║█████╗  ██╔██╗ ██║   ██║   ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝
 *    ██║   ██║██║     ╚════╝╚════██║   ██║   ██║   ██║██║  ██║██╔══╝  ██║╚██╗██║   ██║   ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗
 *    ╚██████╔╝╚██████╗      ███████║   ██║   ╚██████╔╝██████╔╝███████╗██║ ╚████║   ██║   ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║
 *     ╚═════╝  ╚═════╝      ╚══════╝   ╚═╝    ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
 *                                                                                                                                                 
 */


int menu_opcoes_field()
{
    int i=0;
    do {
    if (i<0 || i>7) {
        printf("Erro! Insira um valor válido!");
    }
    printf("O que pretende alterar? Escreva um numero.\n0 - codigo\n1 - ECTS concluidos\n2 - Ano do curso\n3 - Media atual\n4 - Nome\n5 - Nacionalidade\n6 - Data de nascimento\n7 - Numero de matriculas\n");
    fflush(stdin);
    scanf(" %d",&i);
    }
    while (i<0 || i>7);
    return i;
}


int menu_show_page(MENU_PAGE * page) {

    char **strs = malloc(sizeof(char*) * 4);
    strs[0] = page->option_1;
    strs[1] = page->option_2;
    strs[2] = page->option_3;
    strs[3] = page->option_4;

    int bigger = str_get_bigger(strs,4)-4;

    printf("\n┏");
    for (int i = 0; i < bigger; i++) { 
        printf("━");
    }
    printf("┓\n");

    printf("┃ %s",page->title);
    for (int j = 0; j < bigger-strlen(page->title); j++) {
        printf(" ");
    }
    printf("┃\n");

    printf("┣");
    for (int i = 0; i < bigger; i++) {
        printf("━");
    }
    printf("┫\n");

    for (int i = 0; i < 3; i++) {
        printf("┃ %u -> %s",i+1,strs[i]);
        for (int j = 0; j < bigger-strlen(strs[i]); j++) {
            printf(" ");
        }
        printf("┃\n");
    }

    printf("┃ 0 -> Voltar");
    for (int j = 0; j < bigger-strlen(" 0 -> Voltar"); j++) {
        printf(" ");
    }



    printf("┗");
    for (int i = 0; i < bigger; i++) {
        printf("━");
    }
    printf("┛\n");

    



/*     printf("%s\n", page->title);
    printf("1 - %s\n", page->option_1);
    printf("2 - %s\n", page->option_2);
    printf("3 - %s\n", page->option_3);
    printf("4 - %s\n", page->option_4);
    printf("\n"); */
    int i = 0;
    do {
        if (i<0 || i>4) {
            printf("Erro! Insira uma Opção válida!");
        }
        printf("Escolha uma opção: ");
        fflush(stdin);
        scanf(" %d",&i);
    }
    while (i<0 || i>4);
    return i;
}