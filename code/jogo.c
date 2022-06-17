//
// Created by rodri on 30/05/2022.
// Rodrigo da Silva Calçarão - 2019134575
//

#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "estruturas.h"
#include "utils.h"


void show_tabuleiro(char ** matriz, int i) {
    int l, j;//l - linhas || j - colunas
    int nLin, nCol;
    for (l=0; l < i; l++){
        if(l == 3){printf("---------------------\n");}
        if(l == 6){printf("---------------------\n");}


        for(j=0 ; j < i; j++){

            if(j == 3){printf("| ");}
            if(j == 6){printf("| ");}
            //if(j == 9){printf("\n",j);}

            if(matriz[l][j] == NULL) {      // verificar se esta vazio
                printf("_ ");
            } else
                printf("%c ", matriz[l][j]);
        }
        printf("\n");
    }
};

int verifica(int offsetx, int offsety, char** tabuleiro, int jogador){
    int x,y;
    for(x = 1; x <= 3; x++){
        if((tabuleiro[offsetx + (x-1)][offsety + 0] == jogador ) && (tabuleiro[offsetx + (x-1)][offsety + 1] == jogador)  && (tabuleiro[offsetx + (x-1)][offsety + 2] == jogador) ){ // verifica as linhas
                return 1;
        }
    }
    for(y = 1; y <= 3; y++){
        if((tabuleiro[offsetx + 0][offsety + (y-1)] == jogador ) && (tabuleiro[offsetx + 1][offsety + (y-1)] == jogador)  && (tabuleiro[offsetx + 2][offsety + (y-1)] == jogador) ){// verifica as colunas
            return 1;
        }
    }
    if((tabuleiro[offsetx + 0][offsety + 0] == jogador ) && (tabuleiro[offsetx + 1][offsety + 1] == jogador)  && (tabuleiro[offsetx + 2][offsety + 2] == jogador)){ //verifica a diagonal esquerda para a direita
        return 1;
    }
    if((tabuleiro[offsetx + 0][offsety + 2] == jogador ) && (tabuleiro[offsetx + 1][offsety + 1] == jogador)  &&  (tabuleiro[offsetx + 2][offsety + 0]) == jogador){ // verifica a diagonal direita para a esquerda
        return 1;
    }
    return 0;
};



// adicionar verficação de vitoria de tres tabuleiros completos

int fazerjogada (char jogador, char** tabuleiro,int njogada,int* idptr,int id_tab, char* ver_tab){
    int x,y; // x - posicao no eixo x -> linhas y - posicao no eixo y -> colunas
    int ganhou;
    int offsetx, offsety; // limites de mini tabuleiros
        if( njogada == 1 || ver_tab[id_tab - 1] == 'X' || ver_tab[id_tab - 1] == 'O'){// se uma casa já estiver ganha o outro player pode jogar onde quiser

            do {
                if(ver_tab[id_tab - 1] == 'O' || ver_tab[id_tab - 1] == 'X'){
                    printf("Selecione um tabuleiro disponivel!");
                };

                printf("\nEm qual Tabuleiro deseja jogar?(1 a 9)\n");
                int i, j, num = 1;


                for(i = 0; i < 3; i++){
                    for(j = 0; j < 3; j++){
                        printf("| ");
                        printf("%d ", num);
                        num++;
                    }
                    printf("| ");
                    printf("\n");
                }
                printf("Indique:");
                scanf("%d", &id_tab);
                *idptr = id_tab;
            } while (id_tab < 1 || id_tab > 9 || ver_tab[id_tab - 1] == 'X'|| ver_tab[id_tab - 1] == 'O' );
        };

        switch (id_tab) {
            case 1:
                offsetx = 0;
                offsety = 0;
                break;
            case 2:
                offsetx = 0;
                offsety = 3;
                break;
            case 3:
                offsetx = 0;
                offsety = 6;
                break;
            case 4:
                offsetx = 3;
                offsety = 0;
                break;
            case 5:
                offsetx = 3;
                offsety = 3;
                break;
            case 6:
                offsetx = 3;
                offsety = 6;
                break;
            case 7:
                offsetx = 6;
                offsety = 0;
                break;
            case 8:
                offsetx = 6;
                offsety = 3;
                break;
            case 9:
                offsetx = 6;
                offsety = 6;
                break;

        }
        printf("Onde quer colocar a peca no tabuleiro %d?\n",id_tab);
        do {

            do {
                printf("\nLinha (1 a 3):");
                scanf("%d", &x);
                if (x > 3 || x < 1) {
                    printf("Aviso : Selecione uma linha de 1 a 3!");
                }
            } while (x < 1 || x > 3);

            do {
                printf("Coluna (1 a 3):");
                scanf("%d", &y);
                if (y > 3 || y < 1) {
                    printf("Aviso : Selecione uma coluna de 1 a 3!");
                }
            } while (y < 1 || y > 3);

        }while(tabuleiro [offsetx + (x-1)][offsety + (y-1)] == 'X' || tabuleiro [offsetx + (x-1)][offsety + (y-1)] == 'O');

        tabuleiro [offsetx + (x-1)][offsety + (y-1)] = jogador; // guarda na matriz a jogada
        ganhou = verifica(offsetx,offsety,tabuleiro,jogador);

        if(ganhou == 1){
            for (int k = 1; k < 4; k++){
                for(int l = 1; l < 4 ;l++){
                    tabuleiro [offsetx + (k-1)][offsety + (l-1)] = jogador;
                }
            }
            if(jogador == 'X'){
                ver_tab[id_tab-1] = 'X';
            }else if (jogador == 'O') ver_tab[id_tab-1] = 'O';
        }
         id_tab = 3*(x-1) + y; // saber qual tabuleiro da proxima jogada
        return  id_tab;

};

