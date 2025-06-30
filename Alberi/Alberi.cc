#include <iostream>
#include <cstring>
using namespace std;

//Definisco una struttura dati albero di tipo char
struct node {
    char * inf;             //Contiene l'informazione (o valore) del nodo, di tipo intero.
    node * parent;          //Puntatore al nodo genitore (padre) del nodo corrente --> Opzionale
    node * firstChild;      //Puntatore al primo figlio del nodo corrente
    node * nextSibling;     //Puntatore al prossimo fratello del nodo corrente
};

//Dichiaro un nuovo tipo tipo_inf
typedef char* tipo_inf;     //tipo_inf è un nuovo nome per il tipo di dati char*.
//Dopo questa dichiarazione, ogni volta che si utilizza tipo_inf nel codice, è come se si stesse utilizzando char*

//Struct node e il tipo di dato tree con l'utilizzo di un tipo tipo_inf
struct node {
    tipo_inf inf;           //Contiene l'informazione (o valore) del nodo, di tipo intero.
    node * parent;          //Puntatore al nodo genitore (padre) del nodo corrente --> Opzionale
    node * firstChild;      //Puntatore al primo figlio del nodo corrente
    node * nextSibling;     //Puntatore al prossimo fratello del nodo corrente
};
typedef node * tree;    //Definisce tree come un puntatore a node, quindi tree è equivalente a node * (punta alla radice dell'albero)
tree root;              //Variabile root di tipo tree, che è un puntatore a un nodo (node *). Viene utilizzato per rappresentare il nodo radice dell'albero.

//Primitive per la creazione di alberi - ALCUNE PRIMITIVE USANO DELLE FUNZIONI SCRITTE IN BASSO!

//Primitiva per la creazione di un nuovo nodo con valore informativo i
node* new_node (tipo_inf i) {       //Riceve una stringa (un puntatore a char) che rappresenta l'informazione da memorizzare nel nuovo nodo.
    node* n=new node;               //Crea dinamicamente un nuovo nodo e assegna il puntatore a n.
	copy(n->inf,i);                 //Utilizza la funzione copy (definita in basso) per copiare la stringa i nel campo inf del nodo n.
	n->nextSibling=n->firstChild=n->parent=NULL;        //Imposto tutti i puntatori a NULL
	return n;                       //Restituisce il puntatore al nuovo nodo.
}

/* Senza utilizzare la funzione copy, è possibile ottenere lo stesso risultato nel seguente modo:
    node* new_node(tipo_inf i) {
        node* n = new node;
        //Allocare memoria per inf e copiare la stringa i
        n->inf = new char[strlen(i) + 1];       //+1 per il terminatore null
        strcpy(n->inf, i);
        //Imposto a NULL tutti i puntatori
        n->nextSibling = nullptr;
        n->firstChild = nullptr;
        n->parent = nullptr;
        return n;
    }
*/

//Primitiva per l'inserimento di un sottoalbero radicato in c come primo figlio di p
void insert_child (tree p, tree c) {        //p -> puntatore al nodo genitore, c -> puntatore al nodo figlio che deve essere inserito.
	c->nextSibling=p->firstChild;           //Il nextSibling di c punta al primo figlio attuale di p: il nodo c diventa il primo figlio di p, e l'attuale primo figlio di p diventa il prossimo fratello di c.
	c->parent=p;                            //Imposta il parent di c per puntare a p, indicando che p è il genitore di c.
	p->firstChild=c;                        //Imposta firstChild di p per puntare a c, indicando che c è ora il primo figlio di p.
}

/* PASSAGGI DELLA FUNZIONE insert_child (3 linee di funzione - 3 passaggi corrispondenti a ogni linea):
    1. Collegamento del prossimo fratello del nuovo figlio
    2. Collegamento del genitore del nuovo figlio
    3. Aggiornamento del primo figlio del genitore
*/

//Primitiva per l'inserimento di un sottoalbero radicato in t come fratello successivo di n
void insert_sibling (node* n, tree t) {     //n -> puntatore al nodo corrente, il cui prossimo fratello sarà aggiornato, t -> puntatore al nodo che deve essere inserito come prossimo fratello.
    t->nextSibling=n->nextSibling;          //Imposta il nextSibling di t per puntare al nextSibling attuale di n: il nuovo nodo t punta al fratello che seguiva n
	t->parent=n->parent;                    //Imposta il parent di t per puntare allo stesso genitore di n, indicando che t è un fratello di n.
	n->nextSibling=t;                       //Imposta nextSibling di n per puntare a t, inserendo così t come prossimo fratello di n.
}

