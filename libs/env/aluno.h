#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED

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
void seek_data(char *ficheiro_estu, /*char *ficheiro_situacao, */ALUNO *base_dados);

//Cria e inicializa a lista de estudantes
ALUNO * criar_lista(int i);

//Permite adicionar um aluno à lista
void inserir_estudante(ALUNO *lista_estudantes,int i);

//Permite remover um aluno da lista
void remover_estudante(ALUNO *lista_estudantes,int i);

//Permite alterar um dos dados do aluno
void atualizar_estudante(ALUNO *lista_estudantes,int i);

#endif