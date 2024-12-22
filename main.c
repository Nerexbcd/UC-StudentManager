#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "libs/utils/string_util.h"

#include "libs/style/program.h"
#include "libs/style/menu.h"

#ifdef _WIN32
    #define OS "W"
    #include<windows.h>
    #define PATH_SEPARATOR_CHAR '\\'
    #define PATH_SEPARATOR_STR  "\\"
#elif __linux__
    #define OS "L"
    #include<unistd.h>
    #define PATH_SEPARATOR_CHAR '/'
    #define PATH_SEPARATOR_STR  "/"
#endif


// ============================== STYLING DEFINITIONS

/* Clear Console */
/* It clears the current output console */
void clearConsole();

// ------------------------------ COLORS

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define RED(string)     ANSI_COLOR_RED string ANSI_COLOR_RESET
#define GREEN(string)   ANSI_COLOR_GREEN string ANSI_COLOR_RESET
#define YELLOW(string)  ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
#define BLUE(string)    ANSI_COLOR_BLUE string ANSI_COLOR_RESET
#define MAGENTA(string) ANSI_COLOR_MAGENTA string ANSI_COLOR_RESET
#define CYAN(string)    ANSI_COLOR_CYAN string ANSI_COLOR_RESET


// ============================== STYLING

void clearConsole()
{
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}


// ============================== TXT FILES DEFINITIONS

typedef struct txtFile {
    char *path;
    char *fileName;
    char *fileDir;
    char loaded;
    char **data;
    size_t size;
} txtFile;

// ------------------------------ TXT File Error Handling

/* Error File Openning */
void txt_error_open_file(char *path);

/* Error File Data Not Loaded */
void txt_error_not_loaded(char *path);

/* Error Index Out Of Bounds */
void txt_error_index_out_of_bounds();

// ------------------------------ TXT File Initialization

/* Initialize txt file data array */
/* It Prepares the file to be used */
txtFile txt_files_init(char *path);

// ------------------------------ TXT File to memory and vice versa

/* Load txt files in to Program */
/* It reads the file and stores the data in the data array */
void txt_load_file(txtFile *txt);

/* Unload txt files from Program */
/* It frees the memory allocated for the data array */
void txt_unload_file(txtFile *txt);

// ------------------------------ TXT File Infos

/* Get txt file size */
/* It returns the number of lines in the file */
size_t txt_get_size(txtFile txt);

// ------------------------------ TXT Data Manipulation

/* Get txt file data */
/* It returns an array with each line one the file*/
char** txt_get_data(txtFile txt);

/* Get txt file line */
/* It returns the line index from the file */
char* txt_get_line(txtFile txt, size_t index);

/* Append data to txt file */
/* It adds a new line to the file */
void txt_append_data(txtFile *txt, char *data);

/* Update data in txt file */
/* It changes the data in the line index */
void txt_update_data(txtFile *txt, char *data, size_t index);

/* Remove data from txt file */
/* It removes the line index from the file */
void txt_remove_data(txtFile *txt, size_t index);

// ------------------------------ TXT File Save

/* Save data to txt file */
/* It saves the data array to the file */
void txt_save_file(txtFile txt);


// ============================== TXT FILES

// ------------------------------ TXT File Error Handling

void txt_error_open_file(char *path) {
    fprintf(stderr,RED("Error: Could not open file %s\n"), path);
    printf(CYAN("Exiting...\n"));
    exit(1);
}

void txt_error_not_loaded(char *path) {
    fprintf(stderr,RED("Error: File %s not loaded\n"), path);
    printf(CYAN("Exiting...\n"));
    exit(1);
}

void txt_error_index_out_of_bounds() {
    fprintf(stderr,RED("Error: Index out of bounds\n"));
    printf(CYAN("Exiting...\n"));
    exit(1);
}

// ------------------------------ TXT File Initialization

txtFile txt_files_init(char *path) {
    struct txtFile txt;
    txt.path = strdup(path);
    txt.size = 0;
    txt.loaded = 0;
    char** pathParts = str_split(strdup(path), PATH_SEPARATOR_CHAR, NULL);
    txt.fileDir = strdup("");

    txt.size++;
    for (int i = 0; *(pathParts + i); i++) {
        if (*(pathParts + i + 1) == NULL) {
            txt.fileName = *(pathParts + i);
            txt.size++;
        } else {
            strcat(strcat(txt.fileDir, *(pathParts + i)) , PATH_SEPARATOR_STR);
            txt.size++;
        }  
    }
    return txt;
}

// ------------------------------ TXT File to memory and vice versa

