#include <stdio.h>
#include "jogo.h"
#include "matdin.h"
#include "estruturas.h"


// print de uma mensagem a dizer que um tabuleiro foi ganho
//
int main() {
        // DECLARAÇÃO VARIAVEIS
        char **tabuleiro = NULL;
        tabuleiro = criaMat(9,9);// array bidimensional
        int jogotipo = 0; // opcao de tipo de jogo
        int opcao_menu;//opcao de jogada
        int njogada = 1; // conta n jogada
        char jogador = 'X'; // qual é o jogador
        int id_tab = 0; //id de um tabuleiro de 1 a 9
        char* ver_tab [9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'}; // vetor verifica se o mini tab esta ganho ou nao
        int win; // verifica vitoria de jogo
        his* cabeca = NULL; // lista ligada
        int id_tab_atual;//-> tabuleiro atual
        char retomar; //-> opção de retomar jogada
        int* tpjogo = NULL;
        FILE* file;
        char texto [12];
        int buffer = 12;
        int* idptr;
        idptr = &id_tab_atual;
        int k;


        //verificação se existe um jogo que se possa recuperar ou não
    file = fopen("jogo.bin", "r");
    if (file != NULL) {

        if (!feof(file)) {

            fclose(file);
            do {
                printf("\n Deseja continuar o jogo anterior?(S/N)\n");
                retomar = getchar();
                printf("\n");
            } while (retomar != 'S' && retomar != 'N');
            if (retomar == 'N') {
                remove("jogo.bin");
            }
            if (retomar == 'S') {
                file = fopen("jogo.bin", "r");
                fread(texto, sizeof(char), 2,file);

                if (strcmp(texto, "2P") == 0){
                    tpjogo = 1;
            } else tpjogo = 2;

            cabeca = retomarjogo(cabeca, tabuleiro, ver_tab);

            printf("Jogo carregado!\n\n");
            njogada = ultimajog(cabeca) + 1;
            id_tab =  ultimotab( cabeca);
            if('X' == ultimojogador(cabeca)) {
                jogador = '0';
            }else jogador = 'X';

            }
        }
    }

//MENU TIPO DE JOGO
        if(retomar == 'N' || njogada == 1) {
            printf("--------------------------------------------------------\n");
            printf("|         !BEM-VINDO AO ULTIMATE TIC TAC TOE!          |\n");
            printf("| 1. Jogo para 2 players                               |\n");
            printf("| 2. Jogar contra computador                           |\n");
            printf("| 9. Fechar o Jogo                                     |\n");
            printf("--------------------------------------------------------\n\n");
        }
    //MENU JOGADA
        do {
            if(retomar == 'N' || njogada == 1){
                printf( "Escolha o tipo de jogo:");
                scanf("%d",&jogotipo);
            }else {
                jogotipo = tpjogo;
            }
            switch (jogotipo) {
                case 1 :
                    if(njogada==1){
                        file = fopen("jogo.bin","w");
                        fwrite("2P", sizeof(char),2,file);

                        fclose(file);
                    }
                do{
                    if(njogada %2 == 0){jogador = 'O';
                    }else jogador = 'X';
                    printf("\n");
                    printf("      Jogada %d",njogada);
                    printf("\n-----Turno do %c------\n\n", jogador);
                    show_tabuleiro(tabuleiro,9);
                    printf("\n1 - Colocar uma peca\n");
                    printf("2 - Ver o historico das ultimas 10 jogadas\n");
                    printf("9 - Terminar o jogo\n");
                    printf("\nEscolha uma opcao:");
                    scanf("%d",&opcao_menu);

                    switch (opcao_menu) {
                        case 1:
                            id_tab_atual =id_tab;
                            id_tab = fazerjogada( jogador,tabuleiro, njogada,idptr, id_tab, ver_tab);
                            cabeca = atualiza_his(cabeca,id_tab_atual,id_tab,jogador,njogada);

                            win = vitoria(ver_tab,jogador);
                            if(win == 1){
                                printf("\n");
                                show_tabuleiro(tabuleiro,9);
                                libertaMat(tabuleiro,9);
                                exportaficheiro( cabeca, jogador);
                                return 0;
                            }
                            njogada++;
                            break;
                        case 2:
                            imprime_historico(cabeca,njogada); // fazer lista ligada para as jogadas anteriores
                            continue;
                        case 9:
                            printf("\n--------Game over--------\n");
                            printf(" See You Later Aligator \n");
                            break;
                        default:
                            printf("\n \n...selecione uma opcao valida...\n\n");
                    }
                }while(opcao_menu != 9);

                return 0;

                case 2:
                    if(njogada==1){
                        file = fopen("jogo.bin","a");
                        fprintf(file,"PC\n");
                        fwrite("PC", sizeof(char),2,file);
                        fclose(file);
                    }
                    printf("\n");
                    do{
                        if(njogada %2 == 0){
                            jogador = 'O';
                            id_tab_atual = id_tab;
                            printf("\n");
                            printf("      Jogada %d",njogada);
                            printf("\n-----Turno do %c------\n\n", jogador);
                            show_tabuleiro(tabuleiro,9);
                            id_tab =  computador(id_tab,ver_tab,tabuleiro,njogada,jogador);
                            cabeca = atualiza_his(cabeca,id_tab_atual,id_tab,jogador,njogada);
                            win = vitoria(ver_tab,jogador);
                            if(win == 1){
                                libertaMat(tabuleiro,9);
                                return 0;
                            }
                            njogada++;

                        }else {
                            jogador = 'X';

                            printf("\n");
                            printf("      Jogada %d",njogada);
                            printf("\n-----Turno do %c------\n\n", jogador);
                            show_tabuleiro(tabuleiro,9);
                            printf("\n1 - Colocar uma peca\n");
                            printf("2 - Ver o historico das ultimas 10 jogadas\n");
                            printf("9 - Terminar o jogo\n");
                            printf("\nEscolha uma opcao:");
                            scanf("%d",&opcao_menu);
                            switch (opcao_menu) {
                                case 1:
                                    id_tab = fazerjogada( jogador,tabuleiro, njogada,idptr ,id_tab, ver_tab);
                                    cabeca = atualiza_his(cabeca,id_tab_atual,id_tab,jogador,njogada);
                                    //printf("\n%d\n",cabeca->njogada);
                                    win = vitoria(ver_tab,jogador);
                                    if(win == 1){
                                        printf("\n");
                                        show_tabuleiro(tabuleiro,9);
                                        libertaMat(tabuleiro,9);
                                        exportaficheiro( cabeca, jogador);
                                        return 0;
                                    }
                                    njogada++;
                                    break;
                                case 2:

                                    imprime_historico(cabeca,njogada); // fazer lista ligada para as jogadas anteriores
                                    continue;
                                case 9:
                                    printf("\n--------Game over--------\n");
                                    printf(" See You Later Aligator \n");
                                    break;
                                default:
                                    printf("\n \n...selecione uma opcao valida...\n\n");
                            }
                        }
                    }while(opcao_menu != 9);

                    return 0;

                case 9:
                    printf("\n-------BYE BYE-------\n");
                    printf(" See You Later Aligator \n");
                    break;
                default:
                    printf("\nOpcao inexistente, por-favor selecione uma das indicadas!\n");
            }

        }while( jogotipo != 9 );
    libertaMat(tabuleiro,9);
    return 0;
}
