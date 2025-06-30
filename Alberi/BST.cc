#include <iostream>
#include <cstring>
using namespace std;

//Alberi binari di ricerca -> alberi che hanno in ogni nodo un contenuto informativo value e una chiave key

//Definisco una struttura con chiave intera e un valore semplice di tipo stringa
typedef int tipo_key;
typedef char * tipo_inf;
struct bnode {
    tipo_key key;       //Per semplicità si assume che i valori di chiave siano univoci nel bst
    tipo_inf inf;
    bnode * left;
    bnode * right;
    bnode * parent;
};
typedef bnode * bst;

//Funzioni in comune con gli alberi binari normali

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

//Primitive di creazione e accesso al nodo di un bst - ALCUNE PRIMITIVE USANO FUNZIONI DICHIARATE IN BASSO!

//Primitiva per creare un nuovo nodo in un albero binario di ricerca (BST) con una chiave e un'informazione specificate
bnode* bst_newNode(tipo_key k, tipo_inf i){		//Prende in ingresso un valore di tipo tipo_key, definito come int, e un valore di tipo tipo_inf, definito come un puntatore a char
	bnode* n=new bnode;							//Alloca dinamicamente memoria per un nuovo nodo e assegna l'indirizzo di questo nuovo nodo al puntatore n.
	copy(n->inf,i);								//Chiama la funzione copy per copiare la stringa i nel campo inf del nuovo nodo n
	copy_key(n->key, k);						//Chiama la funzione copy_key per copiare il valore della chiave k nel campo key del nuovo nodo n
	n->right=n->left=n->parent=NULL;			//Inizializza tutti i puntatori a NULL
	return n;									//Restituisce il puntatore al nuovo nodo creato
}

//Primitiva che restituisce la chiave associata a un nodo bnode
tipo_key get_key(bnode* n){		//Prende in ingresso un puntatore a un nodo bnode
	return (n->key);			//Restituisce il valore della chiave (key) memorizzato nel nodo n
}

//Primitiva che restituisce l'informazione associata a un nodo bnode
tipo_inf get_value(bnode* n){	//Prende in ingresso un puntatore a un nodo bnode
	return (n->inf);			//Restituisce il valore del campo inf memorizzato nel nodo n
}

//Primitiva che restituisce il puntatore al sottoalbero sinistro di un nodo in un albero binario di ricerca (BST)
bst get_left(bst t){		//Prende in ingresso un puntatore a un nodo dell'albero binario di ricerca (bnode)
	return (t->left);		//Restituisce il puntatore al sottoalbero sinistro del nodo t
}

//Primitiva che restituisce il puntatore al sottoalbero destro di un nodo in un albero binario di ricerca (BST)
bst get_right(bst t){		//Prende in ingresso un puntatore a un nodo dell'albero binario di ricerca (bnode)
	return (t->right);		//Restituisce il puntatore al sottoalbero destro del nodo t
}

//Primitiva che restituisce il genitore (parent) di un nodo bnode in un albero binario di ricerca (BST)
bnode* get_parent(bnode* n){	//Prende in ingresso un puntatore a un nodo bnode (il nodo di cui si desidera ottenere il genitore)
	return (n->parent);			//Restituisce il puntatore al genitore del nodo n. Se il nodo n è la radice dell'albero o non ha un genitore (è NULL), la funzione restituirà NULL
}

//Primitive per l'aggiornamento di un bst

//Primitiva per l'inserimento di un nuovo nodo n in un albero binario di ricerca 
void bst_insert(bst& b, bnode* n){	//Prende in ingresso un riferimento a un puntatore a un nodo bnode (la radice dell'albero binario di ricerca), e un puntatore n a un nodo (il nodo che deve essere inserito)
	bnode* x;						//Questo puntatore sarà utilizzato per navigare attraverso l'albero durante la ricerca del punto di inserimento per il nuovo nodo n.
	bnode* y=NULL;					//Questo puntatore sarà utilizzato per tenere traccia del nodo genitore di x durante questo processo di navigazione
	//Se l'albero è vuoto, il nuovo nodo diventa la radice dell'albero
	if(b==NULL){
		b=n;						//n diventa la radice dell'albero
	}
	else {							//Se l'albero non è vuoto
	    x=b;						//Imposta x alla radice dell'albero b
		//Trova la posizione corretta per inserire il nuovo nodo
	    while (x != NULL) {
	    	y=x;					//Il nodo corrente x diventa il genitore potenziale del nodo n
	      	if (compare_key(get_key(n),get_key(x))<0) {		//Se la chiave del nodo n è minore della chiave del nodo x:
		    	x = get_left(x);							//Ci si sposta nel sottoalbero sinistro di x
	      	}
			else {
		    	x = get_right(x);							//Ci si sposta nel sottoalbero destro di x
	      	}
	    }
		//Collega il nuovo nodo al suo genitore (y)
	    n->parent = y;										//Il campo parent del nodo n viene impostato per puntare al suo nuovo genitore y
		//Inserisce il nuovo nodo come figlio sinistro o destro di y
	    if (compare_key(get_key(n), get_key(y))<0) {		//Se la chiave del nodo n è minore della chiave del nodo y:
	      y->left = n;										//Il nodo n viene inserito come figlio sinistro di y
	    } 		
		else {
	    	y->right = n;									//Il nodo n viene inserito come figlio destro di y
	    }	
	}
}