/* PASSAGGI DELLA FUNZIONE insert_sibling (3 linee di funzione - 3 passaggi corrispondenti a ogni linea):
    1. Collegamento del prossimo fratello del nuovo nodo
    2. Collegamento del genitore del nuovo nodo
    3. Aggiornamento del prossimo fratello del nodo corrente
*/

//Primitive per l'accesso a alberi

//Primitiva per restituire il contenuto informativo del nodo n
tipo_inf get_info (node * n) {      //Prende in ingresso il puntatore al nodo da cui ottenere l'informazione.
	return n->inf;                  //Restituisce il valore contenuto nel campo inf del nodo n.
}

//Primitiva per restituire il padre del nodo n
node * get_parent (node * n) {      //Prende in ingresso il puntatore al nodo di cui si vuole ottenere il genitore.
	return n->parent;               //Restituisce il valore del campo parent del nodo n, che è un puntatore al nodo genitore di n
}

//Primitiva per restituire il primo figlio del nodo n se esiste
node * get_firstChild (node * n) {      //Prende in ingresso il puntatore al nodo di cui si vuole ottenere il primo figlio.
	return n->firstChild;               //Restituisce il valore del campo firstChild del nodo n, che è un puntatore al primo figlio di n
}

//Primitiva per restituire il fratello successivo del nodo n se esiste
node * get_nextSibling (node * n) {     //Prende in ingresso il puntatore al nodo di cui si vuole ottenere il fratello successivo.
	return n->nextSibling;              //Restituisce il valore del campo nextSibling del nodo n, che è un puntatore al fratello successivo di n
}

//Funzioni essenziali - alcue funzioni sono presenti in alcune primitive

//Funzione che confronta due stringhe di tipo tipo_inf utilizzando la funzione strcmp della libreria standard <cstring>
int compare(tipo_inf s1,tipo_inf s2){       //Due parametri: s1 e s2 -> puntatori a stringhe di tipo tipo_inf
	return strcmp(s1,s2);                   //Restituisce 0 se le stringhe sono uguali, un valore negativo se la prima stringa precede in ordine alfabetico la seconda e un valore positivo nel caso contrario.
}

//Funzione che copia una stringa dalla sorgente (source) alla destinazione (dest).
void copy(tipo_inf& dest, tipo_inf source){     //Due parametri: dest (riferimento a un puntatore a char dove verrà copiata la stringa), source (puntatore a char, rappresenta la stringa da copiare)
	dest=new char[strlen(source)];              //Alloca dinamicamente un array di caratteri di lunghezza sufficiente per contenere la stringa source, inclusa la terminazione null (\0).
	strcpy(dest,source);                        //Copia il contenuto della stringa source nella memoria appena allocata puntata da dest
}

//Funzione che stampa il contenuto di una stringa di tipo tipo_inf
void print(tipo_inf inf){       //Prende in ingresso un puntatore di tipo tipo_inf che contiene l'informazione da stampare.
	cout<<inf;                  //Stampa del puntatore
}

//Visite di alberi

//Visita DFS -> visita dei nodi dalla radice alle foglie

//Visita DFS ricorsiva: serializzazione di un albero --> la tipologia di visita è in preordine e la visita del nodo consiste nella stampa dell'apertura di parentesi e del contenuto del nodo
void serialize(tree t) {
    cout<<"(";                      //Stampa un carattere "(" per indicare l'inizio della serializzazione di un sottoalbero.
    print(get_info(t));             //Chiama la funzione get_info(t) per ottenere le informazioni memorizzate nel nodo t e usa print per stamparle
    tree t1 = get_firstChild(t);    //Ottiene il puntatore al primo figlio del nodo t.
    while(t1!=NULL) {               //fFinchè t1 non è NULL (ci sono ancora figli da visitare):
        serialize(t1);              //Richiama ricorsivamente la funzione serialize per serializzare il sottoalbero radicato in t1.
        t1 = get_nextSibling(t1);   //Ottiene il puntatore al fratello successivo di t1 per continuare con l'elaborazione degli altri figli del nodo t.
    }
    cout<<")";                      //Stampa un carattere ")" per indicare la fine della serializzazione del sottoalbero radicato in t
}