int vitoria(char* ver_tab, char jogador){ // aqui ele verifica todas as combinações no array apra saber se existe vitória
    int n;
    if(ver_tab[0] == jogador  && ver_tab[1] == jogador  && ver_tab[2] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[3] == jogador  && ver_tab[4] == jogador  && ver_tab[5] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[6] == jogador  && ver_tab[7] == jogador  && ver_tab[8] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[0] == jogador  && ver_tab[3] == jogador  && ver_tab[6] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[1] == jogador  && ver_tab[4] == jogador  && ver_tab[7] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[2] == jogador  && ver_tab[5] == jogador  && ver_tab[8] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[2] == jogador  && ver_tab[4] == jogador  && ver_tab[6] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }else if(ver_tab[0] == jogador  && ver_tab[4] == jogador  && ver_tab[8] == jogador){
        printf("Parabens o jogador %c ganhou!", jogador);
        return 1;
    }
    for(int v = 0; v < 9;v++){
        if (ver_tab[v] == NULL) {
            return 0;
        }
    }
    printf("Empate");
    return 1;
}

int computador(int id_tab,char* ver_tab,char** tabuleiro,int njogada, char jogador){
    int x;
    int y;
    int offsetx;
    int offsety;
    int ganhou;


    if( ver_tab[id_tab - 1] == 'X' || ver_tab[id_tab - 1] == 'O') {// se uma casa já estiver ganha o outro player pode jogar onde quiser
        do{
          id_tab =  intUniformRnd(1, 9);
        } while (id_tab < 1 || id_tab > 9 || ver_tab[id_tab - 1] == 'X' || ver_tab[id_tab - 1] == 'O');
    }
    switch (id_tab) {
        case 1:
            offsetx = 0;
            offsety = 0;
            break;
        case 2:
            offsetx = 0;
            offsety = 3;
            break;
        case 3:
            offsetx = 0;
            offsety = 6;
            break;
        case 4:
            offsetx = 3;
            offsety = 0;
            break;
        case 5:
            offsetx = 3;
            offsety = 3;
            break;
        case 6:
            offsetx = 3;
            offsety = 6;
            break;
        case 7:
            offsetx = 6;
            offsety = 0;
            break;
        case 8:
            offsetx = 6;
            offsety = 3;
            break;
        case 9:
            offsetx = 6;
            offsety = 6;
            break;
    }
    do {
        x = intUniformRnd(1,3);
        y = intUniformRnd(1,3);
    }while(tabuleiro [offsetx + (x-1)][offsety + (y-1)] == 'X' || tabuleiro [offsetx + (x-1)][offsety + (y-1)] == 'O');

    tabuleiro [offsetx + (x-1)][offsety + (y-1)] = jogador;
    ganhou = verifica(offsetx,offsety,tabuleiro,jogador);

    if(ganhou == 1){
        for (int k = 1; k < 4; k++){
            for(int l = 1; l < 4 ;l++){
                tabuleiro [offsetx + (k-1)][offsety + (l-1)] = jogador;
            }
        }
       ver_tab[id_tab-1] = 'O';
    }
    id_tab = 3*(x-1) + y; // saber qual tabuleiro da proxima jogada
    return  id_tab;
}


