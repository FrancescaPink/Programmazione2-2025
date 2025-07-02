#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#include "bst.h"

void inserisci_in_bst(bst& b, int stelle, const char* nome, const char* luogo) {
    tipo_inf i;
    i.stelle = stelle;
    strcpy(i.nome, nome);
    strcpy(i.luogo, luogo);
    tipo_key k = stelle;  // oppure qualche altro criterio per la chiave

    bnode* nodo = bst_newNode(k, i);
    bst_insert(b, nodo);
}


void stampa (bst b) {
    if (b != NULL) {
        stampa(b->left);
        cout << "Nome: " << b->inf.nome << ", Stelle: " << b->inf.stelle << ", Luogo: " << b->inf.luogo << endl;
        stampa(b->right);
    }
}


int main () {
    ifstream file("hotel.txt");
    if (!file) {
        cerr << "Errore nell'apertura del file hotel.txt" << endl;
        return 1;
    }

    int numero_elementi;
    file >> numero_elementi;

    bst b = NULL;
    int stelle;
    char nome[20];
    char luogo[20];

    for (int i=0; i<numero_elementi; i++) {
        file >> stelle;
        file.ignore(); // per consumare il newline dopo il numero
        file.getline(nome, 50);
        file.getline(luogo, 50);
        inserisci_in_bst(b, stelle, nome, luogo);
    }

    stampa(b);

    return 0;
}
