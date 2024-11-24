#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "../utils/string_util.h"
#include "../style/colors.h"


void inserir_estudante(ALUNO *lista_estudantes,int i,char *txt)
{
    int j;
    for (j=0;j<=sizeof(lista_estudantes);j++) {
        if ((lista_estudantes[j]).ocupado==0) {
        (lista_estudantes[j]).ocupado=1;
        (lista_estudantes[j]).codigo=0;
        (lista_estudantes[j]).ects_concluidos=0;
        (lista_estudantes[j]).ano_curso=0;
        (lista_estudantes[j]).media_atual=0;
        (lista_estudantes[j]).nome;
        (lista_estudantes[j]).nacionalidade;
        (lista_estudantes[j]).data_n;
        break;
        }
    }
}

void remover_estudante(ALUNO *lista_estudantes,int i)
{
    (lista_estudantes[i]).ocupado=0;
}

void atualizar_estudante(ALUNO *lista_estudantes,int i)
{
    
}
