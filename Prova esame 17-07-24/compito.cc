/**
 * @file compito.cc
 * @author Francesca 
 * @brief Programma principale per gestire due giocatori di carte, confrontare le loro carte e verificare la presenza di tris.
 */

#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Struttura per rappresentare una carta con un valore e un seme.
 */
#include "liste.h"

/**
 * @brief Funzione che simula la pesca di una carta
 * @param c Lista di carte del giocatore
 * @param v Valore della carta pescata
 * @param s Seme della carta pescata
 * @details Questa funzione crea un nuovo elemento di tipo `elem`, inizializza i suoi campi con il valore e il seme della carta, e lo inserisce nella lista di carte del giocatore.
 * @note La funzione `insert_elem` è utilizzata per inserire il nuovo elemento nella lista.
 * @see insert_elem
 */
void pesca(lista& c, int v, char s) {
    elem* p = new elem;
    p->inf.seme = s;
    p->inf.valore = v;
	p->pun=p->prev=NULL;
    c = insert_elem(c, p);
}

/**
 * @brief Funzione per stampare il contenuto di una lista doppiamente collegata.
 * @param p Puntatore alla lista da stampare come argomento
 * @details Questa funzione itera attraverso la lista e stampa il valore e il seme di ogni carta presente nella lista.
 * @note La funzione `tail` è utilizzata per spostarsi al prossimo elemento della lista.
 * @see tail
 */
void stampa_lista(lista p) {
	while (p != NULL) {				                            //Finché non si arriva alla fine della lista
		cout<<p->inf.valore<<" " << p->inf.seme << endl ; 		//Stampa valore
		p = tail(p);     			                            //Spostamento sul prossimo elemento
	}
}

/**
 * @brief Funzione che stampa le due liste di carte a coppie nella stessa posizione e, per ogni coppia, il messaggio <carta prima lista> “è maggiore/minore/uguale a “ <carta seconda lista>
 * @param g1 Prima lista di carte
 * @param g2 Seconda lista di carte
 * @details Questa funzione confronta le carte di due giocatori e stampa un messaggio che indica se la carta del primo giocatore è maggiore, minore o uguale a quella del secondo giocatore.
 */
void stampa(lista g1, lista g2) {
    while (g1 != NULL && g2!= NULL) {
        compare(g1->inf, g2->inf);  // Confronta le due carte
        if (compare(g1->inf, g2->inf) > 0)
            cout << g1->inf.valore << g1->inf.seme << " è maggiore a " << g2->inf.valore << g2->inf.seme << endl;
        else if (compare(g1->inf, g2->inf) < 0)
            cout << g1->inf.valore << g1->inf.seme << " è minore a " << g2->inf.valore << g2->inf.seme << endl;
        else 
            cout << g1->inf.valore << g1->inf.seme << " è uguale a " << g2->inf.valore << g2->inf.seme << endl;
        g1 = tail(g1);  // Passa al prossimo elemento della prima lista
        g2 = tail(g2);  // Passa al prossimo elemento della seconda lista
    }
}

/**
 * @brief Funzione che verifica se ci sono tris nelle carte di un giocatore.
 * @param carte Lista di carte del giocatore
 * @return Un array di interi di dimensione 13, dove ogni elemento rappresenta se c'è un tris per quel valore (1-13).
 * @details Questa funzione conta quante carte ci sono per ogni valore da 1 a 13 e restituisce un array che indica se c'è un tris (almeno 3 carte dello stesso valore) per ciascun valore.
 */
int* tris(lista carte) {
    int contatori[13] = {0};  // Conta quante carte ci sono per ogni valore da 1 a 13
    int* risultato = new int[13]();  // Inizializza tutto a 0
    while (carte != NULL) {
        int v = carte->inf.valore;      // Ottiene il valore della carta -> assegna a v il valore della carta
        if (v >= 1 && v <= 13)          // Verifica che il valore sia tra 1 e 13
            contatori[v - 1]++;         // Incrementa il contatore per quel valore
        carte = tail(carte);            // Passa alla carta successiva
    }
    // Ora verifichiamo quali valori hanno almeno 3 carte (cioè un tris)
    for (int i = 0; i < 13; i++) {
        if (contatori[i] >= 3) {        // Se ci sono almeno 3 carte dello stesso valore
            risultato[i] = 1;           // Segna che c'è un tris per quel valore
        }
    }
    return risultato;
}