//Versione ricorsiva della funzione bst_insert
void bst_insert(bst& b, bnode* n){
	//Caso base: se l'albero è vuoto, il nuovo nodo diventa la radice dell'albero
	if(b==NULL) { 
		b=n;
		return;
	}
	//Confronta la chiave del nuovo nodo con la chiave della radice attuale
	if (compare_key(get_key(n),get_key(b))<0)
		//Se la chiave del nuovo nodo è minore della chiave della radice attuale, inserisci nel sottoalbero sinistro
		if(get_left(b)!=NULL)			//Se il sottoalbero sinistro di b non è NULL:
			bst_insert(b->left,n);		//Si richiama ricorsivamente bst_insert per inserire n nel sottoalbero sinistro
		else { 
			//Se il sottoalbero sinistro è vuoto, collega il nuovo nodo come figlio sinistro della radice attuale
			b->left=n;					//Il nuovo nodo n viene collegato come figlio sinistro di b 
			n->parent=b;				//Si imposta il puntatore parent di n per puntare a b
		}
	else
		//Altrimenti, inserisci nel sottoalbero destro
		if(get_right(b)!=NULL)			//Se il sottoalbero destro di b non è NULL:
			bst_insert(b->right,n);		//Si richiama ricorsivamente bst_insert per inserire n nel sottoalbero destro
		else { 
			//Se il sottoalbero destro è vuoto, collega il nuovo nodo come figlio destro della radice attuale
			b->right=n;					//Il nuovo nodo n viene collegato come figlio destro di b 
			n->parent=b;				//Si imposta il puntatore parent di n per puntare a b
		}	
}

//Primitiva per cancellare un nodo dall'albero di ricerca
void bst_delete(bst& b, bnode* n){
	bnode* new_child; 				//Variabile d'appoggio che individua il nodo da sostuire a n come figlio
	// Caso 1: Nodo foglia (non ha figli)
	if (get_left(n) == NULL) {
	    if (get_right(n) == NULL) 	//Nodo foglia
	        new_child=NULL;			//Se n è una foglia, il suo nuovo figlio è NULL
	    else {
	        cout << "Nodo con solo figlio destro\n";		//Solo figlio destro
	        new_child=get_right(n);							//Il nuovo figlio è il figlio destro di n
	    }
	}
	// Caso 2: Nodo con solo figlio sinistro
	else 
		if (get_right(n) == NULL) { 						//Solo figlio sinistro
	    	cout << "Nodo con solo figlio sinistro\n";		// Il nuovo figlio è il figlio sinistro di n
	     	new_child=get_left(n);
		}
		// Caso 3: Nodo con entrambi i figli
		else { 												//Entrambi i figli: cerco l'elemento più grande nel sottoalbero di sx
	        cout << "Nodo con entrambi i figli\n";
	        // Trova il successore in ordine nel sottoalbero sinistro di n
		    bnode* app = get_left(n);
	        while (get_right(app) != NULL) 					//Cerco l'elemento più a destra nel sottoalbero di sx
	           	app = get_right(app);						//Trova l'elemento più a destra nel sottoalbero sinistro di n
	        //Gestione del successore in ordine
			//Se il successore in ordine è una foglia
			if(get_left(app)==NULL){ 						//app è una foglia
				update_father(app, NULL);					//Rimuovi il riferimento al successore in ordine dal suo genitore			
		    } 
			//Se il successore in ordine ha un figlio sinistro
			else {  										//app ha il figlio sinistro
				(app->parent)->right = get_left(app);		//Collega il figlio sinistro del successore al genitore del successore
				(app->left)->parent = get_parent(app);		//Collega il genitore del figlio sinistro del successore al successore stesso
		    }
			//Sostituisci il nodo n con il successore in ordine (app)
			app->left = get_left(n);
			app->right = get_right(n);
			//Aggiorna i puntatori genitore dei figli del successore in ordine
			if(get_left(app)!=NULL)
			    (app->right)->parent = app;
			if(get_left(app)!=NULL)
			    (app->left)->parent = app;
			new_child=app;									//Il nuovo figlio è il successore in ordine (app)
	    }
	//Aggiorna il puntatore genitore del nuovo figlio (new_child)
	if(new_child!=NULL)
	   new_child->parent = get_parent(n);
	//Se n è la radice dell'albero, aggiorna il puntatore alla radice (b)
	if(n==b) 												//n è la radice
	   	b=new_child;
	else
	   	update_father(n, new_child);						//Aggiorna il puntatore genitore del padre di n per puntare a new_child
	delete n;												//Dealloca il nodo n eliminato
}

