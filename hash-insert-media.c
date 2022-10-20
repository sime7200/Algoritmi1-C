#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define A 0.618033989

/*
    Scrivere una funzione che calcoli la lunghezza media delle liste concatenate che 
    si sono formate al termine dell'inserimento.
    Questo valore è dato dal numero di chiavi contenute nella tabella di Hash, 
    diviso per il numero di bucket non vuoti.

*/


typedef struct bucket_lista {
   int info;
   struct bucket_lista *next;
} *bucket_lista; // struttura che definisce il contenuto di un bucket da gestire con liste concatenate
typedef bucket_lista *HashTable;


HashTable newTable (int N) {
	HashTable T= (HashTable)calloc (N, sizeof (bucket_lista));
	return T;
}


void errore(char *mess){
	perror(mess);
	exit(EXIT_FAILURE);
}


// funzione per la creazione di un nuovo bucket data la chiave
bucket_lista newBucket (int k) {
	bucket_lista nuovoBucket = (bucket_lista)malloc (sizeof(struct bucket_lista));
	if (nuovoBucket == NULL) printf ("ERRORE: mancata allocazione della memoria per il nuovo bucket\n\n");
	else {
		nuovoBucket->info= k;
		nuovoBucket->next= NULL;
	}
	return nuovoBucket;
}

int h(long int k, int N) {
    return N * ((double)k*A - (int)(k*A));
}


int hash_insert (HashTable T, int N, int k) {
    int j = h(k,N);
    bucket_lista b = newBucket(k);
    if(T[j] == NULL) T[j] = b;
    else if(T[j]->info > k) {
        b->next = T[j];
        T[j] = b;
    }
    else {
        bucket_lista el = T[j];
        while (el->next != NULL) {
            if(el->next->info > k) {
                b->next = el->next;
                el->next = b;
                break;
            }
            el = el->next;
        }
        el->next = b;
    }
    return j;
}



float media(HashTable T, int N) {
    int sum=0;
    int num=0;
    for(int i=0; i<N; i++) {
        bucket_lista el = T[i];
        num += 1;
        while (el != NULL) {
            sum += 1;
            el = el->next;
        }
    }
    return (float)sum/num;
}


void caricamento_randomizzato_tabella (HashTable T, int N, int M) {
    srand (time(NULL));

    for (int i=0; i<=M; i++) {
        int r= rand() % 100;
            hash_insert (T, N, r);
    }
}


void stampa(HashTable T, int N) {
    for(int i=0; i<N; i++) {
        printf("\n");
        bucket_lista el = T[i];
        while (el != NULL) {
            printf("%d\t", el->info);
            el = el->next;
        }
    }
    printf("\n");
}


int main(int argc, char **argv) {
    if(argc!=1) errore("Inserire solo il nome dell'eseguibile.\n");
    HashTable T = newTable(10);
    caricamento_randomizzato_tabella(T,10,90);
    stampa(T,10);
    int j = hash_insert(T,10,200);
    printf("\n\n\nPosizione: %d\n", j);
    stampa(T,10);
    printf("\n\n---------------------------------------------------");

    printf("\n\nLa media dei valori in ogni lista e': %.2f\n", media(T,10));
    
    return 0;
}