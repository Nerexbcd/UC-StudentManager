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
#include "libs/data/db.h"

#ifdef _WIN32
    #define OS "W"
    #include<windows.h>
#elif __linux__
    #define OS "L"
    #include<unistd.h>
#endif


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

        mostrar_toda_lista(base_dados->alunos);

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

        mostrar_toda_lista(base_dados->alunos);

        printf("\n\nbanananananan\n\n");

        db_remove(base_dados, 2);

        printf("%u\n",base_dados->size);

        mostrar_toda_lista(base_dados->alunos);

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