#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

#define tam 10
#define false 0
#define true 1

typedef struct {
    int simples, comp, laco, aresta, dir, fonte[tam], sumis[tam], mat[tam][tam];


} TipoGrafo;

int verificaCaminho(int atual, int vet[], int mat[tam][tam],int conf[],int *cont);
int verificaTrajeto(int atual, int vet[], int mat[tam][tam],int conf[],int mConf[tam][tam],int *cont);
int verificaCircuito_dir(int atual, int vet[], int mat[tam][tam],int conf[],int *cont,int inicio);
int verificaCircuito(int atual, int vet[], int mat[tam][tam],int conf[],int mConf[tam][tam],int *cont,int inicio);

int main(int argc, char** argv) {


    int lin, col, x = 1,confd=false,confs=false;
    TipoGrafo grafo;

    grafo.simples = true;
    grafo.comp = true;
    grafo.laco = false;
    grafo.aresta = 0;

    for (lin = 0; lin < tam; lin++) {
        grafo.fonte[lin] = true;
        grafo.sumis[lin] = true;

        for (col = 0; col < tam; col++) {
            grafo.mat[lin][col] = 999;
        }

    }

    while (x != 0) {

        printf("\n=================================\n1-Inserir nova aresta\n2-Verificar se é direcionado\n3-Verificar se é simples\n"
                "4-Verificar se é completo\n5-Imprimir matriz do grafo\n6-Verificar ciclo entre x,y,z\n7-Verificar grau de x\n"
                "8-Verificar arestas paralelas\n9-Verificar se há caminho,trajeto e circuito entre 5 vertices\n0-Sair\nDigite a opção: ");
        scanf("%d", &x);
        printf("\n=================================\n");
        
        switch (x) {

            case 1:
                confd=false;
                confs=false;
                
                printf("Digite a ligação (digite dois números. ex: 1 3 - ligação vertice 1-3 ");
                scanf("%d %d", &lin, &col);

                if (grafo.mat[lin][col] == 999) {
                    grafo.aresta++;
                    grafo.mat[lin][col] = 1;
                } else {
                    grafo.aresta++;
                    grafo.mat[lin][col]++;
                }

                if (grafo.laco == false && lin == col) {
                    grafo.laco = true;
                    grafo.simples = false;
                }
                break;

            case 2:
                confd=true;
                grafo.dir=false;
                
                lin = 0;
                col = 0;
                while (lin < tam) {
                    if (grafo.mat[lin][col] != grafo.mat[col][lin]) {
                        grafo.dir = true;
                        lin = tam;
                        break;
                    }
                    col++;

                    if (col == tam) {
                        lin++;
                        col = 0;
                    }

                }

                if (grafo.dir == true) {
                    printf("\nGrafo é dirigido\n");
                    lin = 0;
                    col = 0;
                    while (lin < tam) {
                        if (grafo.mat[lin][col] != 999 && (grafo.fonte[col] == true || grafo.sumis[lin] == true)) {
                            grafo.fonte[col] = false;
                            grafo.sumis[lin] = false;
                        }
                        col++;

                        if (col == tam) {
                            lin++;
                            col = 0;
                        }
                    }

                    int conff = 0, confs = 0;
                    for (lin = 0; lin < tam; lin++) {

                        if (grafo.sumis[lin] == true && grafo.fonte[lin] == true) {
                            grafo.sumis[lin] = false;
                            grafo.fonte[lin] = false;
                        }

                        if (grafo.fonte[lin] == true && conff == 0) {
                            conff++;
                        }
                        if (grafo.sumis[lin] == true && confs == 0) {
                            confs++;
                        }
                    }

                    if (conff == 1) {
                        printf("Há fonte nesse grafo\n");
                    } else {
                        printf("Não há fonte nesse grafo\n");
                    }

                    if (confs == 1) {
                        printf("Há sumidouro nesse grafo\n");
                    } else {
                        printf("Não há sumidouro nesse grafo\n");
                    }
                } else {
                    printf("\nGrafo não é dirigido\n");
                }
            break;

            case 3:
                confs=true;
                if (grafo.simples != false) {
                    lin = 0;
                    col = 0;
                    while (lin < tam) {
                        if (grafo.mat[lin][col] > 1 && grafo.mat[lin][col] != 999) {
                            grafo.simples = false;
                            lin = tam;
                            break;
                        }

                        col++;
                        if (col == tam) {
                            lin++;
                            col = 0;
                        }
                    }
                }

                if (grafo.simples == true) {
                    printf("Grafo é simples\n");
                } else {
                    printf("Grafo não é simples\n");
                }
            break;

            case 4:
                lin = 0;
                col = 0;
                while (lin < tam) {
                    if (grafo.mat[lin][col] == 999 && lin != col) {
                        grafo.comp = false;
                        lin = tam;
                        break;
                    }

                    col++;
                    if (col == tam) {
                        lin++;
                        col = 0;
                    }
                }

                if (grafo.comp == true) {
                    printf("Grafo é completo\n");
                } else {
                    printf("Grafo não é completo\n");
                }
            break;   
            
            case 5:
                for(lin=0;lin<tam;lin++){
                    printf("\n");
                    for(col=0;col<tam;col++){
                        printf("%d ",grafo.mat[lin][col]);
                    }
                }
                
            break;
            
            case 6:
                if(confd==false){
                    printf("\nÉ necessario rodar a verificação de direcionamento antes de usar essa função");
                }else{
                    if(grafo.dir==true){
                        int x,y,z,conf=false;

                        printf("\nDigite o número do 1° vértice: ");
                        scanf("%d",&x);
                        printf("\nDigite o número do 2° vértice: ");
                        scanf("%d",&y);
                        printf("\nDigite o número do 3° vértice: ");
                        scanf("%d",&z);

                        if(grafo.mat[x][y]!=999){
                            if(grafo.mat[y][z]!=999){
                                if(grafo.mat[z][x]!=999){
                                    conf=true;
                                }
                            }
                        }

                        if(grafo.mat[x][z]!=999 && conf==false){
                            if(grafo.mat[z][y]!=999){
                                if(grafo.mat[y][x]!=999){
                                    conf=true;
                                }
                            }
                        }

                        if(conf==true){
                            printf("\nHá ciclo entre esses vértices");
                        }else{
                            printf("\nNão há ciclo entre esses vértices");
                        }


                    }else{
                        printf("\nGrafo não é direcionado.");
                    }
                }
                
            break;    
            
            case 7:
                int x,grau=0;
                printf("\nDigite o número do vértice: ");
                scanf("%d",&x);
                
                for(int i=0;i<tam;i++){
                    if(grafo.mat[x][i]!=999){
                        grau++;
                    }
                    if(grafo.mat[i][x]!=999){
                        grau++;
                    }
                }
                printf("\nGrau do vertice %d: %d",x,grau);
                
            break;    
            
            case 8:
                int paralela=false;
                lin = 0;
                col = 0;
                while (lin < tam) {
                    if (grafo.mat[lin][col] > 1 && grafo.mat[lin][col] != 999) {
                        paralela=true;
                        lin = tam;
                        break;
                    }
                    col++;
                    if (col == tam) {
                        lin++;
                        col = 0;
                    }
                }
                        
                if(paralela==true){
                    printf("\nHá aresta paralela");
                }else{
                    printf("\nNão há aresta paralela");
                }
                        
            break;
            
            case 9:
                if (confd == false) {
                    printf("\nÉ necessario rodar a verificação de direcionamento antes de usar essa função");
                } else {
                    int vet[5], conf[5], cont = 0, verf = false,mConf[tam][tam];
                    printf("\nDigite os 5 vértices: ");

                    for (int i = 0; i < 5; i++) {
                        scanf("%d", &vet[i]);
                    }

                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            conf[j] = false;
                        }
                        cont=0;
                        conf[i]=true;
                        verf = verificaCaminho(vet[i], vet, grafo.mat, conf, &cont);
                        if (verf == true) {
                            i = 5;
                        }
                        conf[i]=false;
                    }

                    if (verf == true) {
                        printf("\nHá caminho entre os vértices");
                    } else {
                        printf("\nNão há caminho entre os vértices");
                    }
                    
                    
                    verf=false;
                    if(grafo.dir==true){
                        
                        
                        
                        for (int i = 0; i < 5; i++) { 
                            for (int j = 0; j < 5; j++) {
                                conf[j] = false;
                            }
                            cont=0;
                            conf[i] = true;
                            verf = verificaCaminho(vet[i], vet, grafo.mat, conf, &cont);
                            if (verf == true) {
                                i = 5;
                            }
                            conf[i] = false;
                        }
                    }else{
                        for(int i=0;i<5;i++){
                            for (int j = 0; j < tam; j++) {
                                if(j<5){
                                    conf[j] = false;
                                }    
                                for(int k=0;k<tam;k++){
                                    mConf[j][k]=false;
                                }
                            }
                            cont=0;
                            verf=verificaTrajeto(vet[i],vet,grafo.mat,conf,mConf,&cont);
                            if(verf==true){
                                i=5;
                            }
                        }
                        
                    }
                    
                    if(verf==true){
                        printf("\nHá trajeto entre os vértices");
                    }else{
                        printf("\nNão há trajeto entre os vértices");
                    }
                    
                    cont=0;
                    verf=false;
                    if(grafo.dir==true){
                        for (int i = 0; i < 5; i++) {
                            conf[i] = false;
                        }
                        conf[0]=true;
                        verf=verificaCircuito_dir(vet[0], vet, grafo.mat, conf, &cont,vet[0]);
                    }else{
                        for (int j = 0; j < tam; j++) {
                            if(j<5){
                                conf[j] = false;
                            }    
                            for (int k = 0; k < tam; k++) {
                                mConf[j][k] = false;
                            }
                        }
                        verf=verificaCircuito(vet[0],vet,grafo.mat,conf,mConf,&cont,vet[0]);
                    }
                    
                    if(verf==true){
                        printf("\nHá Circuito entre os vértices");
                    }else{
                        printf("\nNão há circuito entre os vértices");
                    }
                    
                }
            break;    
            
            case 0:
                printf("\nFinalizando...");
                return;
            break;
            
            default:
                printf("\nOpção invalida");
            break;    
                


        }
    }
    
    return (EXIT_SUCCESS);
}

