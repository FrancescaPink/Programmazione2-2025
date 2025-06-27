#include<iostream>
using namespace std;

//Definizione di una struttura chiamata elem che rappresenta un elemento di una lista
struct elem {
    int inf;                //Elemento della lista (campo informativo)
    elem * pun;             //Puntatore che punta al prossimo elemento della lista
};
//Dichiarazione della testa della lista
typedef elem* lista;                //Utilizza la parola chiave typedef per definire un nuovo tipo chiamato lista. 
lista testa;                        //Il tipo lista è sinonimo di elem*, cioè un puntatore a un oggetto di tipo elem.

//Primitive

//Primitiva testa: accesso alla testa della lista
int head(lista l){
    return l->inf;                  //Ritorna il valore informativo del primo elemento della lista.
}

//Primitiva testa: accesso alla coda della lista
lista tail(lista l){
    return l->pun;                  //Ritorna il puntatore al prossimo elemento della lista.
}

//Primitiva per l'inserimento di un valore in testa alla lista. Inserimento in testa: nuovo dato composto dall'informazione e un puntatore provenienti dal main
lista insert_elem(lista l, elem * e){       //Inserisce un elemento e in testa alla lista l e ritorna il nuovo puntatore alla testa.
    e->pun=l;               //Collega il nuovo elemento e al primo elemento della lista esistente, rendendolo il nuovo primo elemento                
    return e;               //Lista aggiornata: ritorna il puntatore al nuovo elemento e, che ora è la nuova testa della lista.
}

//Primitiva per l'eliminazione di un elemento della lista
lista delete_elem(lista l, elem* e){    //Elimina l'elemento e dalla lista l e ritorna la nuova testa della lista.
    if (l==e){                          //Se l'elemento da eliminare è in testa (il primo della lista)        
        l=tail(l);                      //Eliminazione dell'elemento in testa spostando la lista con tail   
    }
    else{
        lista l1=l;                     //Creazione di una lista d'appoggio che inizia dalla testa della lista
        while (tail(l1)!=e){            //Controllo fino a quando trovo l'elemento da eliminare
            l1=tail(l1);                //Spostamento della lista per escludere l'elemento da eliminare
        }
        l1->pun=tail(e);                //aggiorna il campo pun di questo elemento per puntare al successivo elemento di e (tail(e)).
    }
    delete e;                           //Eliminazione dell'elemento - deallocazione della memoria
    return l;                           //Ritorno della nuova testa della lista
}

//Primitiva per la ricerca di un elemento nella lista
elem* search(lista l, int v) {  //La funzione prende: un puntatore alla testa della lista (lista l) e il valore da cercare (int v).
	while(l!=NULL){             //Ricerca di un elemento nella lista fino a quando ci sono elementi da controllare
		if(head(l)==v){         //Utilizza la funzione head(l) per ottenere il valore del campo informativo del nodo corrente
			return l;           //Se il valore del nodo corrente è uguale a v, la funzione restituisce il puntatore all'elemento trovato
        }
		else{
			l=tail(l);          //Il puntatore l viene aggiornato per puntare al nodo successivo utilizzando la funzione tail(l)
        }
    }
	return NULL;                //Se l'elemento non si trova nella lista ritorna NULL
}

//Copia della lista originale in uno nuova lista
lista copy(lista l1){           //La funzione prende un parametro lista l1: un puntatore alla testa della lista originale.
    lista l=NULL;               //Si inizializza la nuova lista a NULL, l è un puntatore alla testa della nuova lista
    elem* curr;                 //Puntatore al nodo corrente, che verrà creato nella nuova lista
    elem* prev=NULL;            //Puntatore al nodo precedente nella nuova lista, inizialmente impostato a NULL.
    while(l1!=NULL){            //Fichè l1 non è NULL, cioè fino a quando ci sono elementi nella lista originale da copiare:
        curr = new elem ;       //Creazione del nuovo nodo
        curr->inf = head(l1);   //Il nuovo nodo prende l'informazione dalla lista iniziale
        curr->pun=NULL;         //Il campo pun del nuovo nodo è impostato a NULL, poiché al momento non conosciamo il prossimo nodo.
        if(prev==NULL){         //Se è NULL sto creando la testa della nuova lista
            l=curr;             //Imposto l (la testa della nuova lista) a curr
        }
        else{
            prev->pun=curr;     //Se prev non è NULL, colleghiamo il nodo precedente (prev) al nuovo nodo (curr).
        }
        prev=curr;              //Aggiorno prev per puntare al nuovo nodo, cosicchè nel prossimo ciclo questo nodo diventi il precedente.
        l1=tail(l1);            //Aggiorniamo l1 per puntare al prossimo nodo della lista originale.
    }
    return l;                   //Ritorno della nuova lista             
}

//Funzioni

//Funzione per la stampa di tutti gli elementi della lista
void stampa_lista(lista p){         //La funzione prende un parametro lista p: un puntatore alla testa della lista
    while (p != NULL) {             //Finché p non diventa NULL, cioè finché non si esauriscono gli elementi della lista:
        cout << head(p) << " " ;    //Stampa il valore del campo informativo del nodo corrente utilizzando la funzione head(p)
        p = tail(p);                //Aggiorna p per puntare al prossimo nodo della lista utilizzando la funzione tail(p).
    }
    cout << endl ;
}

