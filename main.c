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

    setlocale(LC_ALL, "Portuguese");

    /*
    // // Podes usar a função sizeof para saber quantas linhas tem
    //printf("Size: %u\n", txt_get_size(txt_estudantes));
    */

    
    //int condicao_saida=0;
    //MENU PRINCIPAL
    //do
    //{
        
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
            //sleep(1);
            fflush(stdin);
        }
        
        

       
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
   
        ALUNO *dados_alunos = criar_lista(&txt_estudantes);

        size_t size_alunos = 0;

        seek_data(txt_estudantes, txt_situacao,dados_alunos, &size_alunos);

       /* mostrar_toda_lista(dados_alunos);
        
    
        mostrar_lista_por_ordem_apelido(dados_alunos);
   
        char * string = "do";
        pesquisar(dados_alunos,string);

        int a = estudantes_risco_prescrever(dados_alunos);

        char * c = "Portuguesa";
        float ano_a= 2024;
        float * b = media_idades_nacionalidade(dados_alunos, c, ano_a);
        printf("%.0f\n",b[0]);
        printf("%.0f\n",b[1]);
        printf("%.0f\n",b[2]);*/

   //tem que ter inicializado dos ficheiros antes
    int cond_saida=0; //condicao de saída do loop



    do
    {
        int opcao=0;

        float ano_atual = 0;
        float x = 0;
        float y = 0;
        int n_est_risco = 0;
        int n_fin = 0;
        float * media = NULL;
        char * nacion = NULL;
        char * pesquisa = NULL;
        int i = 0;
        
        printf("\nOpcao: ");
        fflush(stdin);
        scanf(" %d",&opcao);
        
        switch (opcao)
        {
        case 1: //mostrar a lista
            printf("Lista de estudantes: \n");
            mostrar_toda_lista(dados_alunos);
            break;

        case 2: //inserir um aluno
            printf("Insira os dados do aluno:\n");
            inserir_estudante(dados_alunos,&size_alunos);
            break;

        case 3: //remover um aluno
            i = escolher_codigo(dados_alunos);
            remover_estudante(dados_alunos, i);
            break;

        case 4: //alterar dados de um aluno
            atualizar_uma_caracteristica_estudante(dados_alunos);
            break;

        case 5: //pesquisar estudante por nome
            pesquisa = menu_obter_pesquisa(pesquisa);
            pesquisar(dados_alunos,pesquisa);
            break;

        case 6: //mostra lista por ordem alfabética do último nome
            mostrar_lista_por_ordem_apelido(dados_alunos);
            break;

        case 7: //mostrar alunos entre duas médias 
            x = menu_obter_float();
            y = menu_obter_float();
            mostrar_alunos_entre_medias(dados_alunos,x,y);
            break;

        case 8: //mostrar estudantes em risco de prescrever
            n_est_risco = estudantes_risco_prescrever(dados_alunos);
            break;

        case 9: //determinar o número de estudantes finalistas
            n_fin = n_est_finalistas(dados_alunos);
            printf("Número de estudantes finalistas: %d.\n",n_fin);
            fflush(stdin);
            break;

        case 10: //mostra a média das idades dos alunos de uma certa nacionalidade por ano
            ano_atual = 2024;
            nacion = menu_obter_nacionalidade();
            media = media_idades_nacionalidade(dados_alunos, nacion, ano_atual);
            for (i=0;i<6;i++) {
                if (media[i]!=0) {
                    printf("\nMedia das idades dos alunos da nacionalidade \"%s\" do ano %i: %f",nacion,i+1,media[i]);
                }
            }
            break;

        case 11:
            break;

        //etc
        case 12:
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