int verificaCaminho(int atual, int vet[], int mat[tam][tam],int conf[],int *cont){
        
    int i,verf;
    
    if(*cont==4){
        i=0;
        while(i<5){
            if(conf[i]==true){
                i++;
                
                if(i==5){
                    return true;
                }
            }else{
                i=5;
            }
        }
    }
    
    for (i = 0; i < 5; i++) {
        if (mat[atual][vet[i]] != 999 && atual != vet[i]) {
            if (conf[i] == true) {
                return 2;
            }else {

                conf[i] = true;
                (*cont)++;
                verf = verificaCaminho(vet[i], vet, mat, conf, cont);
                
                if(verf!=2){
                    if (verf == true) {
                        return true;
                    } else {
                        conf[i] = false;
                        (*cont)--;
                    }        
                }
            }
        }
    }
    return false;
}

int verificaTrajeto(int atual, int vet[], int mat[tam][tam],int conf[],int mConf[tam][tam],int *cont){
        
        int verf,i;
        
        if(*cont==4){
        i=0;
        while(i<5){
            if(conf[i]==true){
                i++;
                
                if(i==5){
                    return true;
                }
            }else{
                i=5;
            }
        }
    }
        
        for(int i=0;i<5;i++){
            if(mat[atual][vet[i]]!=999 && atual!=vet[i]){
                if (mConf[atual][vet[i]] != mat[atual][vet[i]]) {
                    mConf[atual][vet[i]]++;
                    mConf[vet[i]][atual]++;
                    conf[i]=true;
                    (*cont)++;
                    verf = verificaTrajeto(vet[i], vet, mat, conf,mConf, cont);
                    if (verf == true) {
                        return true;
                    }
                }
            }
        }
        
        (*cont)--;
        return false;
        
}

