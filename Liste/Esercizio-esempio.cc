//Creazione di una lista singolarmente collegata
//Definisci una struct Nodo con un campo intero val e un puntatore next.
//Crea manualmente una lista con 3 nodi (senza cicli) e stampa i valori.
//Inserimento in testa -> scrivi una funzione void inserisciInTesta(Nodo*& testa, int valore) che inserisce un nuovo nodo all'inizio della lista.
//Stampa della lista -> Scrivi una funzione void stampaLista(Nodo* testa) che stampa tutti gli elementi della lista.
//Conteggio elementi -> Scrivi una funzione int contaElementi(Nodo* testa) che restituisce quanti nodi ci sono.

#include <iostream>
using namespace std;

//Definizione della lista
struct nodo {
    int inf;
    nodo * puntatore;
};
typedef nodo * lista;       // Ho creato un tipo di dato lista che è un puntatore a nodo

int head (lista l) { //Restituisce il valore del primo elemento della lista
    return l->inf;
}

lista tail (lista l) { //Restituisce il puntatore al secondo elemento della lista
    return l->puntatore;
}

void stampalista (lista l) {
    while (l != NULL) {             // Finché l non è NULL, cioè finché ci sono nodi nella lista
        cout << head(l) << " ";     // Stampa il valore del nodo corrente
        l = tail(l);                // Aggiorna il puntatore per passare al nodo successivo
    }
    cout << endl;                   // Aggiunge una nuova riga alla fine della stampa
}

void contaelementi (lista l, int conta) {
    if (l != NULL) 
        contaelementi(tail(l), conta + 1);              // Chiamata ricorsiva per il nodo successivo, incrementando il contatore
    else 
        cout << "Numero di elementi nella lista: " << conta << endl;    // Stampa il numero totale di nodi 
}


int main () {
    // Creo manualmente una lista con 3 nodi
    lista testa = new nodo;                                 // Creo il primo nodo
    testa->inf = 1;                                         // Assegno il valore 1 al primo nodo
    testa->puntatore = new nodo;                            // Creo il secondo nodo
    testa->puntatore->inf = 2;                              // Assegno il valore 2
    testa->puntatore->puntatore = new nodo;                 // Creo il terzo nodo
    testa->puntatore->puntatore->inf = 3;                   // Assegno il valore 3
    testa->puntatore->puntatore->puntatore = NULL;          // Il terzo nodo punta a NULL, indicando la fine della lista

    stampalista(testa);                                     // Chiamata alla funzione per stampare la lista
    contaelementi(testa, 0);                                // Chiamata alla funzione per contare gli elementi
}