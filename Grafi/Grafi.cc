#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//Struttura lista di adiacenza
struct adj_node {
    int node;                   //Identificativo del nodo
    float weight;               //peso dell'arco
    adj_node* next;             //Puntatore al prossimo elemento della lista di adiacenza
};
typedef adj_node* adj_list;     //Definisce un nuovo tipo chiamato adj_list che è un puntatore a un adj_node

//Grafo
typedef struct{
    adj_list* nodes;            //Array dinamico di dim liste di adiacenze, una per vertice
    int dim;                    //Dimensione dell'array, ovvero il numero di vertici nel grafo.
} graph;                        //Numero dei vertici

//Primitive di creazione ed aggiornamento di un grafo

//Primitiva che restituisce la rappresentazione di un grafo di n vertici identificati univocamente da 1 a n attraverso n liste di adiacenza
graph new_graph(int n){                 //Prende un intero n come argomento
	graph G;                            //Dichiara una variabile G di tipo graph.
	G.dim=n;                            //Imposta la dimensione del grafo G al valore n passato in ingresso
	G.nodes= new adj_list[n];           //Alloca dinamicamente un array di adj_list con n elementi: ogni elemento di questo array rappresenterà una lista di adiacenza per un vertice del grafo.
	    for (int i=0; i<n; i++) {       //Questo ciclo for inizializza ciascun elemento dell'array G.nodes a NULL
	        G.nodes[i] = NULL;          //Indica che le liste di adiacenza sono vuote inizialmente
	    }
	return G;                           //Restituisce il grafo G inizializzato
}

//Primitiva che aggiunge l'arco orientato (u,v) alla lista di adiacenza del nodo u (aggiunge in testa alla lista). L'arco ha peso w.
void add_arc(graph& G, int u, int v, float w) {     //Prende come argomenti un riferimento a un grafo G, due interi u e v, e un float w
  adj_node* t = new adj_node;                       //Alloca dinamicamente un nuovo nodo di adiacenza t.
  t->node = v-1;                                    //Imposta il nodo di destinazione v (diminuito di 1 per adattarsi all'indice basato su 0 dell'array)
  t->weight = w;                                    //Imposta il peso dell'arco
  t->next = G.nodes[u-1];                           //Imposta il puntatore al prossimo nodo della lista di adiacenza di u (diminuito di 1)
  G.nodes[u-1] = t;                                 //Inserisce il nuovo nodo t all'inizio della lista di adiacenza del nodo u
}

//Primitiva che aggiunge l'arco non orientato (u,v) alle liste di adiacenza di u e v. L'arco ha peso w
void add_edge(graph& g, int u, int v, float w) {    //Prende come argomenti un riferimento a un grafo g, due interi u e v, e un float w
  add_arc(g,u,v,w);                                 //Aggiunge con la funzione add_arc un arco orientato dal nodo u al nodo v con il peso w
  add_arc(g,v,u,w);                                 //Aggiunge un arco orientato dal nodo v al nodo u con il peso w per simulare un arco non orientato tra u e v
}

//Primitive di accesso ad un grafo

//Primitiva che restituisce il numero n dei nodi del grafo
int get_dim(graph g){       //Prende come argomento un grafo g
	return g.dim;           //Restituisce la dimensione del grafo g, che rappresenta il numero di vertici nel grafo
}

//Primitiva che restituisce la testa della lista di adiacenza del nodo con identificativo in ingresso
adj_list get_adjlist(graph g,int u){        //Prende come argomento un grafo g e un intero u
	return g.nodes[u-1];                    //Restituisce la lista di adiacenza del nodo u, che si trova all'indice u-1 dell'array nodes del grafo g
}

//Primitiva che restituisce l’identificativo del nodo contenuto nell’elemento della lista di adiacenza
int get_adjnode(adj_node* l){       //Prende come argomento un puntatore a un nodo di adiacenza l
	return (l->node+1);             //Restituisce il valore del nodo associato al nodo della lista di adiacenza, aggiungendo 1 per convertire l'indice da base 0 a base 1
}

