#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED
#include "../data/txt_files.h"
#include "../env/aluno.h"


typedef struct db
{
    ALUNO *alunos;
    size_t size;
}DB;

//Transfere os dados dos ficheiros para a struct base de dados do tipo ALUNO
void db_load_data(txtFile file_estudante, txtFile file_situacao, DB *base_dados);

//Cria e inicializa a lista de estudantes
DB *db_init(size_t size_alunos);

//Permite adicionar um aluno à lista
void db_insert(DB *base_dados, ALUNO aluno);

//Permite remover um aluno da lista
void db_remove(DB *base_dados, int index);

//Permite atualizar um aluno da lista
void db_update(DB *base_dados, int index, ALUNO aluno);

ALUNO db_get(DB *base_dados, int index);

#endif