/**
 * @brief Funzione che calcola il punteggio di un tris e lo rimuove dalla lista di carte.
 * @param carte Lista di carte del giocatore
 * @return Il punteggio del tris calato (somma dei valori delle 3 carte del tris).
 * @details Questa funzione cerca un tris nella lista di carte, lo stampa, lo rimuove dalla lista e restituisce il punteggio del tris. Se non trova un tris, restituisce 0.
 */
int cala(lista& carte) {
    int contatori[13] = {0};      // Array per contare quante carte ci sono per ogni valore da 1 a 13
    lista p = carte;              // Puntatore ausiliario per scorrere la lista senza modificarla
    // PRIMA PASSATA: conta le carte per valore
    while (p != NULL) {
        contatori[p->inf.valore - 1]++;   // Incrementa il contatore per il valore della carta corrente (es. valore 3 → indice 2)
        p = tail(p);                      // Passa alla carta successiva
    }
    // CERCA UN TRIS: un valore che compare almeno 3 volte
    int valoreTris = -1;                  // Inizialmente nessun tris trovato
    for (int i = 0; i < 13; i++) {
        if (contatori[i] >= 3) {          // Se ci sono almeno 3 carte dello stesso valore
            valoreTris = i + 1;           // Salva il valore del tris trovato (ricorda: indice 0 → valore 1)
            break;                        // Si ferma al primo tris trovato
        }
    }
    if (valoreTris == -1)
        return 0;                         // Se nessun tris trovato, restituisce punteggio 0
    // SECONDA PASSATA: rimuove le prime 3 carte con quel valore
    int trovate = 0;                      // Conta quante carte del tris sono state trovate finora
    lista current = carte;                // Puntatore per scorrere di nuovo la lista
    int punteggio = 0;                    // Variabile per sommare il punteggio del tris
    cout << "Calo tris: ";                // Messaggio per mostrare il tris calato
    while (current != NULL && trovate < 3) {
        if (current->inf.valore == valoreTris) {
            // Se la carta corrente ha il valore giusto, è parte del tris
            cout << current->inf.valore << current->inf.seme << " ";  // Stampa la carta
            lista daRimuovere = current;     // Segna la carta da rimuovere
            current = tail(current);         // Sposta il puntatore prima di rimuovere la carta (per non invalidare la lista)
            carte = delete_elem(carte, daRimuovere);  // Rimuove la carta dalla lista del giocatore
            trovate++;                       // Incrementa il numero di carte del tris trovate
            punteggio += valoreTris;         // Aggiunge il valore della carta al punteggio
        } else {
            current = tail(current);         // Passa alla prossima carta se non è parte del tris
        }
    }
    cout << endl;   // Fine stampa tris
    return punteggio;  // Restituisce il punteggio ottenuto con il tris
}

/**
 * @brief Funzione principale del programma.
 * @details Questa funzione carica i dati dei due giocatori da file, crea le liste di carte, stampa le carte e verifica la presenza di tris per ciascun giocatore.
 * @return 0 se il programma termina correttamente.
 * @note I file "g1.txt" e "g2.txt" devono essere presenti nella stessa directory del programma e devono contenere i dati delle carte dei due giocatori.
 */