void txt_load_file(txtFile *txt){
    txtFile w_txt = *txt; 
    FILE *file = fopen(w_txt.path, "r");

    if (file == NULL) txt_error_open_file(w_txt.path);

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *string = malloc(fileSize + 1);
    fread(string, fileSize, 1, file);
    fclose(file);

    printf(CYAN("File %s loaded\n"), w_txt.path);

    string[fileSize] = 0;

    w_txt.data = str_split(string, '\n', &w_txt.size);
    free(string);
    w_txt.loaded = 1;

    *txt = w_txt;
}

void txt_unload_file(txtFile *txt){
    txtFile w_txt = *txt;
    for (int i = 0; *(w_txt.data + i); i++) {
        free(*(w_txt.data + i));
    }
    free(w_txt.data);
    w_txt.loaded = 0;
    *txt = w_txt;
}

// ------------------------------ TXT File Infos

size_t txt_get_size(txtFile txt){
    if (txt.loaded == 0) txt_error_not_loaded(txt.path);

    return txt.size;
}

// ------------------------------ TXT Data Manipulation

char** txt_get_data(txtFile txt){
    if (txt.loaded == 0) txt_error_not_loaded(txt.path);

    return txt.data;
}

char* txt_get_line(txtFile txt, size_t index){
    if (txt.loaded == 0) txt_error_not_loaded(txt.path);
    if (index >= txt.size) txt_error_index_out_of_bounds();

    return *(txt.data + index);
}

void txt_append_data(txtFile *txt, char *data){
    txtFile w_txt = *txt;

    if (w_txt.loaded == 0) txt_error_not_loaded(w_txt.path);
    
    w_txt.data = realloc(w_txt.data, (w_txt.size + 1) * sizeof(char*));
    *(w_txt.data + w_txt.size) = strdup(data);
    w_txt.size++;
    *txt = w_txt;
}

void txt_update_data(txtFile *txt, char *data, size_t index){
    txtFile w_txt = *txt;

    if (w_txt.loaded == 0) txt_error_not_loaded(w_txt.path);
    
    if (index >= w_txt.size) txt_error_index_out_of_bounds();

    free(*(w_txt.data + index));
    *(w_txt.data + index) = strdup(data);
    *txt = w_txt;
}

void txt_remove_data(txtFile *txt, size_t index){
    txtFile w_txt = *txt;

    if (w_txt.loaded == 0) txt_error_not_loaded(w_txt.path);
    
    if (index >= w_txt.size) txt_error_index_out_of_bounds();

    free(*(w_txt.data + index));
    for (int i = index; i < w_txt.size - 1; i++) {
        *(w_txt.data + i) = *(w_txt.data + i + 1);
    }
    w_txt.size--;
    w_txt.data = realloc(w_txt.data, w_txt.size * sizeof(char*));
    *txt = w_txt;
}

// ------------------------------ TXT File Save

void txt_save_file(txtFile txt){

    if (txt.loaded == 0) txt_error_not_loaded(txt.path);
    
    FILE *file = fopen(txt.path, "w");

    if (file == NULL) txt_error_open_file(txt.path);
    
    for (int i = 0; i < txt.size; i++) {
        fprintf(file, "%s\n", *(txt.data + i));
    }
    fclose(file);
    printf(CYAN("File %s saved\n"), txt.path);
}


// ============================== ALUNO

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
    int codigo;
    int n_matriculas;
    int ects_concluidos;
    int ano_curso;
    float media_atual;
    char * nome;
    char * nacionalidade;
    DATA_NAS data_n;
}ALUNO;

typedef struct apelido
{
    char * apel;
}APELIDO;



//Permite alterar um dos dados do aluno
void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes);

//Mostra os dados de um aluno
void mostrar_um_aluno(ALUNO aluno);



//Listar estudantes por ordem alfabética do apelido (considera-se apelido a última palavra
//do nome completo)
void mostrar_lista_por_ordem_apelido(ALUNO *lista_estudantes);

//Permite calcular o número de posições ocupadas, ou seja, com lista_estudantes[i].ocupado==1
int calcular_tam_lista(ALUNO *lista_estudantes);

//Determina média do número de matrículas dos estudantes, em geral e por nacionalidade
float media_mat(ALUNO *lista_estudantes,char *nacion);
//falta determinar por nacionalidades, vou ver mais tarde

//Pesquisa um aluno através de parte do seu nome
void pesquisar(ALUNO *lista_estudantes,char *pesquisa);

//Calcular e mostrar quantos estudantes existem com cada um de 3 escalões de média atual especificados 
//pelo utilizador
int mostrar_alunos_entre_medias(ALUNO *lista_estudantes,float x,float y);