int verificaCircuito_dir(int atual, int vet[], int mat[tam][tam],int conf[],int *cont,int inicio){
        
    int i,verf;
    
    if(*cont==4){
        i=0;
        while(i<5){
            if(conf[i]==true){
                i++;
                
                if(i==5){
                    if(mat[atual][inicio]!=999){
                        return true;
                    }
                }
            }else{
                i=5;
            }
        }
    }
    
    for (i = 0; i < 5; i++) {
        if (mat[atual][vet[i]] != 999 && atual != vet[i]) {
            if (conf[i] == true) {
                return 2;
            }else {

                conf[i] = true;
                (*cont)++;
                verf = verificaCircuito_dir(vet[i], vet, mat, conf, cont,inicio);
                
                if(verf!=2){
                    if (verf == true) {
                        return true;
                    } else {
                        conf[i] = false;
                        (*cont)--;
                    }        
                }
            }
        }
    }
    return false;
}

int verificaCircuito(int atual, int vet[], int mat[tam][tam],int conf[],int mConf[tam][tam],int *cont,int inicio){
        
        int verf;
        
        if(*cont==4){
            if(mat[atual][inicio]){
                return true;
            }    
        }
        
        for(int i=0;i<5;i++){
            if(mat[atual][vet[i]]!=999 && atual!=vet[i] && conf[i]==false){
                conf[i]=true;
                (*cont)++;
                verf=verificaCircuito(vet[i],vet,mat,conf,mConf,cont,inicio);
                (*cont)--;
                if(verf==true){
                    return true;
                }
            }
        }
        
        return false;
        
}