#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "libs/style/tools.h"
#include "libs/data/files.h"
#include "libs/env/aluno.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"
#include "libs/style/menu.h"

#ifdef _WIN32
    #define OS "W"
    #include<windows.h>
#elif __linux__
    #define OS "L"
    #include<unistd.h>
#endif


int main(void)
{
    fflush(stdin);

    setlocale(LC_ALL, "Portuguese");
            
        for (int i = 0; i < 10; i++)
        {
            clearConsole();
            printf(CYAN("Starting..."));
            for (int j = 1; j < i; j++) {
                printf(CYAN("."));
            }
            if (i == 9) printf(CYAN(" [DONE!]"));
            printf("\n");
            //sleep(1);
            fflush(stdin);
        }
        
        

       
        printf("\nBEM VINDO!\n\n");
        
        char *path_estudantes; //caminho do ficheiro dos dados dos estudantes
        char *path_situacao; //caminho do ficheiro da situacao escolar
  

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
        
        txtFile txt_estudantes = files_init(path_estudantes); //estrutura que armazena a informacao do ficheiro dos estudantes
        txtFile txt_situacao   = files_init(path_situacao); //estrutura que armazena a informacao do ficheiro da situacao escolar
   
        ALUNO *dados_alunos = criar_lista(&txt_estudantes); //estrutura que armazena a informacao dos alunos

        size_t size_alunos = 0; //tamanho total da informaçao na estrutura dados_alunos (bytes)

        int size_base = seek_data(txt_estudantes, txt_situacao,dados_alunos, &size_alunos); //tamanho inicial da estrutura

       
    //fim da inicializacao  
    
    int cond_saida=0; //condicao de saída do loop

    do
    {
        int opcao=0; //opcao escolhida pelo utilizador

        float ano_atual = 0; //para se calcular idades
        float x = 0; //para medias
        float y = 0; //para medias
        int n_est_risco = 0; //numero de estudantes a precrever
        int n_fin = 0; //numero finalistas
        float * media = NULL; //media geral de todos os alunos
        char * nacion = NULL; //para guardar a string nacionalidade
        char * pesquisa = NULL; //para guardar a string pesquisa
        int i = 0; //codigo de um aluno
        char * data1 = malloc(sizeof(char)*10); //uma data de nascimento
        char * data2 = malloc(sizeof(char)*10); //uma data de nascimento
        
        fflush(stdin);
        printf("\nEscolha entre as seguintes opcoes:");
        fflush(stdin);
        printf("\n1- Ver todos os dados dos estudantes.\n2- Adicionar um estudante.\n3- Remover um estudante.");
        fflush(stdin);
        printf("\n4- Atualizar um dado de um estudante.\n5- Pesquisar um estudante pelo seu nome.");
        fflush(stdin);
        printf("\n6- Mostrar a lista dos nomes dos alunos por ordem alfabetica dos seus apelidos.");
        fflush(stdin);
        printf("\n7- Mostrar alunos com medias entre dois valores.");
        fflush(stdin);
        printf("\n8- Determinar o numero de alunos em risco de prescrever.\n9- Determinar o numero de estudantes finalistas.");
        fflush(stdin);
        printf("\n10- Mostrar as medias das idades dos alunos de uma certa nacionalidade por ano (apenas considera o ano atual).");
        fflush(stdin);
        printf("\n11- Listar os alunos com datas de nascimento entre dois valores e que pertecam a um grupo de 5 nacionalidades.");
        fflush(stdin);
        printf("\n12- Determinar o numero medio de matriculas, em geral e por nacionalidade.");
        fflush(stdin);
        printf("\n13- Guardar os ficheiros.");
        fflush(stdin);
        printf("\n14- Sair.");
        fflush(stdin);
        
        printf("\n\nOpçao: ");
        fflush(stdin);
        scanf(" %d",&opcao);
        
        switch (opcao)
        {
        case 1: //mostrar a lista
            printf("\nLista de estudantes: \n");
            mostrar_toda_lista(dados_alunos, size_base);
            break;

        case 2: //inserir um aluno
            printf("\nInsira os dados do aluno:\n");
            fflush(stdin);
            size_base = inserir_estudante(dados_alunos, size_base);
            break;

        case 3: //remover um aluno
            i = escolher_codigo(dados_alunos);
            remover_estudante(dados_alunos, i);
            break;

        case 4: //alterar dados de um aluno
            atualizar_uma_caracteristica_estudante(dados_alunos, size_base);
            break;

        case 5: //pesquisar estudante por nome
            pesquisa = menu_obter_pesquisa();
            pesquisar(dados_alunos,pesquisa, size_base);
            break;

        case 6: //mostra lista por ordem alfabética do último nome
            printf("\nLista dos nomes dos alunos por ordem alfabetica do seu apelido:\n");
            mostrar_lista_por_ordem_apelido(dados_alunos, size_base);
            break;

        case 7: //mostrar alunos entre duas médias 
            x = menu_obter_float();
            y = menu_obter_float();
            mostrar_alunos_entre_medias(dados_alunos,x,y, size_base);
            break;

        case 8: //mostrar estudantes em risco de prescrever
            n_est_risco = estudantes_risco_prescrever(dados_alunos, size_base);
            break;

        case 9: //determinar o número de estudantes finalistas
            n_fin = n_est_finalistas(dados_alunos, size_base);
            printf("Numero de estudantes finalistas: %d.\n",n_fin);

            fflush(stdin);
            break;

        case 10: //mostra a média das idades dos alunos de uma certa nacionalidade por ano
            ano_atual = 2025;
            nacion = menu_obter_nacionalidade();
            media = media_idades_nacionalidade(dados_alunos, nacion, ano_atual, size_base);
            for (i=0;i<6;i++) {
                if (media[i]!=0) {
                    if (strcmp(nacion,"0")!=0) {
                        printf("\nMedia das idades dos alunos da nacionalidade \"%s\" do ano %i: %.2f",nacion,i+1,media[i]);
                    }
                    else {
                        printf("\nMedia geral das idades do ano %i: %.2f",i+1,media[i]);
                    }
                }
            }
            puts("");
            break;

        case 11: //listar estudantes cujas datas de nascimento estejam entre x e y e que pertencam no maximo a 5 nacionalidades
            printf("\nIntroduza a primeira data de nascimento (dd-mm-aaaa): ");
            fflush(stdin);
            scanf(" %s",data1);
            printf("\nIntroduza a segunda data de nascimento (dd-mm-aaaa): ");
            fflush(stdin);
            scanf(" %s",data2);
            listar_est_entre_data_n(dados_alunos, data1 , data2, size_base);
            break;

        case 12: //determinar o numero medio de matriculas, em geral e por nacionalidade
            n_medio_mat(dados_alunos, size_base);
            break;
        
        case 13: //guardar o ficheiro
            criar_txt_ficheiro_guardar (dados_alunos, size_base, path_estudantes, path_situacao);
            break;

        case 14:
            criar_txt_ficheiro_guardar(dados_alunos,size_base,path_estudantes,path_situacao);
            cond_saida=1;
            printf("A sair...");
            break;

        default:
            printf("Erro! Escolha uma opção válida");
            break;
        }
    } while (cond_saida==0);
    
  
    getchar();
    return 0;
}