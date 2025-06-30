#include <iostream>
#include <cstring>
using namespace std;

//Creazione di un binary tree --> il numero di figli per ogni nodo è al più 2

//Definizione della struttura dati albero binario
struct bnode {              //Definisco una struttura dati albero di tipo char
    char * inf;
    bnode * left;
    bnode * right;
    bnode * parent;
};
typedef char* tipo_inf;     //tipo_inf è un nuovo nome per il tipo di dati char*
struct bnode {              //Definisco una struttura dati albero di tipo tipo_inf
    tipo_inf inf;
    bnode * left;
    bnode * right;
    bnode * parent;
};
//Dichiarazione ddel tipo di dato binary tree
typedef bnode * btree;

//Primitive e funzioni per binary tree

//Primitiva per la creazione di un nuovo nodo di un albero binario con valore informativo i
bnode* new_node(tipo_inf i){
	bnode* n=new bnode;                 //Viene allocata dinamicamente la memoria per un nuovo nodo di tipo bnode utilizzando l'operatore new.
	copy(n->inf,i);                     //La funzione copy copia l'informazione di tipo tipo_inf dal parametro i al campo inf del nodo n
	n->left=n->right=n->parent=NULL;    //Inizializzo tutti i puntatori a NULL
	return n;                           //Il puntatore n al nuovo nodo appena creato e inizializzato viene restituito dalla funzione.
}

/*Se non è disponibile una funzione copy, è possibile riscrivere la funzione new_node in questo modo:
    bnode* new_node(tipo_inf i) {
        bnode* n = new bnode;                       // Creo un nuovo nodo di tipo bnode
        n->inf = i;                                 // Copio direttamente l'informazione 'i' nel campo 'inf' del nodo
        n->left = n->right = n->parent = NULL;      // Inizializzo i puntatori left, right e parent a NULL
        return n;                                   // Ritorno il puntatore al nuovo nodo appena creato e inizializzato
}
*/

//Primitiva che inserisce un nodo t come figlio sinistro del nodo p in un albero binario
void insert_left(btree p, btree t) {    //Prende come parametri il nodo genitore (p) e il nodo da inserire come figlio sinistro (t)
	p->left=t;                          //Assegna il nodo t come figlio sinistro del nodo p
	t->parent=p;                        //Imposta il nodo p come genitore del nodo t
}

//Primitiva che inserisce un nodo t come figlio destro del nodo p in un albero binario
void insert_right(btree p, btree t) {   //Prende come parametri il nodo genitore (p) e il nodo da inserire come figlio sinistro (t)
	p->right=t;                         //t diventa il figlio destro di p.
	t->parent=p;                        //Assegna il puntatore p al campo parent del nodo t, indicando che p è il genitore di t.
}

//Primitiva che restituisce il nodo genitore di un nodo specifico in un albero binario
bnode* get_parent(bnode* b){        //Prende in ingresso un puntatore a un nodo dell'albero binario
	return b->parent;               //Restituisce il puntatore al nodo genitore del nodo b. Se b non ha un genitore questo campo sarà NULL
}

//Primitiva che restituisce il figlio sinistro di un nodo specifico in un albero binario
bnode* get_left(bnode* b){      //Prende in ingresso un puntatore a un nodo dell'albero binario
	return b->left;             //Restituisce il puntatore al nodo figlio sinistro del nodo b. Se b non ha un figlio sinistro, questo campo sarà NULL.
}

//Primitiva che restituisce il figlio destro di un nodo specifico in un albero binario
bnode* get_right(bnode* b) {    //Prende in ingresso un puntatore a un nodo dell'albero binario
	return b->right;            //Restituisce il puntatore al nodo figlio destro del nodo b. Se b non ha un figlio destro, questo campo sarà NULL.
}

//Primitiva che restituisce il valore del campo informativo (inf) di un nodo specifico in un albero binario
tipo_inf get_info(bnode* b) {   //Prende in ingresso un puntatore a un nodo dell'albero binario
	return b->inf;              //Restituisce il valore del campo informativo inf del nodo b
}

//Funzione che confronta due stringhe di tipo tipo_inf utilizzando la funzione strcmp della libreria standard <cstring>
int compare(tipo_inf s1,tipo_inf s2) {      //Due parametri: s1 e s2 -> puntatori a stringhe di tipo tipo_inf
	return strcmp(s1,s2);                   //Restituisce 0 se le stringhe sono uguali, un valore negativo se la prima stringa precede in ordine alfabetico la seconda e un valore positivo nel caso contrario.
}

//Funzione che copia una stringa da un puntatore source a un puntatore dest, allocando dinamicamente la memoria necessaria per contenere la stringa copiata
void copy(tipo_inf& dest, tipo_inf source){     //Due parametri: dest (riferimento a un puntatore a char dove verrà copiata la stringa), source (puntatore a char, rappresenta la stringa da copiare)
	dest=new char[strlen(source)];              //Alloca dinamicamente un array di caratteri di lunghezza sufficiente per contenere la stringa source, inclusa la terminazione null (\0).
	strcpy(dest,source);                        //Copia il contenuto della stringa source nella memoria appena allocata puntata da dest
}

//Funzione che prende in ingresso un oggetto di tipo tipo_inf e stampa il suo contenuto
void print(tipo_inf inf){       //Prende in ingresso un puntatore di tipo tipo_inf che contiene l'informazione da stampare.
	cout<<inf;                  //Stampa del puntatore
}