int main () {
    lista giocatore1 = NULL;
    lista giocatore2 = NULL;

    //Caricamento dei dati dal primo file
    ifstream file1("g1.txt");

    for (int i=0; i<12; i++) {
        int v;
        char s;
        file1 >> v;     //Prende la riga i, il valore a sx lo mette in v
        //file1.ignore();
        file1 >> s;     //Prende la riga i, il valore a dx lo mette in s
        pesca(giocatore1, v, s);
    }
    file1.close();

    //Caricamento dei dati dal secondo file
    ifstream file2("g2.txt");

    for (int i=0; i<12; i++) {
        int v;
        char s;
        file2 >> v;
        file2.ignore();
        file2 >> s;
        pesca(giocatore2, v, s);
    }
    file2.close();

    //Effettuo la stampa per confrontare i due giocatori
    stampa(giocatore1, giocatore2);

    //Tris di giocatore 1
    int* t1 = tris(giocatore1);
    cout << "Tris del giocatore 1: ";
    for (int i = 0; i < 13; i++) {
        cout << t1[i] << " ";
    }
    cout << endl;
    delete[] t1;
    //Tris di giocatore 2
    int* t2 = tris(giocatore2);
    cout << "Tris del giocatore 2: ";
    for (int i = 0; i < 13; i++) {
        cout << t2[i] << " ";
    }
    cout << endl;
    delete[] t2;

    //Cala
    int punti1 = 0, punti2 = 0; // Inizializza i punteggi dei due giocatori a 0
    // === TURNO DEL GIOCATORE 1 ===
    cout << "\n--- Turno giocatore 1 ---" << endl;
    int v;   // Variabile per il valore della carta pescata
    char s;  // Variabile per il seme della carta pescata
    // Pesca una carta da tastiera
    cout << "Giocatore 1, pesca una carta (valore e seme): ";
    cin >> v >> s;
    pesca(giocatore1, v, s); // Inserisce la carta pescata nella lista del giocatore 1
    // Finché ci sono tris nella mano, calali uno alla volta
    while (true) {
        int punti = cala(giocatore1); // Cerca un tris, lo rimuove, e ritorna il punteggio
        if (punti == 0) break;        // Se non ci sono tris, esce dal ciclo
        punti1 += punti;              // Aggiunge il punteggio del tris al totale
    }
    // Se il giocatore 1 non ha più carte, stampa "Fine gioco"
    if (giocatore1 == NULL)
        cout << "Fine gioco per giocatore 1" << endl;


    // === TURNO DEL GIOCATORE 2 ===
    cout << "\n--- Turno giocatore 2 ---" << endl;
    // Pesca una carta da tastiera
    cout << "Giocatore 2, pesca una carta (valore e seme): ";
    cin >> v >> s;
    pesca(giocatore2, v, s); // Inserisce la carta nella lista del giocatore 2
    // Finché ci sono tris nella mano, calali uno alla volta
    while (true) {
        int punti = cala(giocatore2); // Cerca e cala un tris
        if (punti == 0) break;        // Esce se non ci sono più tris
        punti2 += punti;              // Somma il punteggio ottenuto
    }
    // Se il giocatore 2 non ha più carte, stampa "Fine gioco"
    if (giocatore2 == NULL)
        cout << "Fine gioco per giocatore 2" << endl;
    // === STAMPA FINALE DEL PUNTEGGIO E VINCITORE ===
    cout << "\nPunteggio giocatore 1: " << punti1 << endl;
    cout << "Punteggio giocatore 2: " << punti2 << endl;

    // Determina chi ha vinto in base al punteggio
    if (punti1 > punti2)
        cout << "Vince il giocatore 1!" << endl;
    else if (punti2 > punti1)
        cout << "Vince il giocatore 2!" << endl;
    else
        cout << "Pareggio!" << endl;

    // Libera la memoria allocata per le liste
    while (giocatore1 != NULL) {     // Il ciclo continua fino a quando testa non è NULL
        elem* daEliminare = giocatore1; // Salva il puntatore all'elemento da eliminare
        giocatore1 = tail(giocatore1); // Sposta il puntatore alla testa della lista
        delete daEliminare; // Dealloca la memoria dell'elemento corrente
    }
    while (giocatore2 != NULL) {     // Il ciclo continua fino a quando testa non è NULL
        elem* daEliminare = giocatore2; // Salva il puntatore all'elemento da eliminare
        giocatore2 = tail(giocatore2); // Sposta il puntatore alla testa della lista
        delete daEliminare; // Dealloca la memoria dell'elemento corrente
    }
    return 0; // Termina il programma con successo
}