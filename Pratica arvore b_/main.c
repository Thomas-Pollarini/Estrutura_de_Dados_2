#include<stdlib.h>
#include<stdio.h>

#define MM  4 
#define FALSE 0
#define TRUE  1


typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    short n;
    long r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;

void Inicializa(TipoApontador *Dicionario) {
    *Dicionario = NULL;
}

void Pesquisa(long *x, TipoApontador Ap) {
    long i = 1;
    if (Ap == NULL) {
        printf("Registro nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->n && x> Ap->r[i - 1]) i++;
    if (*x == Ap->r[i - 1]) {
        *x = Ap->r[i - 1];
        printf("Registro esta presente na arvore\n");

        return;
    }
    if (x < Ap->r[i - 1])
        Pesquisa(x, Ap->p[i - 1]);
    else Pesquisa(x, Ap->p[i]);
}

void InsereNaPagina(TipoApontador Ap,long Reg, TipoApontador ApDir) {
    short NaoAchouPosicao;
    int k;
    k = Ap->n;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao) {
        if (Reg >= Ap->r[k - 1]) {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1) NaoAchouPosicao = FALSE;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(long Reg, TipoApontador Ap, short *Cresceu, long *RegRetorno, TipoApontador *ApRetorno,TipoApontador *ApIrma) {
    long i = 1; // Posição provavel do vetor em que novo indice sera inserido
    long j;
    TipoApontador ApTemp;

    if (Ap == NULL) // Critério de parada da recursão. Pode ser usado para arvore vazia, arvore com espaço em folhas ou arvore que explode
    {
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->n && Reg > Ap->r[i - 1]){
        i++; // Percorrendo vetores dos nós para encontrar valor maior (ou igual) que o novo indice
    }
    
    if (Reg == Ap->r[i - 1]) {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }

    if (Reg < Ap->r[i - 1]) {
        i--; // Como o valor nao é igual, só pode ser maior, entao volta-se uma posição
    }
    
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno,Ap->p[i+1]); // Chama-se recursivo para descer na arvore

    if (!*Cresceu) return;

    if (Ap->n < MM) /* Pagina tem espaco */ {
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno); // Chama insere na página pq tem esoaço
        *Cresceu = FALSE;
        return;
    }

    /* Overflow: Pagina tem que ser dividida */ // Página nao tem espaço suficiente
    ApTemp = (TipoApontador) malloc(sizeof (TipoPagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
    ApTemp->n = 0;
    ApTemp->p[0] = NULL; // Ela começa com zero indices e primeiro filho pra NULL
    if (i < MM*2/3 + 1) {
        InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    for (j = MM*2/3 + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
    Ap->n = (MM*2/3)+1;
    ApTemp->p[0] = Ap->p[MM*2/3 + 1];
    *RegRetorno = Ap->r[MM*2/3];
    *ApRetorno = ApTemp;
}

void Insere(long Reg, TipoApontador *Ap) {
    short Cresceu;
    long RegRetorno;
    TipoPagina *ApRetorno, *ApTemp, *ApIrma;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno, &ApIrma); // Chamando funcao insere auxiliar
    if (Cresceu) /* Arvore cresce na altura pela raiz */ {
        ApTemp = (TipoPagina *) malloc(sizeof (TipoPagina)); // Criando nova raiz
        ApTemp->n = 1; // Definindo que a nova raiz só terá um índice
        ApTemp->r[0] = RegRetorno; // Definindo valor do unico indice da raiz
        ApTemp->p[1] = ApRetorno; // Definindo filho da direita da raiz, resultado do split que causou explosao no tamanho
        ApTemp->p[0] = *Ap; // Definindo filho da esquerda da raiz, resultado do split que causou explosao no tamanho 
        *Ap = ApTemp; // Enderençando nova raiz
    }
}


void ImprimeI(TipoApontador p, int nivel) {
    long i;
    if (p == NULL) return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++)
        printf("%ld ", (long) p->r[i]);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

void Imprime(TipoApontador p) {
    int n = 0;
    ImprimeI(p, n);
}


int main(int argc, char *argv[]) {

    int t = 1;
    long x;
    TipoPagina *D;

    while (t != 0) {

        printf("\n1-Cria árvore\n2-Insere dados na árvore\n3-Busca por uma informação\n4-Mostra dados por nível\n0-Finalizar\nDigite uma opção:");
        scanf("%d", &t);

        switch (t) {

            case 1:
                Inicializa(&D);
                break;

            case 2:
                printf("\nChave: ");
                scanf("%ld%*[^\n]", &x);
                getchar();
                Insere(x, &D);

                break;

            case 3:
                printf("\nChave: ");
                scanf("%ld%*[^\n]", &x);
                getchar();
                Pesquisa(&x, D);
                break;

            case 4:
                Imprime(D);
                printf("\n");
                break;

            case 0:
                return 0;
                break;

            default:
                printf("\nOpção inválida\n");
                break;
        }
    }
    return 0;

}
