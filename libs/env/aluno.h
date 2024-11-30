#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED
#include "../data/txt_files.h"

//Define a estrutura aluno, de modo a organizar a informação de cada aluno.
//Parâmetro ocupado indica se há um aluno ou não nessa posição da estrutura; permite a eliminação de alunos.
typedef struct aluno
{
    int ocupado;
    int codigo;
    int n_matriculas;
    int ects_concluidos;
    int ano_curso;
    float media_atual;
    char * nome;
    char * nacionalidade;
    char * data_n;
}ALUNO;

//Transfere os dados dos ficheiros para a struct base de dados do tipo ALUNO
void seek_data(txtFile file_estudante, txtFile file_situacao, ALUNO *base_dados, size_t *size_alunos);

//Cria e inicializa a lista de estudantes
ALUNO * criar_lista(txtFile *txt_estudantes);

//Permite adicionar um aluno à lista
void inserir_estudante(ALUNO *lista_estudantes,size_t *size_alunos);

//Permite remover um aluno da lista
void remover_estudante(ALUNO *lista_estudantes,int i);

//Permite alterar um dos dados do aluno
void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes);

//Faz display da struct (apenas os membros com ocupado=1)
void mostrar_toda_lista(ALUNO *lista_estudantes);

//Permite calcular o número de posições ocupadas, ou seja, com lista_estudantes[i].ocupado==1
int calcular_tam_lista(ALUNO *lista_estudantes);

//Determina média do número de matrículas dos estudantes, em geral e por nacionalidade
int media_mat(ALUNO *lista_estudantes,char *nacion);


#endif