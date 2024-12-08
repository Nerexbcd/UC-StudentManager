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

char * menu_obter_pesquisa() 
{
    char * pesquisa = NULL;
    int rep = 0;

    do
    {
        if (rep!=0) {
            printf("Erro! Tente novamente.\n");
        }
        printf("Pesquisar: ");
        fflush(stdin);
        scanf(" %s",pesquisa);
        puts("");
        rep++;
    }
    while (pesquisa==NULL);

    return pesquisa;
}


char * menu_obter_nacionalidade()
{
    char * nacio = NULL;
    int rep = 0;

    do
    {
        if (rep!=0) {
            printf("Erro! Tente novamente.\n");
        }
        printf("Nacionalidade: ");
        fflush(stdin);
        scanf(" %s",nacio);
        puts("");
        rep++;
    }
    while (nacio==NULL);

    return nacio;
}

char * tipo_de_guardar()
{
    char resposta = NULL;
    char * tipo = NULL;
    int ans = 0;

    printf("Pretende guardar? (S/N)");
    fflush(stdin);
    scanf(" %c",resposta);

    if (resposta=='S' || resposta=='s') {
        int rep = 0;
        do
        {
            if (rep!=0) {
                printf("Erro! Tente novamente.\n");
            }
            printf("Guardar em:\n1 - .txt\n2 - .cvs\nEscolha: ");
            fflush(stdin);
            scanf(" %d",ans);
            if (ans==1) {
                tipo = ".txt";
            }
            else if (ans==2) {
                tipo = ".cvs";
            }
            rep++;
            puts("");
        }
        while ((ans!=1) && (ans!=2));
    }

    else return tipo;
}


float menu_obter_float()
{
    float valor = 0;
    int rep = 0;
    do {
        if (rep!=0) {
            printf("Erro! Tente novamente.\n")
        }
        printf("Valor: ");
        fflush(stdin);
        scanf(" %f",valor);
        puts("");
        rep++;
    }
    while (valor<0);

    return valor;
}