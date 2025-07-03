#include <iostream>
#include <fstream>
using namespace std;

#include "grafi.h"
#include "node.h"

//Stampa del grafo
void stampa(graph g) {
    for (int i=0; i<g.dim; i++) {
        cout << "Nodo " << i+1 << ": ";
        adj_list l = g.nodes[i];
        while (l != NULL) {
            cout << "("<< l->node + 1 <<") ";
            l = l->next;
        }
        cout << endl;
    }
}

void stampa_verbose(graph g, node* n) {
    for (int i = 0; i < g.dim; i++) {
        adj_list l = g.nodes[i];
        while (l != NULL) {
            char tipo_from = n[i].tipo;
            char tipo_to = n[l->node].tipo;
            string relazione;

            if (tipo_from == 'U' && tipo_to == 'T')
                relazione = "LIKE";
            else if (tipo_from == 'T' && tipo_to == 'U')
                relazione = "OWNER";
            else if (tipo_from == 'U' && tipo_to == 'U')
                relazione = "FOLLOW";
            else
                relazione = "UNKNOWN";

            cout << n[i].cont << " " << relazione << " " << n[l->node].cont << endl;
            l = l->next;
        }
    }
}

//Il numero torale del like dei tweet di un utente è il massimo rispetto a tutti gli utenti
int* totalLike(graph g, node* n) {
    int* V = new int[g.dim]{0};  // array con 0 iniziali
    // Per trovare il proprietario di ogni tweet
    // Creo un array tweet_owner[i] = indice utente proprietario del tweet i (o -1 se non tweet)
    int* tweet_owner = new int[g.dim];
    for (int i = 0; i < g.dim; i++) 
        tweet_owner[i] = -1;
    // 1) Trovo per ogni tweet il proprietario (arco T -> U di tipo OWNER)
    for (int i = 0; i < g.dim; i++) {
        if (n[i].tipo == 'T') {              // Se il nodo i è un tweet 
            adj_list l = g.nodes[i];         // Lista di adiacenza del tweet i
            bool trovato = false;
            while (l != NULL && !trovato) {  // Ciclo finché non trovo il proprietario, o finché non finisco la lista
                // Controllo se l'arco i -> l->node è di tipo OWNER (T -> U)
                int dest = l->node;
                if (n[dest].tipo == 'U') {   // Se il nodo di destinazione è un utente
                    tweet_owner[i] = dest;   // Assegno il proprietario del tweet
                    trovato = true;          // Segnalo che ho trovato il proprietario
                } else {
                    l = l->next;             // Altrimenti vado avanti nella lista
                }
            }
        }
    }

    // 2) Per ogni arco LIKE (U->T) incremento il contatore del proprietario del tweet
    for (int i = 0; i < g.dim; i++) {
        if (n[i].tipo == 'U') {                         // Se il nodo i è un utente
            // Scorro la lista di adiacenza dell'utente i
            adj_list l = g.nodes[i];                    
            while (l != NULL) {
                int dest = l->node;         
                // S arco i->dest è LIKE (U->T)
                if (n[dest].tipo == 'T') {
                    int owner = tweet_owner[dest];
                    if (owner != -1) {
                        V[owner]++;                     // Il proprietario del tweet riceve un like
                    }
                }
                l = l->next;
            }
        }
    }
    delete[] tweet_owner;
    return V;
}





int main () {
    ifstream file_graph("graph");
    if (!file_graph) {
        cerr << "Errore nell'apertura del file graph" << endl;
        return 1;
    }

    int n_nodi;
    file_graph >> n_nodi;
    graph g = new_graph(n_nodi);  // Creo il grafo con n nodi

    int u, v;
    while (file_graph >> u >> v) {
        add_arc(g, u, v, 0);  // Aggiungo archi orientati con peso 0
    }

    file_graph.close();
    stampa(g);  // Stampa del grafo
    cout << endl;

    //Uso il file node
    ifstream file_node("node");
    if (!file_node) {
        cerr << "Errore nell'apertura del file node" << endl;
        return 1;   
    }
    node* n = new node[n_nodi];     //Array dinamico di nodi di tipo node
    for (int i=0; i<n_nodi; i++) {
        file_node.getline(n[i].cont, 81);       // Legge tutta la riga del contenuto
        file_node >> n[i].tipo;                 // Legge il tipo (T o U)
        file_node.ignore();                     // Scarta il newline dopo il tipo
    }

    file_node.close();
    stampa_verbose(g, n);  // Stampa dettagliata del grafo con i nodi
    cout << endl;

    int* likes = totalLike(g, n);

    // Trovo massimo likes ricevuti
    int max_likes = 0;
    for (int i = 0; i < n_nodi; i++) {
        if (n[i].tipo == 'U' && likes[i] > max_likes)
            max_likes = likes[i];
    }

    // Stampo gli utenti con massimo like
    cout << "Most influential people (with " << max_likes << " likes):" << endl;
    for (int i = 0; i < n_nodi; i++) {
        if (n[i].tipo == 'U' && likes[i] == max_likes)
            cout << n[i].cont << endl;
    }

    delete[] likes;

}