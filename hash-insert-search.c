/*
    Data una tabella di Hash T1 di dimensione N, implementata mediante liste di adiacenza, 
    gestita tramite una semplice funzione di hash:

	H(k, N) = k mod N
	
    a. Scrivete la funzione di inserimento di un nuovo elemento che, una volta ottenuta 
       la posizione in tabella, chiamando la funzione di Hash, invece di inserire il nuovo 
       elemento in testa o in coda alla relativa lista di adiacenza, inserisca l'elemento 
       in modo ordinato (seguendo ordinamento crescente).
    b. Scrivete la funzione di ricerca di un elemento ottimizzata: la ricerca si ferma 
       quando l'elemento è trovato (restituendo 1), o non appena si accorge che l'elemento cercato 
       non può essere presente nella lista di adiacenza, sfruttando la relazione di ordinamento (restituire 0).
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


typedef struct bucket_lista {
   int info;
   struct bucket_lista *next;
} *bucket_lista; 
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


int h (long int k, int N) 
{
    return k%N;
}


// Funzione di inserimento ordinato del valore k 
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


void caricamento_randomizzato_tabella (HashTable T, int N, int M) {
    srand (time(NULL));

    for (int i=0; i<=M; i++) {
        int r= rand() % 100;
            hash_insert (T, N, r);
    }
}


int hash_search(HashTable T, int N, int k) {
    int pos = h(k,N);
    bucket_lista el = T[pos];
    while (el != NULL) {
        if(el->info == k) return 1;
        else if(el->info > k) return 0;
        el = el->next;
    }
    return 0;
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
	if(argc>1) errore("Non usare argomenti per questo eseguibile");

    HashTable T = newTable(10);
    caricamento_randomizzato_tabella(T,10,20);
    stampa(T,10);
    int j = hash_insert(T,10,90);
    printf("\n\n\nPosizione: %d\n", j);
    stampa(T,10);
    int num = hash_search(T,10,90);
    if(num==1) printf("\nTrovato!\n");
    else if(num!=1) printf("\nNon trovato!\n");


    return 0;
}