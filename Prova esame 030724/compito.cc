/**
 * @file compito.cc
 * @brief Main per il programma di gestione degli hotel
 *        Questo programma legge un file di hotel, li inserisce in un BST e permette di effettuare ricerche e operazioni su di essi.
 * @author Francesca 
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#include "bst.h"

/**
 * @brief Inserisce un nuovo hotel nel BST.
 * @param b Il BST in cui inserire l'hotel.
 * @param stelle Numero di stelle dell'hotel.
 * @param nome Nome dell'hotel.
 * @param luogo Luogo dell'hotel.
 * @details Crea un nodo di tipo `bnode` con le informazioni dell'hotel e lo inserisce nel BST.
 *          La chiave del nodo è basata sul numero di stelle.
 */
void inserisci_in_bst(bst& b, int stelle, const char* nome, const char* luogo) {
    tipo_inf i;
    i.stelle = stelle;
    strcpy(i.nome, nome);
    strcpy(i.luogo, luogo);
    tipo_key k = stelle;  

    bnode* nodo = bst_newNode(k, i);
    bst_insert(b, nodo);
}

/**
 * @brief Stampa gli hotel presenti nel BST in ordine decrescente di stelle.
 * @param b Il BST da cui stampare gli hotel.
 * @details Effettua una visita del BST e stampa le informazioni di ogni hotel.
 */
void stampa (bst b) {
    if (b != NULL) {
        stampa(b->left);
        cout << "Nome: " << b->inf.nome << ", Stelle: " << b->inf.stelle << ", Luogo: " << b->inf.luogo << endl;
        stampa(b->right);
    }
}

/**
 * @brief Ricerca e stampa gli hotel in base al numero di stelle.
 * @param t Il BST da cui effettuare la ricerca.
 * @param a Numero di stelle da confrontare.
 * @param b Booleano che indica se cercare hotel con stelle maggiori (true) o minori/uguali (false) a `a`.
 * @details Se `b` è true, stampa gli hotel con un numero di stelle maggiore di `a`, altrimenti stampa quelli con un numero di stelle minore o uguale a `a`.
 */
void ricerca (bst t, int a, bool b) {
    if (t == NULL) {
        return;
    }
    if (b) {
        // Stampa gli hotel con un numero di stelle maggiore di a
        if (t->inf.stelle > a) {
            cout << t->inf.stelle << " stelle " << t->inf.nome << " " << t->inf.luogo << endl;
        }
        ricerca(t->left, a, b);
        ricerca(t->right, a, b);
    } else {
        // Stampa gli hotel con un numero di stelle minore o uguale a a
        if (t->inf.stelle <= a) {
            cout << t->inf.stelle << " stelle " << t->inf.nome << " " << t->inf.luogo << endl;
        }
        ricerca(t->left, a, b);
        ricerca(t->right, a, b);
    }
}

/**
 * @brief Calcola il numero di hotel in un determinato luogo con un numero di stelle superiore a una soglia.
 * @param t Il BST da cui effettuare la ricerca.
 * @param a Soglia di stelle.
 * @param l Luogo in cui cercare gli hotel.
 * @return Il numero di hotel che soddisfano i criteri di ricerca.
 * @details Effettua una visita del BST e conta gli hotel che hanno un numero di stelle superiore a `a` e che si trovano nel luogo specificato da `l`.
 */
int media(bst t, int a, char* l) {
    if (t == NULL) {
        return 0;
    }
    int contatore = 0;
    if (strcmp(t->inf.luogo, l)==0 && t->inf.stelle > a)
        contatore++;
    return contatore + media(t->left, a, l) + media(t->right, a, l);
}

/**
 * @brief Funzione principale del programma.
 * @details Legge gli hotel da un file, li inserisce in un BST, e permette di effettuare ricerche e operazioni su di essi.
 *          Gestisce l'input dell'utente per le ricerche e stampa i risultati.
 */
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