//Primitiva che restituisce il peso del nodo contenuto nell’elemento della lista di adiacenza
float get_adjweight(adj_node* l){   //Prende come argomento un puntatore a un nodo di adiacenza l
	return (l->weight);             //Restituisce il peso associato al nodo della lista di adiacenza
}

//Primitiva che restituisce il prossimo elemento della lista di adiacenza
adj_list get_nextadj(adj_list l){   //Prende come argomento un puntatore a una lista di adiacenza l
	return l->next;                 //Restituisce il puntatore al nodo successivo nella lista di adiacenza
}

//Lettura di un grafo tramite file

//Funzione che aggiungere un arco diretto o un arco non diretto a un grafo a seconda del valore del parametro d
void add(graph& g, int u, int v, float w, bool d) {     //Prende come argomenti un riferimento a un grafo g, due nodi u e v, un peso w e un valore booleano d
	if (d)                                              //Se d è true:
		add_arc(g,u,v,w);                               //Viene chiamata la funzione add_arc per aggiungere un arco diretto
	else                                                //Se d è false:
		add_edge(g,u,v,w);                              //Viene chiamata la funzione add_edge per aggiungere un arco non diretto
}

//Funzione che crea un grafo leggendo i dati da un flusso di input (ifstream)
graph g_build(ifstream &g, bool d, bool w) {    //Prende tre parametri: g (un riferimento a un oggetto di tipo ifstream), d (un booleano che indica se il grafo è diretto o non diretto), w (un booleano che indica se il file contiene pesi degli archi o meno)
    int n;                                      //Dichiarazione della variabile n che conterrà il numero di nodi nel grafo
    g >> n;                                     //Legge il primo valore dal file g e lo memorizza nella variabile n
    graph G = new_graph(n);                     // Chiama la funzione new_graph(n) per creare un nuovo grafo G con n nodi
    int v1,v2;                                  //Dichiarazione delle variabili v1 e v2, che rappresentano i nodi collegati dagli archi
    if (w) {                                    //Se il grafo è pesato (w è true):
        float w;                                //Dichiara float w che conterrà il peso dell'arco
        while (g >> v1 >> v2 >> w) {            //Legge triplette di valori dal file g fino a quando è possibile (v1 e v2 sono i nodi collegati, w è il peso dell'arco)
            add(G,v1,v2,w,d);                   //La funzione add(G, v1, v2, w, d) viene chiamata per aggiungere l'arco al grafo G
        }
    } 
    else {                                      //Se w è false:
        while (g >> v1 >> v2) {                 //Il ciclo while (g >> v1 >> v2) legge coppie di valori (senza il peso dell'arco) dal file g
            add(G,v1,v2,1.0,d);                 //La funzione add(G, v1, v2, 1.0, d) viene chiamata per aggiungere l'arco al grafo G, assumendo un peso predefinito di 1.0 per tutti gli archi.
        }
    }
    return G;                                   //Restituisce il grafo G costruito al chiamante della funzione
}

//Visita di grafi

//Per implementare una visita BFS, occorre utilizzare una struttura dati -> coda con priorità
struct elemBFS
{
       int inf;                     //Informazione contenuta in ogni elemento della coda BFS
       elemBFS* pun ;               //Puntatore al prossimo elemento nella coda
};

typedef elemBFS* lista;             //lista viene utilizzata per rappresentare un puntatore a un elemento elemBFS

typedef struct{                     
	lista head;                     //Puntatore alla testa della coda (primo elemento)
	elemBFS* tail;                  //Puntatore alla coda della coda (ultimo elemento)
} codaBFS;

//Primitive per la visita di grafi

//Primitiva che crea e restituisce un nuovo elemento elemBFS
static elemBFS* new_elem(int n){
	elemBFS* p = new elemBFS ;      //Crea in maniera dinamica un nuovo puntatore elemBFS e alloca memoria per esso
	p->inf=n;                       //Assegna il valore n all'attributo inf dell'elemento appena creato
	p->pun=NULL;                    //Inizializza il puntatore pun dell'elemento a NULL
	return p;                       //Restituisce il puntatore all'elemento elemBFS appena creato
}

