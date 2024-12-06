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

    
    int condicao_saida=0;
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
            sleep(1);
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


        int opcao = 0;
        do
        {
            /*
            switch (opcao)
            {
            case 1:constant-expression:
                code
                break;
            case 2:
                break;
            case 3:
                break;
            default: 
                printf("Erro de seleção! Por favor faça uma escolha válida.\n")
                opcao=0;
                break;
            }
            */
            //etc
        //}
        //while (opcao==0);*/


    //} while (condicao_saida==0);
 

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
  
    return 0;
}