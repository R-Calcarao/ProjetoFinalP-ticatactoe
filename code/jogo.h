//
// Created by rodri on 30/05/2022.
// Rodrigo da Silva Calçarão - 2019134575
//

#ifndef CODE_JOGO_H
#define CODE_JOGO_H



void show_tabuleiro(char **matriz, int i);

int fazerjogada ( char jogador, char** tabuleiro,int njogada,int* idptr,int id_tab, char* ver_tab);

int verifica(int offsetx,int offsety, char** tabuleiro, int jogador);

int vitoria(char* ver_tab,char jogador);

int computador(int id_tab,char* ver_tab,char** tabuleiro,int njogada,char jogador);


#endif //CODE_JOGO_H