//Primitiva per aggiungere un nuovo elemento alla coda codaBFS
codaBFS enqueue(codaBFS c, int i){  //Prende in ingresso: parametro c di tipo codaBFS (la coda di tipo codaBFS a cui aggiungere un nuovo elemento), parametro i di tipo int (il valore intero che deve essere inserito)
	elemBFS *e=new_elem(i);         //Viene creato un nuovo elemento elemBFS utilizzando la funzione new_elem(i)
	if(c.tail!=NULL)                //Se la coda c non è vuota:
		c.tail->pun=e;              //L'elemento e viene aggiunto alla fine della coda: il puntatore pun dell'ultimo elemento della coda (c.tail->pun) viene impostato a puntare al nuovo elemento e
	c.tail=e;                       //Il puntatore c.tail viene aggiornato per puntare al nuovo elemento e, facendolo diventare l'ultimo elemento della coda
	if(c.head==NULL)                //Se la testa della coda c.head è attualmente NULL (è vuota)
		c.head=c.tail;              //Viene impostato c.head uguale a c.tail: ora c.head punta al primo elemento della coda, che è anche l'unico elemento presente
	return c;                       //Viene restituita la coda c aggiornata con il nuovo elemento aggiunto
}

//Primitiva per rimuovere e restituire l'elemento in testa a una coda codaBFS
int dequeue(codaBFS& c) {           //Prende in ingresso un riferimento a un oggetto di tipo codaBFS (qualsiasi modifica fatta a c all'interno della funzione influenzerà direttamente l'oggetto originale)
    int ris=(c.head)->inf;          //Salva l'informazione contenuta nell'elemento in testa alla coda nella variabile ris
	c.head=(c.head)->pun;           //Aggiorna il puntatore head della coda per puntare all'elemento successivo (se presente)
	return ris;                     //Restituisce l'informazione contenuta nell'elemento rimosso dalla coda
}

//Primitiva per restituire l'informazione contenuta nel primo elemento della coda codaBFS passata come parametro
int first(codaBFS c){
	return (c.head)->inf;           //Restituisce il valore dell'attributo inf dell'elemento in testa alla coda c
}

//Primitiva per verificare se una coda codaBFS è vuota
bool isEmpty(codaBFS c){
	if(c.head==NULL)                //Se il puntatore head della coda c è uguale a nullptr (puntatore nullo)
		return true;                //Restituisce true, indicando che la coda è vuota
	return false;                   //Restituisce false, indicando che la coda non è vuota
}

//Primitiva per creare e restituire una nuova coda codaBFS vuota
codaBFS newQueue(){
	codaBFS c={NULL, NULL};         //Crea una variabile c di tipo codaBFS e inizializza i campi head e tail a nullptr (la coda c appena creata è vuota e non contiene elementi)
	return c;                       //Restituisce la coda c appena creata e inizializzata
}

//Grafi connessi e componenti connessi