//Listar os estudantes, cujas datas de nascimento estejam dentro de um intervalo e pertencentes a um
//conjunto máximo de 5 nacionalidades
void listar_est_entre_data_n(ALUNO * lista_estudantes, char *data_1 , char * data_2, char * nac_1, char * nac_2, char * nac_3, char * nac_4, char * nac_5);

//Determinar o número de estudantes em risco de prescrever (3 matrículas e menos de
//60 ECTS, 4 matrículas e menos de 120 ECTS ou mais de 5 matrículas e não finalista) e
//proceder à sua listagem
int estudantes_risco_prescrever(ALUNO * lista_estudantes);

//Determinar a média de idades dos estudantes de uma nacionalidade, atendendo ao ano
//que estão a frequentar
float * media_idades_nacionalidade(ALUNO * lista_estudantes, char * nacio, float ano_atual);

//Determinar o número de estudantes finalistas (pelo menos 154 ECTS realizados)
int n_est_finalistas(ALUNO * lista_estudantes);




void atualizar_uma_caracteristica_estudante(ALUNO *lista_estudantes)
{
    //setlocale(LC_ALL, "Portuguese"); //não funciona?
    int i=0;
    int k=0; //código do estudante
    int j=0; //posição do aluno com código k na lista


    printf("Qual o codigo do estudante? ");
    fflush(stdin);
    scanf(" %d",&k);

    for(int t=0;t<sizeof(*lista_estudantes);t++) {
        if(lista_estudantes[t].codigo==k) {
            j=t;
            break;
        }
    }

    i = menu_opcoes_field();

    switch (i) {
        //i indica qual elemento da estrutura a mudar, fornecido pelo utilizador no menu anterior
        case 0:
            printf("Qual o novo codigo do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).codigo);
            break;

        case 1:
            printf("Qual o novo numero de ECTS concluidos do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ects_concluidos);
            break;

        case 2:
            printf("Qual o novo ano de curso do estudante número %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).ano_curso);
            break;

        case 3:
            printf("Qual a nova media do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%f",&(lista_estudantes[j]).media_atual);
            break;

        case 4:
            //Esvazia-se o string primeiro para evitar erros:
            (*(lista_estudantes+j)).nome=NULL;
            //Por algum motivo o scanf e gets não funcionam para mim, por isso tenho de fazer esta abominação
            char * stringgg=NULL;
            size_t bufsize=200;
            printf("Qual o novo nome do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            lista_estudantes[j].nome=(char*) malloc(sizeof(stringgg));
            lista_estudantes[j].nome=stringgg;
            fflush(stdin);
            break;

        case 5:
            (*(lista_estudantes+j)).nacionalidade=NULL;
            stringgg=NULL;
            bufsize=200;
            printf("Qual a nova nacionalidade do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            lista_estudantes[j].nacionalidade=(char*) malloc(sizeof(stringgg));
            lista_estudantes[j].nacionalidade=stringgg;
            fflush(stdin);
            break;

        case 6:

            stringgg=NULL;
            bufsize=11;
            printf("Qual a nova data de nascimento do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            fflush(stdin);
            getline(&stringgg,&bufsize,stdin);
            stringgg = * str_split(stringgg, '\n', NULL);
            char *dn = stringgg;
            char **ptr_dn = str_split(dn, '-', NULL);
            lista_estudantes[j].data_n.dia= atoi(strdup(ptr_dn[0]));
            lista_estudantes[j].data_n.mes= atoi(strdup(ptr_dn[1]));
            lista_estudantes[j].data_n.ano= atoi(strdup(ptr_dn[2]));

            fflush(stdin);
            break;

        case 7:
            printf("Qual o novo numero de matriculas do estudante numero %d?\n",(lista_estudantes[j]).codigo);
            scanf("%d",&(lista_estudantes[j]).n_matriculas);
            break;
    }

    printf("Novos dados do estudante:\n");
    // mostrar_um_aluno(lista_estudantes,j);
    
}









void mostrar_um_aluno(ALUNO aluno)
{
    fflush(stdin);
    printf("Codigo: %d\n",aluno.codigo);
    printf("Nome: %s\n",aluno.nome);
    printf("Nacionalidade: %s\n",aluno.nacionalidade);
    printf("Data de nascimento: %d-%d-%d\n", aluno.data_n.dia, aluno.data_n.mes, aluno.data_n.ano);
    printf("Numero de matriculas: %d\n",aluno.n_matriculas);
    printf("Ano do curso: %d\n",aluno.ano_curso);
    printf("Media atual: %.1f\n",aluno.media_atual);
    printf("ECTS concluidos: %d\n\n",aluno.ects_concluidos);
    fflush(stdin);
}







void mostrar_lista_por_ordem_apelido(ALUNO *lista_estudantes)
{
    int * vet_organizado;
    vet_organizado = malloc(sizeof(int)*sizeof(lista_estudantes));

    //cria o vetor que vai determinar a ordem alfabética dos apelidos
    for (int k=0;k<sizeof(lista_estudantes);k++) {
        vet_organizado[k]=k;
    }
    
    //struct vai acumular todos os apelidos, pela mesma ordem dos estudantes na lista normal
    APELIDO *lista_apelidos;
    lista_apelidos = malloc(sizeof(APELIDO *) * sizeof(lista_estudantes));

    for (int g=0; g<sizeof(lista_estudantes);g++) {
        char * linha = strdup(lista_estudantes[g].nome);
        char ** nome_comp = NULL;
        nome_comp = str_split(linha,' ', NULL);
        int componentes = 0;
        int i=0;

        while(nome_comp[i+1]!=0) {
            componentes++;
            i++;
        }
        lista_apelidos[g].apel = malloc(sizeof(char) * strlen(nome_comp[componentes]));
        lista_apelidos[g].apel = nome_comp[componentes];
        printf("%s\n",lista_apelidos[g].apel);
    }




    //algoritmo organização
    int temp;
    int pos;
    char letra_a;
    char letra_b;

    //compara os apelidos, mas guarda a sua ordem correta no vet_organizado
    //ainda nao está certo, mas parte anterior está
    for (int i=0; i<sizeof(lista_estudantes)-1; i++) {
        for (int j=0;j<sizeof(lista_estudantes)-i-1;j++) {
            pos = vet_organizado[j];
            letra_a = lista_apelidos[pos].apel[j];
            letra_b = lista_apelidos[pos+1].apel[j];
            printf("%c\n",letra_a);
            printf("%c\n",letra_b);
            puts("ggg");
        // compara elementos adjacentes para ver se estão fora de ordem
            if ((letra_a > letra_b) && (letra_a!=0) && (letra_b!=0)) {
            temp=vet_organizado[j];
            vet_organizado[j]=vet_organizado[j+1];
            vet_organizado[j+1]=temp;
            }
        }
    }

    for (int i=0;i<sizeof(vet_organizado);i++) {
        int posicao = vet_organizado[i];
        printf("%s\n",lista_estudantes[posicao].nome);
    }
}




float media_mat(ALUNO *lista_estudantes,char *nacion) {

    int media=0;
    int num=0;

    if (nacion == 0) {
        for(int i=0;i<sizeof(lista_estudantes);i++) {
            if (lista_estudantes[i].codigo==1) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
    else if (nacion != 0) {
        for(int i=0;i<sizeof(lista_estudantes);i++) {
            if ((lista_estudantes[i].codigo==1) && (lista_estudantes[i].nacionalidade==nacion)) {
                media=media+(lista_estudantes[i].n_matriculas);
                num++;
            }
        }
        return (media/num);
    }
}





void pesquisar(ALUNO *lista_estudantes,char *pesquisa)
{
    int * lista_matches;
    lista_matches = (int *) malloc(sizeof(int)*sizeof(lista_estudantes->nome));

    for (int s=0; s<sizeof(lista_matches); s++) {
        lista_matches[s]=0;
    }


    for (int i=0; i<sizeof(lista_estudantes->nome); i++) {

        char * vetor = lista_estudantes[i].nome;  //define o vetor a comparar.

        for (int k=0; k<sizeof(*(lista_estudantes->nome)); k++) { //vai comparar elemento a elemento
            
            int repeticao=k;

            do {
                int posicao=0;
                int matches=0;

                //procura o primeiro elemento que seja igual ao primeiro elemento do vetor pesquisa
                while((vetor[posicao+repeticao]!=pesquisa[0]) && ((posicao+repeticao)<(strlen(vetor)))) {  //determina qual é o elemento inicial
                    int f=posicao+repeticao;
                        posicao++;
                }

                //se não houver um elemento igual ao primeiro elemento da pesquisa, posicao==strlen(vetor)
                //caso contrário, vai verificar se os outros elementos são iguais
                if (posicao<strlen(vetor)) {

                    matches=1;

                    for (int j=1; (j<strlen(pesquisa)) && (posicao+repeticao+j)<strlen(vetor); j++) {
                        if (pesquisa[j]==vetor[posicao+repeticao+j]) {
                            matches++;
                        }
                    }

                    //verifica se o número de elementos iguais consecutivos é igual ao número de elementos da pesquisa
                    if ((matches)==(strlen(pesquisa))) {
                        lista_matches[i]=1;//o vetor matches vai ser 1 nas posicoes correspondentes às posições dos nomes que contêm a pesquisa
                    }
                    else {
                        repeticao++;//caso não seja igual, verifica se algum outro segmento do nome coincide com o vetor pesquisa
                        //isto acontece através de começar a pesquisa do primeiro elemento em comum 1 espaço à frente do anterior
                    }
                }
            }
            while ((strlen(vetor))-repeticao>strlen(pesquisa) && repeticao!=0);

        }
    }

    int rep=0;
    int g=0;
    for (int k=0; k< sizeof(lista_matches); k++) {
        if (rep==0) {//no case de ser a primeira iteração
            printf("Resultado(s) da pesquisa <%s>:\n",pesquisa);
        }
        if (lista_matches[k]==1) {
            if ((g != 0) && (g%3==0)) {
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            // mostrar_um_aluno(lista_estudantes,k);
            g++;
        }
        rep++;
    }
}



int mostrar_alunos_entre_medias(ALUNO *lista_estudantes,float x,float y) 
{
    int n_est_com_media=0;//número de estudantes com média entre estes valores

    //determinar o maior e menor valor
    float max=x;
    float min=0;
    if (max>y) {
        min=y;
    }
    else {
        max=y;
        min=x;
    }

    //Mostrar os alunos com médias entre estes 2 valores
    int i=0;//elemento de paginação, determina quantas iterações foram mostradas ao utilizador

    for (int k=0;k<sizeof(lista_estudantes);k++) {
        if ((lista_estudantes[k].media_atual>=min) && (lista_estudantes[k].media_atual<=max)) {
            if ((i != 0) && (i%3==0)) {//elemento de paginação, mostra em blocos de 3
                printf("Pagina seguinte ->");
                fflush(stdin);
                getchar();
                puts("");
                fflush(stdin);
            }
            // mostrar_um_aluno(lista_estudantes,k);
            n_est_com_media++;
            i++;
        }
    }

    return n_est_com_media;
}



int n_est_finalistas(ALUNO * lista_estudantes) {
    int n_fin=0;//vai guardar o número de alunos que é finalista

    //para ser considerado finalista, o aluno tem de ter pelo menos 154 ects
    for (int i=0;i<sizeof(lista_estudantes);i++) {
        if (lista_estudantes[i].ects_concluidos>=154) {
            n_fin++;
        }
    }

    return n_fin;//retorna o número de estudantes finalistas
}



// void listar_est_entre_data_n(ALUNO * lista_estudantes, char *data_1 , char * data_2, char * nac_1, char * nac_2, char * nac_3, char * nac_4, char * nac_5)
// {
//     DATA_NAS data_sup;//data maior
//     DATA_NAS data_inf;//data menor

//     DATA_NAS data_prim;//primeira data fornecida, data_1, organizada em struct
//     DATA_NAS data_seg;//segunda data fornecida, data_2, organizada em struct

//     //Coloca as datas fornecidas pelo utilizador na struct do tipo DATA_NAS para fácil comparação
//     //com as datas dos alunos
//     char *dnp = data_1;//ponteiro de data_1
//     char **ptr_dnp = str_split(dnp, '-', NULL);//vai separar as datas da carater '-'
//     data_prim.dia= atoi(strdup(ptr_dnp[0]));//alocação de cada elemento no campo adequado
//     data_prim.mes= atoi(strdup(ptr_dnp[1]));
//     data_prim.ano= atoi(strdup(ptr_dnp[2]));

//     //de forma semelhante:
//     char *dns = data_2;
//     char **ptr_dns = str_split(dns, '-', NULL);
//     data_seg.dia= atoi(strdup(ptr_dns[0]));
//     data_seg.mes= atoi(strdup(ptr_dns[1]));
//     data_seg.ano= atoi(strdup(ptr_dns[2]));


//     //Determina qual a data superior e a data inferior por comparação
//     //comparação por anos
//     if ((data_prim.ano)>(data_seg.ano)) {
//         data_sup = data_prim;
//         data_inf = data_seg;
//     }
//     else if ((data_seg.ano)>(data_prim.ano)) {
//         data_sup = data_seg;
//         data_inf = data_prim;
//     }
//     else if ((data_seg.ano)==(data_prim.ano)) {
//         //comparação por meses
//         if ((data_prim.mes)>(data_seg.mes)) {
//             data_sup = data_prim;
//             data_inf = data_seg;
//         }
//         else if ((data_seg.mes)>(data_prim.mes)) {
//             data_sup = data_seg;
//             data_inf = data_prim;
//         }
//         else if ((data_prim.mes)==(data_seg.mes)) {
//             //comparação por dias
//             if ((data_prim.dia)>(data_seg.dia)) {
//             data_sup = data_prim;
//             data_inf = data_seg;
//             }
//             else if ((data_seg.dia)>(data_prim.dia)) {
//                 data_sup = data_seg;
//                 data_inf = data_prim;
//             }
//         }
//     }

//     //Efetua a comparação
//     int rep=0;
//     for (int k=0;k<sizeof(lista_estudantes);k++) {
//         if (rep!=0 && rep%3==0) {
//                 printf("Pagina seguinte ->");
//                 fflush(stdin);
//                 getchar();
//                 puts("");
//                 fflush(stdin);
//         }

//         if ((lista_estudantes[k].nacionalidade==nac_1 || lista_estudantes[k].nacionalidade==nac_2 || lista_estudantes[k].nacionalidade==nac_3 || lista_estudantes[k].nacionalidade==nac_4 || lista_estudantes[k].nacionalidade==nac_5)) {
//             //Compara os anos inicialmente
//             if ((lista_estudantes[k].data_n.ano>data_inf.ano) && (lista_estudantes[k].data_n.ano<data_sup.ano)) {
//                 mostrar_um_aluno(lista_estudantes,k);
//             }
//             else if (lista_estudantes[k].data_n.ano==data_inf.ano) {
//                 //No caso dos anos serem os extremos, compara os meses.
//                 if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
//                 mostrar_um_aluno(lista_estudantes,k);
//                 }
//                 //No casos dos meses serem os extremos, compara os dias.
//                 else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
//                     if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
//                         mostrar_um_aluno(lista_estudantes,k);
//                     }
//                 }
//                 else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
//                     if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
//                         mostrar_um_aluno(lista_estudantes,k);
//                     }
//                 }
//             }
//             //Mesma situação que o anterior, mas caso extremo oposto
//             else if (lista_estudantes[k].data_n.ano==data_sup.ano) {
//                 if ((lista_estudantes[k].data_n.mes>data_inf.mes) && (lista_estudantes[k].data_n.mes<data_sup.mes)) {
//                 mostrar_um_aluno(lista_estudantes,k);
//                 }
//                 else if (lista_estudantes[k].data_n.mes==data_inf.mes) { 
//                     if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
//                         mostrar_um_aluno(lista_estudantes,k);
//                     }
//                 }
//                 else if (lista_estudantes[k].data_n.mes==data_sup.mes) {
//                     if ((lista_estudantes[k].data_n.dia>=data_inf.dia) && (lista_estudantes[k].data_n.dia<=data_sup.dia)) {
//                         mostrar_um_aluno(lista_estudantes,k);
//                     }
//                 }

//             }
//         }
//         rep++;
//     }
// }


int estudantes_risco_prescrever(ALUNO * lista_estudantes) {

    setlocale(LC_ALL,"Portuguese");//??????
    
    //vetor cujas posicoes com 1 correspondem às posicoes dos alunos em risco de prescricao na struct lista_estudantes
    int * lista_prescricao = malloc(sizeof(int) * sizeof(lista_estudantes));
    for (int i=0; i<sizeof(lista_prescricao); i++) {
        lista_prescricao[i]=0;
    }

    int num=0; //número de estudantes em risco de prescrição
    for (int i=0;i<sizeof(lista_estudantes);i++) {

        if ((lista_estudantes[i].n_matriculas==3) && (lista_estudantes[i].ects_concluidos<60)) {
            lista_prescricao[i]=1;
            num++;
        }
        else if ((lista_estudantes[i].n_matriculas==4) && (lista_estudantes[i].ects_concluidos<120)) {
            lista_prescricao[i]=1;
            num++;
        }
        else if ((lista_estudantes[i].n_matriculas>5) && (lista_estudantes[i].ects_concluidos<154)) {
            lista_prescricao[i]=1;
            num++;
        }

    }

    int rep=0;
    if (num!=0) {
        for (int i=0;i<sizeof(lista_prescricao);i++) {
            if (lista_prescricao[i]==1) {
                if (rep==0) {
                    printf("Lista de alunos em risco de prescrição:\n");
                }
                else if(rep!=0 && rep%10==0) {
                    printf("Pagina seguinte ->");
                    fflush(stdin);
                    getchar();
                    puts("");
                    fflush(stdin);
                }
                printf("%s\n",lista_estudantes[i].nome);
            }
        }
    }
    else {
        printf("Não há alunos em risco de prescrição!\n");
    }

    return num;
}



float * media_idades_nacionalidade(ALUNO * lista_estudantes, char * nacio, float ano_atual)
{
    //vetor vai organizar as médias das idades da nacionalidade fornecida pelo ano de curso
    float * media_por_nac_por_ano = malloc(sizeof(float)*3); 

    for (int j=1; j<sizeof(media_por_nac_por_ano); j++) { //determina qual o ano de curso (e posicao no vetor) estamos a avaliar
        int n_ele=0;
        int soma=0;
        for (int i=0; i<sizeof(lista_estudantes);i++) {
            //procura os alunos que obedecem a todas as condicoes:
            //nacionalidade, ano de curso correto, existência na base de dados
            if ((strcmp(lista_estudantes[i].nacionalidade, nacio) == 0) && (lista_estudantes[i].ano_curso == j)) {
                n_ele++;
                int idade = ano_atual - (lista_estudantes[i].data_n.ano); //idade é obtida de forma muito simplificada através do ano de nascimento.
                //ignoram-se as outras componentes desta data por agora
                soma = soma + idade;
            }
        }
        if (n_ele!=0) {
            media_por_nac_por_ano[j-1] = ((float) soma)/ ((float) n_ele);
        }
        else { //para evitar possíveis divisões por zero
            media_por_nac_por_ano[j-1] = 0;
        }
    }

    return media_por_nac_por_ano; //retorna todo o vetor
}


/* int n_est_finalistas(ALUNO * lista_estudantes) {
    int n_fin=0;
    
    for (int i=0;i<sizeof(lista_estudantes);i++) {
        if ((lista_estudantes[i].ocupado==1) && (lista_estudantes[i].ects_concluidos>=154)) {
            n_fin++;
        }
    }

    return n_fin;
} */

// ============================== DATABASE DEFINITIONS

typedef struct db
{
    ALUNO *alunos;
    size_t size;
}DB;

// ------------------------------ DB Initialization

//Cria e inicializa a lista de estudantes
DB *db_init(size_t size_alunos);

//Transfere os dados dos ficheiros para a struct base de dados do tipo ALUNO
void db_load_data(txtFile file_estudante, txtFile file_situacao, DB *base_dados);

// ------------------------------ DB Manipulation

//Permite adicionar um aluno à lista
void db_insert(DB *base_dados, ALUNO aluno);

//Permite remover um aluno da lista
void db_remove(DB *base_dados, int index);

//Permite atualizar um aluno da lista
void db_update(DB *base_dados, int index, ALUNO aluno);

//Faz display da struct (apenas os membros com ocupado=1)
void mostrar_toda_lista(DB * base_dados);


// ============================== DATABASE

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

//Permite obter um aluno da lista
ALUNO db_get(DB *base_dados, int index);

ALUNO db_get(DB *base_dados, int index)
{
    ALUNO aluno = (ALUNO) base_dados->alunos[index];
    return aluno;
}

void mostrar_toda_lista(DB * base_dados) {

    for (int i=0,j=0; j<base_dados->size;i++) {
        if ((i != 0) && (i%3==0)) {
            printf("Pagina seguinte ->");
            fflush(stdin);
            getchar();
            puts("");
            fflush(stdin);
        }

        // mostrar_um_aluno(db_get(base_dados,j));

        j++;
    }
}


// ============================== MAIN

int main(void)
{
    

    setlocale(LC_ALL, "Portuguese");

    /*
    // // Podes usar a função sizeof para saber quantas linhas tem
    //printf("Size: %u\n", txt_get_size(txt_estudantes));
    */

        
            //program_header();
            
        for (int i = 0; i < 10; i++)
        {
            clearConsole();
            printf(CYAN("Starting..."));
            for (int j = 1; j < i; j++) {
                printf(CYAN("."));
            }
            if (i == 9) printf(CYAN(" [DONE!]"));
            printf("\n");
            // sleep(1);
        }



        MENU_PAGE menu_principal;
        menu_principal.title = "Menu Principal";

/*         menu_principal.option_1 = "Gestão de testes";
        menu_principal.option_2 = "Gestão de outras coisas";
        menu_principal.option_3 = "Gestão de batatas";
        menu_principal.option_4 = "Gestão da horta"; */

        menu_principal.option_1 = "Gestão";
        menu_principal.option_2 = "Gestão";
        menu_principal.option_3 = "Gestão";
        menu_principal.option_4 = "Gestão";

        menu_show_page(&menu_principal);
        


        printf("BEM VINDO!\n\n");

        char *path_estudantes;
        char *path_situacao;



        if (strcmp(OS, "W") == 0)
        {

            path_estudantes = "data\\estudantes.txt";
            path_situacao   = "data\\situacao_Escolar_Estudantes.txt";
        }
        else if (strcmp(OS, "L") == 0)
        {
            path_estudantes = "./data/estudantes.txt";
            path_situacao   = "./data/situacao_Escolar_Estudantes.txt";
        }



        txtFile txt_estudantes = txt_files_init(path_estudantes);
        txtFile txt_situacao   = txt_files_init(path_situacao);

        txt_load_file(&txt_estudantes);
        txt_load_file(&txt_situacao);


        DB *base_dados = db_init(txt_get_size(txt_estudantes));

        db_load_data(txt_estudantes, txt_situacao, base_dados);


        ALUNO aluno2 = db_get(base_dados, 0);

        printf("%d\n", aluno2.codigo);
        printf("%s\n", aluno2.nome);
        printf("%s\n", aluno2.nacionalidade);
        printf("%d-%d-%d\n", aluno2.data_n.dia, aluno2.data_n.mes, aluno2.data_n.ano);
        printf("%d\n", aluno2.ano_curso);
        printf("%.1f\n", aluno2.media_atual);
        printf("%d\n", aluno2.ects_concluidos);
        printf("%d\n", aluno2.n_matriculas);





        // mostrar_toda_lista(base_dados->alunos);

        printf("\n\nbanananananan\n\n");

        ALUNO aluno;

        aluno.codigo = 100;
        aluno.nome = "Joao";
        aluno.nacionalidade = "Portuguesa";
        aluno.data_n.dia = 1;
        aluno.data_n.mes = 1;
        aluno.data_n.ano = 2000;
        aluno.ano_curso = 1;
        aluno.media_atual = 15;
        aluno.ects_concluidos = 0;
        aluno.n_matriculas = 0;

        db_insert(base_dados, aluno);

        printf("%u\n",base_dados->size);

        // mostrar_toda_lista(base_dados->alunos);

        printf("\n\nbanananananan\n\n");

        db_remove(base_dados, 2);

        printf("%u\n",base_dados->size);

        // mostrar_toda_lista(base_dados->alunos);

        // mostrar_lista_por_ordem_apelido(dados_alunos);

        

        // char * string = "do";
        // pesquisar(dados_alunos,string);

        // int a = estudantes_risco_prescrever(dados_alunos);

        // char * c = "Portuguesa";
        // float ano_a= 2024;
        // float * b = media_idades_nacionalidade(dados_alunos, c, ano_a);
        // printf("%.0f\n",b[0]);
        // printf("%.0f\n",b[1]);
        // printf("%.0f\n",b[2]);

        /*char * pesquisa = "i";
        char * ptr_pesquisa = pesquisa;

        pesquisar(dados_alunos,ptr_pesquisa);

        gets("");


      

 

 /*
    mostrar_toda_lista(aaa);

    inserir_estudante(aaa,&size_alunos);
    inserir_estudante(aaa,&size_alunos);
    //inserir_estudante(aaa);
    //inserir_estudante(aaa);

    mostrar_toda_lista(aaa);

    atualizar_uma_caracteristica_estudante(aaa);


    mostrar_toda_lista(aaa);


  */  

    //tem que ter inicializado dos ficheiros antes
    int cond_saida=0; //condicao de saída do loop
/*
    do
    {
        int opcao=0;
        scanf(" %d",&opcao);
        switch (opcao)
        {
        case 1: //mostrar a lista
            mostrar_toda_lista(base_dados);
            break;
        case 2: //inserir um aluno
            break;
        case 3: //remover um aluno
            break;
        case 4: //alterar dados de um aluno
            atualizar_uma_caracteristica_estudante(base_dados);
            break;
        case 5: //pesquisar estudante por nome
            char *pesquisa = NULL;
            pesquisa = menu_obter_pesquisa;
            pesquisar(base_dados,pesquisa);
            break;
        case 6: //mostra lista por ordem alfabética do último nome
            mostrar_lista_por_ordem_apelido(base_dados);
            break;
        case 7: //mostrar alunos entre duas médias
            float x = 0;
            float y = 0;
            x = menu_obter_float();
            y = menu_obter_float();
            mostrar_alunos_entre_medias(base_dados,x,y);
            break;
        case 8: //mostrar estudantes em risco de prescrever
            int n_est_risco = 0;
            n_est_risco = estudantes_risco_prescrever(base_dados);
            break;
        case 9: //determinar o número de estudantes finalistas
            int n_fin = 0;
            n_fin = n_est_finalistas(base_dados);
            printf("Número de estudantes finalistas: %d.\n",n_fin);
            fflush(stdin);
            break;
        case 10: //mostra a média dos alunos de uma certa nacionalidade por ano
            float media = 0;
            float ano_atual = 2024;
            char * nacion = NULL;
            nacion = menu_obter_nacionalidade();
            float * media_idades_nacionalidade(base_dados, nacion, ano_atual);
            //printf
            break;
        case 11:
            break;
        //etc
        case ():
            cond_saida=1;
            printf("A sair...");
            break;
        default:
            printf("Erro! Escolha uma opção válida")
            break;
        }
    } while (cond_saida==0);
    
  */
    return 0;
}