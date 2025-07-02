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

//Punto 2a -> dato un bst e un numero a di stelle, stampo tutti gli hotel con un numero di stelle maggiore di a se b è true, altrimenti stampo tutti gli hotel con un numero di stelle minore o uguale a a
void ricerca (bst t, int a, bool b) {
    if (t == NULL) {
        return;
    }
    if (b) {
        // Stampa gli hotel con un numero di stelle maggiore di a
        if (t->inf.stelle > a) {
            cout << "Nome: " << t->inf.nome << ", Stelle: " << t->inf.stelle << ", Luogo: " << t->inf.luogo << endl;
        }
        ricerca(t->left, a, b);
        ricerca(t->right, a, b);
    } else {
        // Stampa gli hotel con un numero di stelle minore o uguale a a
        if (t->inf.stelle <= a) {
            cout << "Nome: " << t->inf.nome << ", Stelle: " << t->inf.stelle << ", Luogo: " << t->inf.luogo << endl;
        }
        ricerca(t->left, a, b);
        ricerca(t->right, a, b);
    }
}

//Punto 2b -> dato in  in input un bst e un numero di stelle “soglia” e un luogo, restituisca il numero di hotel nel luogo specificato 
//            con un numero di stelle superiore alla soglia. 
int media(bst t, int a, char* l) {
    if (t == NULL) {
        return 0;
    }
    int contatore = 0;
    if (strcmp(t->inf.luogo, l)==0 && t->inf.stelle > a)
        contatore++;
    return contatore + media(t->left, a, l) + media(t->right, a, l);
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
    cout << endl;

    //Punto 2a
    int numero_stelle;
    cout << "Inserisci il numero di stelle: ";
    cin >> numero_stelle;
    bool ctrl;
    cout << "Inserisci 1 se vuoi stampare gli hotel con un numero di stelle maggiore di " << numero_stelle << ", altrimenti inserisci 0: ";
    cin >> ctrl;
    ricerca(b, numero_stelle, ctrl);
    cout << endl;

    //Punto 2b
    int soglia;
    char luogo_ricerca[20];
    cout << "Inserisci la soglia di stelle: ";
    cin >> soglia;
    cout << "Inserisci il luogo: ";
    cin >> luogo_ricerca;
    int hotel_restituiti = media(b, soglia, luogo_ricerca);
    cout << "Valore soglia: " << soglia << "\tLuogo: " << luogo_ricerca << endl;
    cout << "Hotel restituiti: " << hotel_restituiti << endl;

    return 0;
}