//Visita BFS -> visita dei nodi per livelli, a partire dal livello 0 della radice

//Visita BFS iterativa: fa uso di una CODA dove vengono gestiti i nodi aperti. 

//Realizzazione di un modulo "coda-bfs" che implementa una coda di nodi dell'albero
struct elemBFS
{
       node* inf;           //Puntatore al nodo dell'albero.
       elemBFS* pun ;       //Puntatore al prossimo elemento della coda
};

typedef elemBFS* lista;     //Definisce lista come un puntatore a elemBFS, che è utilizzato per rappresentare un elemento di una lista (in questo caso, una lista collegata per la coda BFS).

typedef struct{
	lista head;             //Puntatore al primo elemento della coda (testa della lista)
	elemBFS* tail;          //Puntatore all'ultimo elemento della coda (coda della lista)
} codaBFS;

//Primitive del modulo coda-bfs

//Primitiva per aggiungere un nodo (node* i) alla fine di una coda BFS (codaBFS).
codaBFS enqueue(codaBFS c, node* i){    //Prende: la coda BFS passata come un'istanza della struttura codaBFS, il nodo da aggiungere passato come un puntatore a node.
	elemBFS *e=new_elem(i);     //Crea un nuovo elemento elemBFS con il nodo i passato come argomento
	if(c.tail!=NULL)            //Se la coda non è vuota (c.tail non è NULL):
			c.tail->pun=e;      //Collega il puntatore pun dell'ultimo elemento della coda (c.tail) al nuovo elemento e, aggiungendo e alla fine della lista
	c.tail=e;                   //Aggiorna il puntatore tail della coda con il nuovo elemento e, indicando che e è ora l'ultimo elemento della coda
	if(c.head==NULL)            //Se la testa della coda (head) è NULL (cioè la coda era vuota prima dell'inserimento di e):
		c.head=c.tail;          //Imposta sia la testa che la coda a e, poiché ora è l'unico elemento nella coda
	return c;                   //Restituisce la coda aggiornata dopo l'inserimento del nuovo elemento e.
}

//Primitiva per rimuovere e restituire il nodo dalla testa di una coda BFS (codaBFS)
node* dequeue(codaBFS& c){      //Prende in ingresso un riferimento a una struttura di tipo codaBFS: la funzione dequeue modifica direttamente la struttura della coda, aggiornando i puntatori head e tail
	node* ris=(c.head)->inf;    //Accedi al nodo (inf) memorizzato nell'elemento in testa alla coda e assegnalo a ris
	c.head=(c.head)->pun;       //Aggiorna il puntatore head della coda per puntare al prossimo elemento nella lista: la testa della coda si sposta in avanti di un elemento.
	return ris;                 //Restituisce il nodo che era in testa alla coda.
};

//Primitiva per restituire il nodo (node*) in testa alla coda BFS (codaBFS) senza rimuoverlo
node* first(codaBFS c){         //Prende come parametro un'istanza della coda BFS
	return (c.head)->inf;       //Accede al nodo (inf) memorizzato nel primo elemento della coda e lo restituisce.
};

//Primitiva per verificare se una coda BFS è vuota
bool isEmpty(codaBFS c){        //Prende come parametro un'istanza della coda BFS
	if(c.head==NULL)            //Se la testa della coda è NULL (se la coda è vuota):
		return true;            //Restituisce true se la testa della coda è NULL, false altrimenti
	return false;
}

//Primitiva che crea e restituisce una nuova coda BFS vuota
codaBFS newQueue(){
	codaBFS c={NULL, NULL};         //Crea una nuova variabile c di tipo codaBFS e inizializza sia head che tail a NULL.
	return c;                       //Restituisce la nuova coda BFS vuota.
}

//Primitiva che crea un nuovo elemento di tipo elemBFS con un nodo specificato e lo inizializza
static elemBFS* new_elem(node* n) { //Prende in ingresso un puntatore a un nodo (node* n)
	elemBFS* p = new elemBFS ;      //Alloca dinamicamente un nuovo elemento elemBFS e assegna il puntatore p a questo nuovo elemento
    p->inf=n;                       //Assegna al campo inf del nuovo elemento il nodo n passato come parametro.
    p->pun=NULL;                    // Inizializza il campo pun a NULL, indicando che questo elemento non è collegato a nessun altro elemento
	return p;                       //Restituisce il puntatore al nuovo elemento elemBFS creato e inizializzato
}

