/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Alunos
 *
 * Created on 30 de Agosto de 2022, 12:07
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

#define MM 5
#define true 1
#define false 0

typedef struct tipoPagina *tipoApontador;

typedef struct tipoPagina {
    int n;
    int r[MM];
    tipoApontador p[MM + 1];
};

void Iniciar(tipoApontador *dicionario) {

    *dicionario = NULL;

}

void Pesquisa(int x,tipoApontador ap){

    int i;
    
    if(ap==NULL){
        printf("Registro não está presente na árvore\n");
        return;
    }
    
    while(i < ap->n && x > ap->r[i-1]){
        i++;
    }
    
    if(x == ap->r[i-1]){
        x = ap->r[i-1];
        return;
    }
    
    if(x < ap.r[i-1]){
        Pesquisa(x,ap->p[i-1]);
    }else{
        Pesquisa(x,ap->p[i]);
    }
    
}

void Ins(int reg, tipoApontador ap, short *cresceu,int *retorno,tipoApontador *apretorno){
    
    long i=1, j;
    tipoApontador aptemp;
    
    if(ap==NULL){
        *cresceu=true;
        (*retorno)=reg;
        (*apretorno)=NULL;
        return;
    }
    
    while(i < ap->n && reg > ap->r[i-1]){
        i++;
    }
    
    if(reg== ap->r[i-1]){
        printf("ERRO: Registro ja está presente\n");
        *cresceu=false;
        return;
    }
    
    if(reg < ap->r[i-1]){
        i--;
    }
    
    Ins(reg,ap->p[i],cresceu,retorno,apretorno);
    
    if(!*cresceu){
        return;
    }
    
    if(ap->n <MM){
        InsereNaPagina(ap,*retorno,*apretorno);
        *cresceu=false;
        return;
    }
    
    aptemp=(tipoApontador)malloc(sizeof(tipoPagina));
    aptemp->n = 0;
    aptemp->p[0]=NULL;
}



int main(int argc, char** argv) {




    return (EXIT_SUCCESS);
}

