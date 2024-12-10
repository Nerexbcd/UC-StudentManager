#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "libs/style/tools.h"
#include "libs/data/txt_files.h"
#include "libs/env/aluno.h"
#include "libs/style/colors.h"
#include "libs/style/tools.h"
#include "libs/style/program.h"
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
    getchar();

    setlocale(LC_ALL, "Portuguese");
    setlocale(LC_ALL,"pt_PT.UTF-8");

    /*
    // // Podes usar a função sizeof para saber quantas linhas tem
    //printf("Size: %u\n", txt_get_size(txt_estudantes));
    */

    
    //int condicao_saida=0;
    //MENU PRINCIPAL
    //do
    //{
        
            //program_header();
            
       /* for (int i = 0; i < 10; i++)
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
        */
        

       getchar();
        printf("BEM VINDO!\n\n");
        getchar();
        char *path_estudantes;
        char *path_situacao;
    getchar();

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
        puts("1");
    getchar();
        txtFile txt_estudantes = txt_files_init(path_estudantes);
        txtFile txt_situacao   = txt_files_init(path_situacao);
    puts("1");~
    getchar();
        ALUNO *dados_alunos = criar_lista(&txt_estudantes);

        size_t size_alunos = 0;

        seek_data(txt_estudantes, txt_situacao,dados_alunos, &size_alunos);
    puts("1");
    getchar();
        mostrar_toda_lista(dados_alunos);
        puts("2");
    getchar();
        mostrar_lista_por_ordem_apelido(dados_alunos);
    puts("1");
    getchar();
        char * string = "do";
        pesquisar(dados_alunos,string);

        int a = estudantes_risco_prescrever(dados_alunos);

        char * c = "Portuguesa";
        float ano_a= 2024;
        float * b = media_idades_nacionalidade(dados_alunos, c, ano_a);
        printf("%.0f\n",b[0]);
        printf("%.0f\n",b[1]);
        printf("%.0f\n",b[2]);

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
    getchar();
    return 0;
}