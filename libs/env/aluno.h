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
    char nome[100];
    char nacionalidade[100];
    char data_n[10];
}ALUNO;

void inserir_estudante(ALUNO *lista_estudantes,int i);

void remover_estudante(ALUNO *lista_estudantes,int i);

void atualizar_estudante(ALUNO *lista_estudantes,int i);