//Funzione che restituisce TRUE	se il grafo	è connesso,	FALSE altrimenti
bool connected(graph g, int v){
    bool* raggiunto = new bool[get_dim(g)];     //Crea un nuovo array dinamico di booleani raggiunto di dimensione pari al numero di nodi nel grafo g, ottenuto mediante get_dim(g)
	int i;
    //Inizializzazione dell'array raggiunto a false
	for(int i=0; i<get_dim(g); i++)
		raggiunto[i]= false;                    //Inizializza tutti gli elementi dell'array raggiunto a false, indicando che nessun nodo è stato raggiunto inizialmente
    //Creazione di una nuova coda BFS vuota con l'uso della funzione newQueue()
	codaBFS C=newQueue();
    //Segna il nodo iniziale v come raggiunto e lo inserisce nella coda
	raggiunto[v-1]=true;
	C=enqueue(C,v);
    //Esecuzione della BFS per visitare tutti i nodi raggiungibili da v
	while(!isEmpty(C)){
		int w=dequeue(C);                       //Estrae un nodo w dalla cosa
        //Itera su tutti i nodi adiacenti al nodo w
		for(adj_node* n=get_adjlist(g,w);n!=NULL;n=get_nextadj(n)){
			i = get_adjnode(n);                 //Usa la funzione get_adjnode() per ottenere le liste di adiacenza
            //Se il nodo i non è stato ancora raggiunto, lo segna come raggiunto e lo inserisce nella coda
			if(!raggiunto[i-1]){                //Se un nodo adiacente i non è stato ancora raggiunto:
				raggiunto[i-1]=true;            //Segna quel nodo come raggiunto .
				C=enqueue(C,i);                 //Aggiunge quel nodo alla coda C
            }
		}
	}
    //Verifica se tutti i nodi sono stati raggiunti
	for(int i=0;i<get_dim(g);i++)
		if(!raggiunto[i])
            //Se c'è almeno un nodo non raggiunto, il grafo non è connesso
            //delete[] raggiunto; --> DEALLOCAZIONE DELLA MEMORIA
			return false;
    //Se tutti i nodi sono stati raggiunti, il grafo è connesso
	//delete[] raggiunto; --> DEALLOCAZIONE DELLA MEMORIA
    return true;
}

//Rivediamo la funzione connected per le componenti connesse
bool* connected_2(graph g, int v){
	bool* raggiunto = new bool[get_dim(g)];     //Crea un array dinamico di booleani
	int i;
	for(int i=0; i<get_dim(g); i++)
		raggiunto[i]= false;                    //Inizializza l'array a false
	codaBFS C=newQueue();
	raggiunto[v-1]=true;
	C=enqueue(C,v);
	while(!isEmpty(C)){
		int w=dequeue(C);
		for(adj_node* n=get_adjlist(g,w);n!=NULL;n=get_nextadj(n)){
			i = get_adjnode(n);
			if(!raggiunto[i-1]){
				raggiunto[i-1]=true;
				C=enqueue(C,i);
            }
		}
	}
    return raggiunto;                           //Restituisce l'array raggiunto
}

//Funzione per per trovare e stampare tutte le componenti connesse di un grafo
void connected_component(graph g) {
    //Crea un array dinamico di booleani per tracciare i nodi globalmente raggiunti
    bool* raggiunto_globale = new bool[get_dim(g)];
    //Inizializza tutti gli elementi dell'array a false
    for(int i=0; i<get_dim(g); i++)
	    raggiunto_globale[i]= false;
    //Variabile per tracciare se ci sono nodi non visitati - prendo il primo nodo non raggiunto a false 
    bool nodivisitati = false;
    while (!nodivisitati) {
        int j = -1;
        //Trova il primo nodo non raggiunto
        for(int i=0; i<get_dim(g) && j == -1 ; i++)
            if (raggiunto_globale[i] == false) {
                j = i;
            }
        nodivisitati = true;
        if (j != -1) {
            //Chiamata alla funzione connected_2 per trovare tutti i nodi raggiungibili da j+1
            bool* raggiunto = connected_2(g,j+1);
            cout << "Connected component: ";
            for(int i=0; i<get_dim(g); i++) {
                if (raggiunto[i]) {
                    cout << i+1 << " ";             //Stampa i nodi della componente connessa
                }
                //Aggiorna l'array globale di nodi raggiunti
		        raggiunto_globale[i] |= raggiunto[i];
                //Verifica se ci sono ancora nodi non visitati
                nodivisitati &= raggiunto_globale[i];
            }
            cout << endl;
            //delete[] raggiunto; --> Deallocare la memoria dell'array raggiunto
        }
    }
    //delete[] raggiunto_globale; --> Dealloca la memoria dell'array globale di nodi raggiunti
}