//Funzione per la creazione della lista
lista crea_lista(int num){              //Prende come parametro il numero di elementi che l'utente desidera inserire nella lista
    lista testa = NULL;                 //Inizializza la lista come vuota
    for(int i=0 ; i<num ; i++){
        elem * p = new elem;            //Viene creato dinamicamente un nuovo nodo della lista utilizzando l'operatore new.
        int n;
        cout<<"Inserisci un numero: ";
        cin>>n;
        p->inf = n;                     //Il campo informativo (inf) del nodo p viene impostato con il valore inserito dall'utente
        testa=insert_elem(testa,p);     //Chiamata per l'inserimento nella lista
    }
    return testa;                       //Restituisce la testa della lista completa, che contiene tutti i nodi inseriti dall'utente.
}

//Funzione per eliminare l'intera lista
void elimina_lista(lista& testa){           //Prende un riferimento (&) a un puntatore che punta alla testa della lista.
     while (testa != NULL){                 //Finchè la lista non è vuota
           testa=delete_elem(testa,testa);  //Chiamata per l'eliminazione dell'elemento tramite la funzione delete_elem
     }
}

//Funzione di un esercizio per la creazione di una lista di due elementi a tempo di scrittura
void due_elementi() { 
    lista testa = new elem;     //Creazione dinamica del primo nodo della lista
    testa->inf = 3;             //Assegnazione del primo numero (3) al campo informativo del primo nodo
    lista p = new elem;         //Creazione del secondo nodo della lista            
    p->inf = 7;                 //Assegnazione del secondo numero (7) al campo informativo del secondo nodo
    p->pun = NULL;              //Impostazione del puntatore al prossimo nodo a NULL (terminatore di lista)
    testa->pun = p;             //Collegamento tra il primo nodo e il secondo nodo della lista
    stampa_lista(testa);        //Chiamata alla funzione per stampare la lista
}

// Funzione che conta le occorrenze di un valore nella lista
int conta(lista l, int v){              //La funzione prende: un puntatore alla testa della lista (lista l) e il valore da cercare (int v).
    int occ = 0;                        //Contatore del numero di occorrenze inizializzato a zero
    while((l=search(l,v))!=NULL){       //Finchè viene trovato il valore:
        l=tail(l);                      //l viene aggiornato al nodo successivo della lista.
        occ++;                          //Incremento
    }
    return occ;                         //Ritorno delle occorrenze
}

// Funzione che cancella dalla lista tutte le occorrenze che si trovanno al suo interno di un determinato valore
lista cancella(lista l, int v){         //La funzione prende: un puntatore alla testa della lista (lista l) e il valore da cancellare (int v).
    elem* e;                            //Definizione di un puntatore a un elemento della lista utile per trovare le occorrenze da eliminare
    while((e=search(l,v))!=NULL){       //Trovo il valore e lo assegno al nuovo elemento, finchè questo non è nullo:
        l=delete_elem(l,e);             //Cancello l'elemento dalla lista tramite la funzione delete_elem
    }
    return l;                           //Ritorno la nuova lista
}

//Main

int main() {
    lista testa = NULL;     //Testa della lista inizialmente vuota
    int scelta;             //Variabile per memorizzare la scelta dell'utente
    int num;                //Variabile per memorizzare il numero di elementi da inserire
    do {                    //Menu delle operazioni
        cout << "\nMenu di scelta:" << endl;
        cout << "1. Inserisci elementi nella lista" << endl;
        cout << "2. Stampare la lista" << endl;
        cout << "3. Copia della lista" << endl;
        cout << "4. Conta le occorrenze di un valore" << endl;
        cout << "5. Cancella tutte le occorrenze di un valore" << endl;
        cout << "6. Elimina l'intera lista" << endl;
        cout << "7. Creazione di una lista di due elementi" << endl;
        cout << "0. Esci" << endl;
        cout << "Scelta: ";
        cin >> scelta;
        switch (scelta) {
            case 1:
                cout << "Quanti elementi vuoi inserire? ";
                cin >> num;
                testa = crea_lista(num);
                break;
            case 2:
                cout << "Lista: ";
                stampa_lista(testa);
                break;
            case 3:
                lista copia;
                copia = copy(testa);
                cout << "Copia della lista: ";
                stampa_lista(copia);
                break;
            case 4:
                int valore;
                cout << "Inserisci il valore da contare: ";
                cin >> valore;
                cout << "Numero di occorrenze di " << valore << ": " << conta(testa, valore) << endl;
                stampa_lista(testa);
                break;
            case 5:
                int valore_da_cancellare;
                cout << "Inserisci il valore da cancellare: ";
                cin >> valore_da_cancellare;
                testa = cancella(testa, valore_da_cancellare);
                cout << "Lista dopo la cancellazione di tutte le occorrenze di " << valore_da_cancellare << ": ";
                stampa_lista(testa);
                break;
            case 6:
                elimina_lista(testa);
                cout << "Lista eliminata." << endl;
                break;
            case 7:
                due_elementi();
                break;
            case 0:
                cout << "Uscita dal programma." << endl;
                break;
            default:
                cout << "Scelta non valida. Riprova." << endl;
                break;
        }
    } 
    while (scelta != 0);
    return 0;
}