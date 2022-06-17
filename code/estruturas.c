//
// Created by rodri on 09/06/2022.
// Rodrigo da Silva Calçarão - 2019134575
//

#include "estruturas.h"

his* atualiza_his(his* cabeca,int id_tab_atual, int id_tab,char jogador,int njogada){
    int x,y;
    switch (id_tab) {
        case 1:
            x=1;
            y=1;
            break;
        case 2:
            x=1;
            y=2;
            break;
        case 3:
            x=1;
            y=3;
            break;
        case 4:
            x=2;
            y=1;
            break;
        case 5:
            x=2;
            y=2;
            break;
        case 6:
            x=2;
            y=3;
            break;
        case 7:
            x=3;
            y=1;
            break;
        case 8:
            x=3;
            y=2;
            break;
        case 9:
            x=3;
            y=3;
            break;
    }
    his* atual,*novo = (his*)malloc(sizeof (his)); // alocar memoria para guardar a nova jogada

    novo->id_tab_atual = id_tab_atual;
    novo->x = x;
    novo->y = y;
    novo->jogador = jogador;
    novo->njogada = njogada;
    novo-> prox = NULL;

    if (cabeca == NULL){
        cabeca = novo;
    }else {
        atual = cabeca;
        while(atual->prox != NULL){
            atual = atual ->prox;
        }
        atual->prox = novo;
    }
    FILE *fp;

    fp = fopen("jogo.bin", "a");
    if(fp == NULL){
        printf("\nERRO NA ABERTURA DO FICHEIRO");
        exit(0);
    }else{
        fwrite(&njogada, sizeof(njogada),1,fp);
        fwrite(&jogador, sizeof(jogador),1,fp);
        fwrite(&id_tab_atual, sizeof(id_tab_atual),1,fp);
        fwrite(&x, sizeof(x),1,fp);
        fwrite(&y, sizeof(y),1,fp);

    }
    fclose(fp);

    return cabeca;
}

his* atualiza_LISTA(his* cabeca,int id_tab_atual, int id_tab,char jogador,int njogada){
    int x,y;
    switch (id_tab) {
        case 1:
            x=1;
            y=1;
            break;
        case 2:
            x=1;
            y=2;
            break;
        case 3:
            x=1;
            y=3;
            break;
        case 4:
            x=2;
            y=1;
            break;
        case 5:
            x=2;
            y=2;
            break;
        case 6:
            x=2;
            y=3;
            break;
        case 7:
            x=3;
            y=1;
            break;
        case 8:
            x=3;
            y=2;
            break;
        case 9:
            x=3;
            y=3;
            break;
    }
    his* atual,*novo = (his*)malloc(sizeof (his)); // alocar memoria para guardar a nova jogada

    novo->id_tab_atual = id_tab_atual;
    novo->x = x;
    novo->y = y;
    novo->jogador = jogador;
    novo->njogada = njogada;
    novo-> prox = NULL;

    if (cabeca == NULL){
        cabeca = novo;
    }else {
        atual = cabeca;
        while(atual->prox != NULL){
            atual = atual ->prox;
        }
        atual->prox = novo;
    }

    return cabeca;
}


//falta conseguir enviar os valores de x e y
void imprime_historico(his* cabeca, int njogada){
    his* atual;
    int k; // numero de jogadas que quer ver
    int passada;

    printf("Quantas jogadas pretende ver? (de 1 a 10):");
    scanf("%d",&k);
    printf("\n");
    passada = njogada - k;

    if(cabeca == NULL) printf("\nAinda não houve jogadas!\n");
    else {
        atual = cabeca;
        while(atual->prox != NULL){
           if(atual-> njogada >= passada) {
               printf("numero jogada:%d\njogador:%c\ntab:%d\nx:%d\ny:%d\n---------\n",atual->njogada,atual->jogador,atual->id_tab_atual,atual->x,atual->y);
           }
            atual = atual ->prox;
        }
    }
};

his* retomarjogo(his* cabeca, char** tabuleiro, char* ver_tab){

    FILE *fp;
    char texto [12];
    int buffer = 12;
    int jogada;
    char jogador;
    int id_tab;
    int id_tab_atual;
    int x,y;
    int offsetx, offsety;
    int ganhou;

    fp = fopen("jogo.bin", "r");
    if(fp == NULL){
        printf("\nERRO NA ABERTURA DO FICHEIRO");
        exit(0);
    }else{
        fread(texto, sizeof(char),2,fp);
        while(!feof(fp)){

            fread(&jogada, sizeof(jogada),1,fp);
            fread(&jogador, sizeof(jogador),1,fp);
            fread(&id_tab_atual, sizeof(id_tab_atual),1,fp);
            fread(&x, sizeof(x),1,fp);
            fread(&y, sizeof(y),1,fp);

            id_tab = 3*(x-1) + y;

            cabeca = atualiza_LISTA(cabeca, id_tab_atual, id_tab, jogador, jogada);

            switch (id_tab_atual) {
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

            tabuleiro [offsetx + (x-1)][offsety + (y-1)] = jogador;
            ganhou = verifica(offsetx,offsety,tabuleiro,jogador);

            if(ganhou == 1){
                for (int k = 1; k < 4; k++){
                    for(int l = 1; l < 4 ;l++){
                        tabuleiro [offsetx + (k-1)][offsety + (l-1)] = jogador;
                    }
                }
                if(jogador == 'X'){
                    ver_tab[id_tab_atual-1] = 'X';
                }else if (jogador == 'O') ver_tab[id_tab_atual-1] = 'O';
            }
        }
    }
    fclose(fp);
    return cabeca;
}
int ultimajog(his* cabeca){
    his* atual;


    if(cabeca == NULL) printf("\nAinda não houve jogadas!\n");
    else {

        atual = cabeca;

        while(atual->prox != NULL){
            atual = atual ->prox;
        }
        return atual->njogada;
    }
    return 0;
}

int ultimotab(his* cabeca){
    his* atual;
    int id_tab;
    int x,y;

    if(cabeca == NULL) printf("\nAinda não houve jogadas!\n");
    else {

        atual = cabeca;

        while(atual->prox != NULL){
            atual = atual ->prox;
        }

        id_tab = 3*(atual->x-1) + atual->y;
        return id_tab;
    }
    return 0;
}

int ultimojogador(his* cabeca){
    his* atual;
    char jogador;


    if(cabeca == NULL) printf("\nAinda não houve jogadas!\n");
    else {

        atual = cabeca;

        while(atual->prox != NULL){
            atual = atual ->prox;
        }
        return atual->jogador;
    }
    return 0;
}

void exportaficheiro(his* cabeca,char jogador) {

    char nome[50] = "";
    his* atual;
    FILE *fp;
    do {
    printf("Que nome deseja dar ao ficheiro?");
    scanf("%s", nome);
    }while(nome [0] == '\0');

    sprintf(nome,"%s.txt",nome); // passa aquele teto para variavel

    fp = fopen(nome, "w");
    if(fp == NULL){

        printf("\nERRO NA ABERTURA DO FICHEIRO");
        exit(0);
    }else{
        atual = cabeca ;
        //printf("\n Ficheiro Aberto com sucesso");
        while(atual != NULL) {
            fprintf(fp, "Jogada:%d\nJogador:%c\ntab:%d\nx:%d\ny:%d\n", atual->njogada, atual->jogador,
                    atual->id_tab_atual, atual->x, atual->y);
            fprintf(fp, "----\n");
            atual = atual->prox;
        }
        fprintf(fp,"Vencedor: %c\n", jogador);
    }

    fclose(fp);


}