//Nuova versione della funzione che determina se un grafo è connesso a partire da un nodo specificato. Inoltre, costruisce e stampa l'albero di copertura (spanning tree) radicato nel nodo specificato.
bool connected_3(graph g, int v){
    //Crea un array dinamico di booleani per tracciare i nodi raggiunti
	bool* raggiunto = new bool[get_dim(g)];
    //Crea un array dinamico di interi per tracciare i padri dei nodi nell'albero di copertura
	int* padre = new int[get_dim(g)];
	int i;
    //Inizializza tutti gli elementi dell'array raggiunto a false
	for(int i=0; i<get_dim(g); i++)
		raggiunto[i]= false;
    //Inizializza tutti gli elementi dell'array padre a -1
	for(int i=0; i<get_dim(g); i++)
			padre[i]= -1;
    //Crea una nuova coda BFS vuota
	codaBFS C=newQueue();
    //Segna il nodo iniziale v come raggiunto e lo inserisce nella coda
	raggiunto[v-1]=true;
	C=enqueue(C,v);
    //Esecuzione della BFS per visitare tutti i nodi raggiungibili da v
	while(!isEmpty(C)){
        //Estrae un nodo w dalla coda
		int w=dequeue(C);
        //Itera su tutti i nodi adiacenti al nodo w
		for(adj_node* n=get_adjlist(g,w);n!=NULL;n=get_nextadj(n)){
            //Ottiene il nodo adiacente
			i = get_adjnode(n);
            //Se il nodo adiacente i non è stato ancora raggiunto:
			if(!raggiunto[i-1]){
                //Segna il nodo adiacente come raggiunto
				raggiunto[i-1]=true;
                //Imposta il padre del nodo adiacente come w-1
				padre[i-1]=w-1;
                //Aggiunge il nodo adiacente alla coda
				C=enqueue(C,i);}
		}
	}
    //Verifica se tutti i nodi sono stati raggiunti
	for(int i=0;i<get_dim(g);i++)
        //Se c'è almeno un nodo non raggiunto, il grafo non è connesso
		if(!raggiunto[i])
            //Dealloca la memoria degli array raggiunto e padre --> delete[] raggiunto; delete[] padre;
			return false;
    //Stampa l'albero di copertura
	cout<<"Spanning tree del nodo "<<v<<endl;
	for(int i=0;i<get_dim(g);i++)
        //Stampa il padre di ogni nodo
		if (padre[i]!=-1)
			cout<<"il padre del nodo "<<i+1<<" e' il nodo "<<padre[i]+1<<endl;
    //Dealloca la memoria degli array raggiunto e padre --> delete[] raggiunto; delete[] padre;
    //Se tutti i nodi sono stati raggiunti, il grafo è connesso
	return true;
}


//Main - non comprende tutte le funzioni, ma aiuta a capire i passaggi verso i file

int main(int argc, char *argv[]) {
    //Se il numero di parametri con cui è stato chiamato il programma è inferiore a tre,
    //si ricorda all'utente che deve inserire anche il nome del file che descrive il grafo
    //e i flag "directed" e "weighted".
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " filename directed weighted\n";
        exit(0);
    }
    //Apertura del file che contiene la descrizione del grafo.
    ifstream g;
    g.open(argv[1]);
    //Stampa dei parametri ricevuti.
    cout << argv[1] << " " << argv[2] << " " << argv[3] << endl;
    //Conversione dei parametri "directed" e "weighted" da stringhe a interi.
    int directed = atoi(argv[2]);       //La funzione atoi (che sta per "ASCII to Integer") è una funzione della libreria standard C/C++ che converte una stringa rappresentante un numero in un valore intero. È inclusa nell'header <cstdlib> in C++
    int weighted = atoi(argv[3]);
    //Costruzione del grafo chiamando la funzione g_build.
    graph G = g_build(g, directed, weighted);
    //Stampa del numero di nodi del grafo.
    cout << get_dim(G) << endl;
    //Stampa dell'array di liste di adiacenza.
    adj_list tmp;
    for (int i = 1; i <= get_dim(G); i++) {
        tmp = get_adjlist(G, i);
        cout << i;
        while (tmp) {
            cout << " --> " << get_adjnode(tmp);
            tmp = get_nextadj(tmp);
        }
        cout << endl;
    }
}