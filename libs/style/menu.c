#include "menu.h"
#include "../utils/string_util.h"
#include "../style/colors.h"


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
    char * pesquisa = malloc(sizeof(char)*50);
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
    char * nacio = malloc(sizeof(char)*100);;
    int rep = 0;
    
    do
    {
        if (rep!=0) {
            printf("Erro! Tente novamente.\n");
        }
        printf("Nacionalidade (se nenhuma, escreva 0): ");
        fflush(stdin);
        scanf("%s",nacio);
        rep++;
    }
    while (nacio==NULL);

    return nacio;
}

char * tipo_de_guardar()
{
    char * resposta = malloc(sizeof(char));
    char * tipo = malloc(sizeof(char)*4);
    int ans = 0;

    printf("Pretende guardar em ficheiro? (S/N) ");
    fflush(stdin);
    scanf(" %s",resposta);

    if (strcmp(resposta,"s")==0 || strcmp(resposta,"S")==0) {
        int rep = 0;
        do
        {
            if (rep!=0) {
                printf("Erro! Tente novamente.\n");
            }
            printf("Guardar em:\n1 - .txt\n2 - .cvs\nEscolha: ");
            fflush(stdin);
            scanf(" %d",&ans);
        
            if (ans==1) {
                tipo = strdup(".txt");
                return tipo;
            }
            else if (ans==2) {
                tipo = strdup(".cvs");
                return tipo;
            }
            rep++;
            puts("");
        }
        while ((ans!=1) && (ans!=2));
    }
    else {
        return "0000";
    }
}


float menu_obter_float()
{
    float valor = 0;
    int rep = 0;
    do {
        if (rep!=0) {
            printf("Erro! Tente novamente.\n");
        }
        printf("Valor de media: ");
        fflush(stdin);
        scanf(" %f",&valor);
        rep++;
    }
    while (valor<0);

    return valor;
}


int escolher_codigo(ALUNO * base_dados)
{
    int n;
    int cod;
    char ans;
    int pos;

    do {
        printf("\nQual é o código do aluno? ");
        fflush(stdin);
        scanf(" %i", &cod);
        

        for (int pos = 0; pos<sizeof(base_dados); pos++) {
            if (base_dados[pos].ocupado==1 && base_dados[pos].codigo==cod) {
                printf("\nAluno:\n");
                mostrar_um_aluno(base_dados,pos);
                printf("\nCorreto (S/N)? ");
                scanf(" %c", &ans);
                
                if (ans=='s' || ans=='S') {
                    return pos;
                }
            }
        }

    }
    while(1);

}