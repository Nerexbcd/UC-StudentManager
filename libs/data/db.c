#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "db.h"
#include "../env/aluno.h"
#include "../data/txt_files.h"
#include "../style/colors.h"
#include "../style/menu.h"
#include "../utils/string_util.h"

// ------------------------------ DB Initialization

DB *db_init(size_t size_alunos) {

    //alocar memória necessária para todos os elementos da lista
    ALUNO *wrt_alunos = malloc(sizeof(ALUNO)*((size_alunos)+1));

    for (int i=0 ; i<=(size_alunos) ; i++) {
        int z=0;
        wrt_alunos[i].nome=NULL;
        wrt_alunos[i].nacionalidade=NULL;
    }

    DB *base_dados = malloc(sizeof(DB));
    base_dados->alunos = wrt_alunos;
    base_dados->size = size_alunos;
    
    return base_dados;
}


void db_load_data(txtFile file_estudante, txtFile file_situacao, DB *base_dados)
{
    for (int i=0; i < base_dados->size ; i++) {
        char *linha = txt_get_line(file_estudante, i);
        char **dados = str_split(linha, '\t', NULL);

        base_dados->alunos[i].codigo = atoi(strdup(dados[0]));
        base_dados->alunos[i].nome = strdup(dados[1]);
        base_dados->alunos[i].nacionalidade = strdup(dados[3]);

        char *dn = dados[2];
        char **ptr_dn = str_split(dn, '-', NULL);
        base_dados->alunos[i].data_n.dia= atoi(strdup(ptr_dn[0]));
        base_dados->alunos[i].data_n.mes= atoi(strdup(ptr_dn[1]));
        base_dados->alunos[i].data_n.ano= atoi(strdup(ptr_dn[2]));
    }

    for (int i=0; i < txt_get_size(file_situacao) ; i++) {
        char *linha = file_situacao.data[i];
        char **dados = str_split(linha, '\t', NULL);

        for (int j=0 ; j<base_dados->size ; j++) {
            if (atoi(dados[0]) == base_dados->alunos[j].codigo) {
                
                base_dados->alunos[j].n_matriculas= atoi(strdup(dados[1]));
                base_dados->alunos[j].ects_concluidos= atoi(strdup(dados[2]));
                base_dados->alunos[j].ano_curso= atoi(strdup(dados[3]));
                base_dados->alunos[j].media_atual= atof(strdup(dados[4]));
            }
        }
    }
}


// ------------------------------ DB Manipulation

void db_insert(DB *base_dados, ALUNO aluno)
{
    // Setup work variables
    size_t wrt_size = base_dados->size+1;
    ALUNO * wrt_alunos = base_dados->alunos;
    wrt_alunos = realloc(wrt_alunos , sizeof(ALUNO)*((wrt_size)+1));

    //atribuir valores
    wrt_alunos[wrt_size-1].codigo=aluno.codigo;
    wrt_alunos[wrt_size-1].nome=aluno.nome;
    wrt_alunos[wrt_size-1].nacionalidade=aluno.nacionalidade;
    wrt_alunos[wrt_size-1].data_n=aluno.data_n;

    wrt_alunos[wrt_size-1].ano_curso=aluno.ano_curso;
    wrt_alunos[wrt_size-1].media_atual=aluno.media_atual;
    wrt_alunos[wrt_size-1].ects_concluidos=aluno.ects_concluidos;
    wrt_alunos[wrt_size-1].n_matriculas=aluno.n_matriculas;
    
    // Save Changes
    base_dados->alunos = wrt_alunos;
    base_dados->size = wrt_size;

    

    

    

    // printf("Codigo: ");
    // scanf(" %d",&((lista_estudantes[j]).codigo));

    // char * stringgg=NULL;
    // size_t bufsize=200;
    // printf("Nome: ");
    // fflush(stdin);
    // //não consegui usar o scanf ou gets (?????????????porquê?????)
    // getline(&stringgg,&bufsize,stdin);
    // stringgg = * str_split(stringgg, '\n', NULL);
    // lista_estudantes[j].nome=(char*) malloc(sizeof(stringgg));
    // lista_estudantes[j].nome=stringgg;
    // fflush(stdin);
    
    // stringgg=NULL;
    // bufsize=11;
    // printf("Data de nascimento (dd-mm-aaaa): ");
    // fflush(stdin);
    // getline(&stringgg,&bufsize,stdin);
    // stringgg = * str_split(stringgg, '\n', NULL);
    // char *dn = stringgg;
    // char **ptr_dn = str_split(dn, '-', NULL);
    // lista_estudantes[j].data_n.dia= atoi(strdup(ptr_dn[0]));
    // lista_estudantes[j].data_n.mes= atoi(strdup(ptr_dn[1]));
    // lista_estudantes[j].data_n.ano= atoi(strdup(ptr_dn[2]));

    // fflush(stdin);

    // stringgg=NULL;
    // bufsize=200;
    // printf("Nacionalidade: ");
    // fflush(stdin);
    // getline(&stringgg,&bufsize,stdin);
    // stringgg = * str_split(stringgg, '\n', NULL);
    // lista_estudantes[j].nacionalidade=(char*) malloc(sizeof(stringgg));
    // lista_estudantes[j].nacionalidade=stringgg;
    // fflush(stdin);

    // printf("Ano de curso: ");
    // fflush(stdin);
    // scanf(" %d",&((lista_estudantes[j]).ano_curso));

    // printf("Media atual: ");
    // fflush(stdin);
    // scanf(" %f",&((lista_estudantes[j]).media_atual));

    // printf("ECTS concluidos: ");
    // fflush(stdin);
    // scanf(" %d",&((lista_estudantes[j]).ects_concluidos));

    // printf("Numero de matriculas: ");
    // fflush(stdin);
    // scanf(" %d",&((lista_estudantes[j]).n_matriculas));

    // puts("\n");
    // fflush(stdin);

    //para esvaziar a memória alocada no caso de não ser necessária

}




void db_remove(DB *base_dados, int index)
{
    // Setup work variables
    size_t wrt_size = base_dados->size;
    ALUNO * wrt_alunos = base_dados->alunos;

    wrt_alunos[index] = wrt_alunos[wrt_size-1];

    wrt_size--;

    wrt_alunos = realloc(wrt_alunos , sizeof(ALUNO)*((wrt_size)+1));

    // Save Changes
    base_dados->alunos = wrt_alunos;
    base_dados->size = wrt_size;
}

void db_update(DB *base_dados, int index, ALUNO aluno)
{
    // Setup work variables
    ALUNO * wrt_alunos = base_dados->alunos;

    wrt_alunos[index] = aluno;

    // Save Changes
    base_dados->alunos = wrt_alunos;
}

ALUNO db_get(DB *base_dados, int index)
{
    ALUNO aluno = (ALUNO) base_dados->alunos[index];
    return aluno;
}