//Altre funzioni utili

//Funzione per il calcolo dell'altezza di un albero
int altezza(tree t) {
	if(get_firstChild(t)==NULL)         //Se il nodo t non ha figli (se get_firstChild(t) restituisce NULL):
		return 0;                       //Restituisce 0, indicando che l'altezza dell'albero è 0 perché non ci sono nodi sotto t.
	int max=0;                          //max tiene traccia dell'altezza massima tra i sottoalberi di t,
    int max_loc;                        //max_loc conterrà l'altezza calcolata per ciascun sottoalbero di t1 durante il ciclo successivo.
	tree t1 = get_firstChild(t);        //Ottiene il puntatore al primo figlio di t.
	while(t1!=NULL){                    //Finchè t1 non è NULL (finché ci sono figli da esplorare):
		max_loc=altezza(t1);            //Chiama ricorsivamente la funzione altezza per calcolare l'altezza del sottoalbero radicato in t1 e memorizza il risultato in max_loc
		if(max_loc>max)                 
			max=max_loc;                //Aggiorna max con max_loc se max_loc è maggiore di max: max conterrà l'altezza massima tra tutti i sottoalberi di t
		t1 = get_nextSibling(t1);       //Ottiene il puntatore al fratello successivo di t1 per procedere con l'esplorazione degli altri figli di t.
	}                                   //Alla fine del ciclo, max conterrà l'altezza massima tra i sottoalberi di t.
	return max+1;                       //Ritorna max + 1 per includere anche il nodo t stesso: l'altezza totale dell'albero radicato in t è max + 1.
}

//Funzione per il calcolo della dimensione di un albero, ovvero il numero totale di nodi nell'albero.
//La dimensione di un albero è il numero totale di nodi che contiene, inclusa la radice e tutti i suoi discendenti.
//La dimensione di un albero vuoto è 0, mentre la dimensione di un albero con un solo nodo (la radice) è 1.
//La funzione può essere implementata sia con una visita DFS ricorsiva che con una visita BFS iterativa.

//Con DFS ricorsiva
int dimensione(tree t){
	int dim=0;                          //dim tiene traccia della dimensione totale dell'albero.
    int dim1;                           //dim1 conterrà la dimensione calcolata per ciascun sottoalbero di t1 durante il ciclo successivo
	tree t1 = get_firstChild(t);        //Ottiene il puntatore al primo figlio del nodo t
	while(t1!=NULL){                    //Finchè t1 non è NULL (finché ci sono figli da esplorare):
		dim1=dimensione(t1);            //ichiama ricorsivamente la funzione dimensione per calcolare la dimensione del sottoalbero radicato in t1 e memorizza il risultato in dim1.
		dim+=dim1;                      //Aggiunge dim1 alla dimensione totale dim per accumulare la dimensione di tutti i sottoalberi di t.
		t1 = get_nextSibling(t1);       //Ottiene il puntatore al fratello successivo di t1 per procedere con l'esplorazione degli altri figli di t
	}                                  
	return dim+1;                       //Restituisce la dimensione totale dell'albero radicato in t.
}

//Con BFS
int dimensione(tree t){
	int count=0;                                //Verrà utilizzata per contare il numero di nodi nell'albero.
	codaBFS c = newQueue();                     //Viene creata una nuova coda BFS vuota utilizzando la funzione newQueue()
	c=enqueue(c,t);                             //Viene inserito il nodo radice dell'albero (t) nella coda BFS.
	while(!isEmpty(c)){                         //Finché la coda non è vuota:
		node* n=dequeue(c);                     //Viene estratto il nodo dalla coda BFS 
		count++;                                //Incremento il contatore count di 1
		tree t1 = get_firstChild(n);            //Ottengo il primo figlio del nodo estratto n (t1 diventa il primo figlio del nodo n o NULL se non ha figli)
		while(t1!=NULL){                        //Finché ci sono ancora figli da esaminare per il nodo estratto n.
				c=enqueue(c,t1);                //Utilizza la funzione enqueue() per inserire il nodo t1 nella coda c
				t1 = get_nextSibling(t1);       //Utilizza la funzione get_nextSibling() per ottenere il prossimo fratello di t1
			}
	}
	return count;                               //Restituisce il valore di count, che rappresenta il numero totale di nodi nell'albero
}