//Primitive per l'accesso a bst

//Primitiva che cerca un nodo con una chiave specifica k all'interno di un albero binario di ricerca (BST)
bnode* bst_search(bst b,tipo_key k){			//Prende in ingresso un puntatore al nodo radice dell'albero (b) e una chiave k di tipo_key
	while (b != NULL) {							//Finché b non diventa NULL (finchè l'algoritmo continua a cercare):
	    if (compare_key(k,get_key(b))==0)
	    	return b;							//Restituisce il nodo corrente se la chiave corrisponde a quella cercata
	    if (compare_key(k,get_key(b))<0) {
		    b = get_left(b);					//Se la chiave cercata è inferiore, passa al sottoalbero sinistro
	    } 
		else {
		    b = get_right(b);					//Se la chiave cercata è superiore, passa al sottoalbero destro
	    }
	}
	return NULL;								//Se non trova la chiave, restituisce NULL
}

//Funzioni utili --> SE LE DICHIARO STATIC HANNO VISIBILITA' LIMITATA AL FILE IN CUI SONO DEFINITE: NON POSSONO ESSERE CHIAMATE DA ALTRI FILE CHE INCLUDONO IL FILE SU CUI SONO STATE DICHIARATE

//Funzione per copiare un valore di tipo tipo_key da una variabile ad un'altra
static tipo_key copy_key(tipo_key& s,tipo_key s1){	//Prende in ingresso un riferimento a una variabile di tipo tipo_key e una variabile di tipo tipo_key passata per valore
	s=s1;		//Copia il valore di s1 nella variabile referenziata da s: poiché s è un riferimento, questo assegnamento modifica direttamente la variabile a cui s fa riferimento.
	return s;	//Restituisce il valore di s, che ora è uguale a s1
}

//Funzione per confrontare due chiavi di tipo tipo_key
static tipo_key compare_key(tipo_key s,tipo_key s1){	//Prende in ingresso i due valori di chiavi da confrontare
		return s-s1;									//Restituisce il risultato della sottrazione s-s1
}

//Funzione per stampare il valore di una chiave
void print_key(tipo_key k){		//Prende in ingresso la chiave di tipo tipo_key che si desidera stampare
	cout<<k;					//Stampa la chiave
}

//Funzione per la stampa di un albero binario di ricerca - DFS INORDINE
void print_BST(bst b){				
	if(get_left(b)!=NULL)			//Se esiste un sottoalbero sinistro per il nodo b:
		print_BST(get_left(b));		//La funzione print_BST viene chiamata ricorsivamente per stampare il sottoalbero sinistro
	print_key(get_key(b));			//Utilizza la funzione print_key per stampare la chiave del nodo b
	cout<<"  ";						//Stampa uno spazio per separare la chiave dal valore del nodo
	print(get_value(b));			//Utilizza la funzione print per stampare il valore associato alla chiave del nodo b
	cout<<endl;
	if(get_right(b)!=NULL)			//Se esiste un sottoalbero destro per il nodo b:
		print_BST(get_right(b));	//La funzione print_BST viene chiamata ricorsivamente per stampare il sottoalbero destro
}

//Funzione che aggiorna il puntatore al figlio (sinistro o destro) del padre di p al nuovo elemento q
void update_father(bnode* p, bnode* q) {	//Prende in ingresso il puntatore p al nodo che deve essere aggiornato e un puntatore q al nodo che sostituirà p come figlio del suo genitore
	if (p == get_left(get_parent(p)))		//Se il nodo p è il figlio sinistro del suo genitore (p->parent):
		(p->parent)->left = q;				//Aggiorna il puntatore sinistro del genitore (p->parent) per puntare a q: sostituisce il nodo p con il nodo q come figlio sinistro del genitore
	else									//Se il nodo p non è il figlio sinistro del suo genitore, allora è il figlio destro:
		(p->parent)->right = q;				//Aggiorna il puntatore destro del genitore (p->parent) per puntare a q: sostituisce il nodo p con il nodo q come figlio destro del genitore
}

//Funzioni extra - prese da internet

//Funzione che trova il nodo con la chiave minima nel BST a partire dalla radice fornita
bnode* bst_minimum(bnode* root) {		//Prende in ingresso un puntatore root che rappresenta la radice dell'albero o del sottoalbero
    while (root->left != nullptr) { 	//Continua a scendere verso sinistra finché esistono nodi
        root = root->left; 				//Aggiorna root al figlio sinistro
    }
    return root; 						//Restituisce il nodo con la chiave minima
}

//Funzione che trova il nodo con la chiave massima nel BST a partire dalla radice fornita
bnode* bst_maximum(bnode* root) {		//Prende in ingresso un puntatore root che rappresenta la radice dell'albero o del sottoalbero
    while (root->right != nullptr) { 	//Continua a scendere verso destra finché esistono nodi
        root = root->right; 			//Aggiorna root al figlio destro
    }
    return root; 						//Restituisce il nodo con la chiave massima
}
