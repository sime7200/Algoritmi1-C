#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo_albero {
	int info;
	struct nodo_albero *sx, *dx;
};
typedef struct nodo_albero *Albero;


void errore(char *mess){
	perror(mess);
	exit(EXIT_FAILURE);
}


Albero crea_nodo(int num) {
    Albero a = malloc(sizeof(Albero));
    if(a!=NULL) {
        a->info=num;
        a->dx=NULL;
        a->sx=NULL;
    }
    return a;
}


Albero inserisci(Albero root, int n) {
    Albero a;
    if(root==NULL) {
        a = crea_nodo(n);
        return a;
    }
    else if(n<root->info) {
        root->sx = inserisci(root->sx,n);
    }
    else if(n>root->info) {
        root->dx = inserisci(root->dx,n);
    }
    return root;
}


Albero carica_ABR (Albero root) {
	int a[15]={50,17,72,12,23,54,76,9,14,19,67,1,99,73,3};
	for(int i=0; i<15; i++) root=inserisci(root, a[i]);
	return root;
}


int conta_nodi(Albero root){
    if(root==NULL) return 0;
    int sin=0;
    int des=0;
    if(root->sx!=NULL) sin = 1 + conta_nodi(root->sx);
    if(root->dx!=NULL) des = 1 + conta_nodi(root->dx);
    return sin + des;
}


int conta_foglie(Albero root) {
    if(root==NULL) return 0;
    if(root->sx==NULL && root->dx==NULL) return 1;
    int sin = conta_foglie(root->sx);
    int des = conta_foglie(root->dx);
    return sin + des;
}
/*
stessa funzione sopra
int num_foglie(Albero root){
    if(root==NULL) return 0;
    if(root->sx==NULL && root->dx==NULL) return 1;
    return num_foglie(root->sx) + num_foglie(root->dx);
} 
*/

int conta_pari(Albero root) {
    if(root==NULL) return 0;
    if(root->info%2==0) return 1 + conta_pari(root->sx) + conta_pari(root->dx); 
    return conta_pari(root->sx) + conta_pari(root->dx);
}


int somma_nodi(Albero root) {
    if(root==NULL) return 0;
    return root->info + somma_nodi(root->sx) + somma_nodi(root->dx);
}


int somma_pari(Albero root) {
    if(root==NULL) return 0;
    if(root->info %2 == 0) return root->info + somma_pari(root->sx) + somma_pari(root->dx);
    return somma_pari(root->sx) + somma_pari(root->dx);
}


int maxNum(int a, int b) {
    if(a<b) return b;
    else return a;
}

int altezza(Albero a){
    if(a==NULL) return -1;
    int sin = 1 + altezza(a->sx);
    int des = 1 + altezza(a->dx);
    return maxNum(sin,des);
}


int massimo(Albero root) {
    if(root==NULL) return;
    if(root->dx == NULL) return root->info;
    return massimo(root->dx);    
}


bool trovaValore(Albero root, int x) {
    if(root==NULL) return false;
    if(root->info==x) return true;
    if(x<root->info) return trovaValore(root->sx,x);
    if(x>root->info) return trovaValore(root->dx,x);
}



void stampa(Albero a) 
{
    if(a==NULL) return;
    printf("%d\t", a->info);
    stampa(a->sx);
    stampa(a->dx);
}


int main(int argc, char** argv){
	if(argc>1) errore("Non usare argomenti per questo eseguibile");

    Albero lis = malloc(sizeof(Albero));
    if(lis==NULL) return 1;
    lis=carica_ABR(lis);
    stampa(lis);
    lis=inserisci(lis,2);
    printf("\n\nStampa dopo inserimento: ");
    stampa(lis);
    int ris = conta_nodi(lis);
    printf("\nNodi: %d\n", ris);
    int sum = somma_nodi(lis);
    printf("Somma: %d\n", sum);
    int pari = somma_pari(lis);
    printf("Somma pari: %d\n", pari);
    int h = altezza(lis);
    printf("Altezza: %d\n", h);

    int mas = massimo(lis);
    printf("Massimo: %d\n", mas);
    int foglie = conta_foglie(lis);
    printf("Conta foglie: %d\n", foglie);
    bool val = trovaValore(lis, 2);
    if(val) printf("Trovato il 2!\n");
    
    return 0;
}