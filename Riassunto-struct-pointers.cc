#include <iostream>
#include <string>

using namespace std;

// Definizione di una struct
struct Studente {
    string nome;
    int eta;
};

// Funzione che prende un puntatore a Studente
void stampaStudente(Studente* s) {
    cout << "Nome: " << s->nome << ", Eta: " << s->eta << endl;
}

int main() {
    // --- 1. Uso di struct normale ---
    Studente s1;
    s1.nome = "Anna";
    s1.eta = 22;
    stampaStudente(&s1); // Passaggio dell'indirizzo

    // --- 2. Puntatore a struct allocata dinamicamente ---
    Studente* s2 = new Studente; // Allocazione dinamica
    s2->nome = "Luca";
    s2->eta = 24;
    stampaStudente(s2);

    // Libera la memoria allocata dinamicamente
    delete s2;

    // --- 3. Puntatore normale e puntatore a puntatore ---
    int x = 10;
    int* p = &x;        // Puntatore a intero
    int** pp = &p;      // Puntatore a puntatore

    cout << "\nValore di x: " << x << endl;
    cout << "Valore tramite p: " << *p << endl;
    cout << "Valore tramite pp: " << **pp << endl;

    // --- 4. Array dinamico di Studente ---
    int n = 2;
    Studente* classe = new Studente[n]; // array dinamico

    classe[0].nome = "Marco";
    classe[0].eta = 21;

    classe[1].nome = "Giulia";
    classe[1].eta = 23;

    cout << "\nClasse:\n";
    for (int i = 0; i < n; i++) {
        stampaStudente(&classe[i]);
    }

    // Libera la memoria
    delete[] classe;

    return 0;
}