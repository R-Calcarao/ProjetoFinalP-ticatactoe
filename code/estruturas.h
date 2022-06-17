//
// Created by rodri on 31/05/2022.
// Rodrigo da Silva Calçarão - 2019134575
//

#ifndef CODE_ESTRUTURAS_H
#define CODE_ESTRUTURAS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jogo.h"

typedef struct historico{
    int id_tab_atual;
    int x;
    int y;
    char jogador;
    int njogada;
    struct historico *prox;
}his;


his* atualiza_his(his* cabeca,int id_tab_atual,int id_tab,char jogador,int njogada);

his* atualiza_LISTA(his* cabeca,int id_tab_atual, int id_tab,char jogador,int njogada);

void imprime_historico (his* cabeca,int njogada); // conseguir enviar os x e y

his* retomarjogo(his* cabeca, char** tabuleiro,char* ver_tab);

int ultimajog(his* cabeca);

int ultimotab(his* cabeca);

int ultimojogador(his* cabeca);

void exportaficheiro(his* cabeca,char jogador);




#endif //CODE_ESTRUTURAS_H
