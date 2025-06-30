#include <iostream>
#include <fstream>
using namespace std;

#include "Strutture_dati.h"
#include "Strutture_dati.cc"

//Funzione per caricare i dati di un bst da un file
void load (bst& tree, const char* filename) {   //Prende in input un riferimento a un BST ( bst& tree) e il nome di un file ( const char* filename)
    ifstream fs(filename);                      //Utilizzare un oggetto ifstreamper aprire il file specificato dal nome
    if (fs) {                                   //Controllare che il file sia aperto correttamente. Se sì, procedere con l'elaborazione
        int dim;                                //Variabile intera per memorizzare il numero di nodi da leggere nel file
        bnode* node;                            //Puntatore a un nodo dell'albero BST
        tipo_key key;                           //Variabile per memorizzare la chiave del nodo
        tipo_inf inf;                           //Variabile per memorizzare le informazioni del nodo
        fs >> dim;                              //Legge il numero di nodi (dimensione dell'albero) dal file e lo memorizza nella variabile dim
        for (int i = 0; i < dim; i++) {         //Ciclo che ripete più dimvolte, cioè una volta per ogni nodo da leggere dal file
            node = NULL;                        //Imposta nodeNULL all'inizio di ogni iterazione    
            fs >> key;                          //Leggere la chiave del nodo dal file
            fs.ignore();                        //Ignora il carattere della nuova riga rimasto nel buffer dopo aver letto la chiave
            fs.getline(inf.nome, 20);           //Leggi le informazioni del nodo proveninenti dal file
            fs.getline(inf.luogo, 20);          // Leggere una riga di testo dal file e memorizzarla nel campo luogodella struttura inf
            node = bst_newNode(key, inf);       //Crea un nuovo nodo utilizzando la funzione bst_newNodepassando la chiave e le informazioni
            bst_insert(tree, node);             //Inserisce il nuovo nodo creato nell'albero BST utilizzando la funzione bst_insert     
        }
    }
}

//Funzione che stampa i nodi in ordine decrescente
void stampa_decrescente (bnode * node)
{
    if (node != NULL)
    {
        if (get_right(node))
            stampa_decrescente(get_right(node));
        cout<<get_key(node)<<get_value(node).nome<<get_value(node).luogo;
        if (get_left(node))
            stampa_decrescente(get_left(node));
    }
}