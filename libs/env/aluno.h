#ifndef ALUNO_H_INCLUDED
#define ALUNO_H_INCLUDED
#include "../data/files.h"

//Parâmetro define data de nascimento
typedef struct data_nascimento
{
    int dia;
    int mes;
    int ano;
}DATA_NAS;

//Define a estrutura aluno, de modo a organizar a informação de cada aluno.
//Parâmetro ocupado indica se há um aluno ou não nessa posição da estrutura; permite a eliminação de 
//alunos.
//data_n está armazenada numa outra estrutura
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
    DATA_NAS data_n;
}ALUNO;

//Define a estrutura apelido, de modo a comparar os apelidos de cada aluno
typedef struct apelido
{
    char * apel;
}APELIDO;

//Define a estrutura nacionalidade, para quando for relevante determinar um numero limitado de nacionalidades permitidas
typedef struct nacionalidades
{
    char * nacionalidade;
}NACIO;

//Transfere os dados dos ficheiros para a struct base de dados do tipo ALUNO
void seek_data(SDTM_File file_estudante, SDTM_File file_situacao, ALUNO *base_dados, size_t *size_alunos);

//Cria e inicializa a lista de estudantes
ALUNO * criar_lista(SDTM_File *txt_estudantes);

//Permite adicionar um aluno à lista
int inserir_estudante(ALUNO *lista_estudantes,size_t *size_alunos, int size_base);

//Permite remover um aluno da lista
void remover_estudante(ALUNO *lista_estudantes,int i);

//Permite alterar um dos dados do aluno
void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes, int size_base);

//Mostra os dados de um aluno
void mostrar_um_aluno(ALUNO *lista_estudantes,int posicao);

//Faz display da struct (apenas os membros com ocupado=1)
void mostrar_toda_lista(ALUNO *lista_estudantes, int size_base);

//Listar estudantes por ordem alfabética do apelido (considera-se apelido a última palavra
//do nome completo)
void mostrar_lista_por_ordem_apelido(ALUNO *lista_estudantes, int size_base);

//Permite calcular o número de posições ocupadas, ou seja, com lista_estudantes[i].ocupado==1
int calcular_tam_lista(ALUNO *lista_estudantes);


//Pesquisa um aluno através de parte do seu nome
void pesquisar(ALUNO *lista_estudantes,char *pesquisa, int size_base);

//Calcular e mostrar quantos estudantes existem com cada um de 3 escalões de média atual especificados 
//pelo utilizador
int mostrar_alunos_entre_medias(ALUNO *lista_estudantes,float x,float y, int size_base);

//Listar os estudantes, cujas datas de nascimento estejam dentro de um intervalo e pertencentes a um
//conjunto máximo de 5 nacionalidades
void listar_est_entre_data_n(ALUNO * lista_estudantes, char *data_1 , char * data_2, int size_base);

//Determinar o número de estudantes em risco de prescrever (3 matrículas e menos de
//60 ECTS, 4 matrículas e menos de 120 ECTS ou mais de 5 matrículas e não finalista) e
//proceder à sua listagem
int estudantes_risco_prescrever(ALUNO * lista_estudantes, int size_base);

//Determinar a média de idades dos estudantes de uma nacionalidade, atendendo ao ano
//que estão a frequentar
float * media_idades_nacionalidade(ALUNO * lista_estudantes, char * nacio, float ano_atual, int size_base);

//Determinar o número de estudantes finalistas (pelo menos 154 ECTS realizados)
int n_est_finalistas(ALUNO * lista_estudantes, int size_base);

//Determinar o numero medio de matriculas, em geral e por nacionalidade
void n_medio_mat(ALUNO * lista_estudantes, int size_base);

//Prepara o texto e outras informações relevantes para guardar o ficheiro, e depois guarda o ficheiro
void criar_txt_ficheiro_guardar (ALUNO * dados_alunos, int size_base, char * filepath1, char * filepath2);


#endif