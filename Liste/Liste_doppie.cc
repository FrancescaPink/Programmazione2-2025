#include <iostream>
using namespace std ;

//Definizione di una struttura chiamata elem che rappresenta un elemento di una lista doppiamente collegata.
struct elem
{
       int inf;			//Campo informativo
       elem* pun;		//Puntatore al prossimo elemento della lista
       elem* prev;		//Puntatore all'elemento precedente della lista (previous)
} ;
typedef elem* lista ;	//Puntatore a un elemento della lista

//Primitive

//Primitiva testa
int head(lista p) {		//Prende in input un puntatore a una lista (lista p) e restituisce il valore (inf) del primo elemento della lista.
	return p->inf;		//Utilizza l'operatore di dereferenziazione -> per accedere al membro inf della struttura elem.
}

//Primitiva coda
lista tail(lista p) {	//Prende in input un puntatore a una lista (lista p).
	return p->pun;		//Restituisce un puntatore all'elemento successivo della lista, che è memorizzato nel membro pun
}

//Primitiva del puntatore prev
lista prev(lista p) { 	//Prende in input un puntatore a una lista (lista p). 
	return p->prev;		//Restituisce un puntatore all'elemento precedente della lista, che è memorizzato nel membro prev
}

//Primitiva per l'inserimento di un valore nella lista
lista insert_elem(lista l, elem* e){	//Inserisce un nuovo elemento e all'inizio della lista l e restituisce il nuovo puntatore alla lista.
	e->pun=l;			//Imposta il puntatore pun del nuovo elemento e per puntare all'inizio attuale della lista l.
	if(l!=NULL)			//Se la lista non è vuota (l non è NULL): 
		l->prev=e;		//Imposta il puntatore prev del vecchio primo elemento per puntare al nuovo elemento e
	e->prev=NULL;		//Imposta il puntatore prev del nuovo elemento e a NULL, poiché ora e è il primo elemento della lista.
	return e;			//Restituisce il puntatore al nuovo primo elemento della lista
}

//Primitiva per l'eliminazione di un valore nella lista
lista delete_elem(lista l, elem* e){	//Rimuove un elemento e dalla lista l e restituisce il nuovo puntatore alla lista.
		if(l==e)						//Verifica se l'elemento da rimuovere e è la testa della lista l
			l=e->pun; 					//e è la testa della lista: aggiorna l per puntare al secondo elemento della lista, che diventa la nuova testa.
		else 							//e non è la testa della lista
			(e->prev)->pun = e->pun;	//Aggiorna il puntatore pun dell'elemento precedente a e per saltare e e puntare direttamente al successivo di e.
		if(e->pun!=NULL)				//Verifica se e non è l'ultimo elemento della lista.
			(e->pun)->prev=e->prev;		//Aggiorna il puntatore prev del successivo di e per puntare al precedente di e
		delete e;						//Dealloca la memoria occupata dall'elemento e.
		return l;
}

//Primitiva per la ricerca di un valore presente nella lista
elem* search(lista l, int v) {		//Cerca un elemento nella lista l il cui valore corrisponde alla stringa v e restituisce un puntatore a tale elemento
    while (l != NULL) {				//Esegue un ciclo finché l non è NULL, cioè finché non si raggiunge la fine della lista.
        if (head(l) == v)			//Confronta il valore del primo elemento della lista (ottenuto con head(l)) con la stringa v
            return l;				//Se sono uguali restituisce il puntatore all'elemento corrente l
        else						
            l = tail(l);			//Se non sono uguali, aggiorna l per puntare al prossimo elemento della lista
    }
    return NULL;					//Se il ciclo termina senza trovare un elemento con il valore v, restituisce NULL.
}

//Funzioni utili

//Funzione per la stampa di una lista
void stampalista(lista p)			//Stampare il contenuto di una lista doppiamente collegata, prende un puntatore alla lista (lista p) come argomento
{
	cout<<"[";
	while (p != NULL) {				//Finché non si arriva alla fine della lista
		cout<<head(p)<<" " ; 		//Stampa valore
		cout<<"(p: "<<p<< " succ:"<<p->pun<<" prev:"<<p->prev<<")";		//Stampa l'indirizzo del puntatore corrente (p), il puntatore all'elemento successivo (p->pun) e il puntatore all'elemento precedente (p->prev).
		p = tail(p);     			//Spostamento sul prossimo elemento
	}
	cout<<"]"<<endl;
}

//Funzione per la creazione di una lista
lista crealista(int n)						//Prende un intero n come argomento e restituisce un puntatore alla lista (lista).
{
      lista testa = NULL ;					//Inizializza il puntatore alla testa della lista a NULL, indicando che la lista è inizialmente vuota
      for (int i = 1 ; i <= n ; i++) {
          elem* p = new elem ;				//Alloca memoria per un nuovo elemento di tipo elem.
          cout<<"URL "<<i<<": " ;			//Chiede all'utente di inserire un valore (inf) per il nuovo elemento
          cin>>p->inf;						//Legge il nuovo elemento
          p->pun=p->prev=NULL;				//Inizializza i puntatori pun e prev del nuovo elemento a NULL.
          testa=insert_elem(testa,p);		//Usa la funzione insert_elem per inserire il nuovo elemento p all'inizio della lista. Aggiorna il puntatore testa in modo che punti al nuovo primo elemento della lista.
      }
      return testa ;						//Restituisce il puntatore alla testa della lista, ora contenente n elementi.
}

//Funzione per la cancellazione di una lista
lista cancella(lista l, int v){			    //Prende un puntatore alla lista (lista l) e un intero (int * v) come argomenti e restituisce un puntatore alla lista aggiornata.
	elem* e;								//Dichiara un puntatore e che verrà usato per trovare gli elementi da cancellare.
	while((e=search(l,v))!=NULL) {			//Utilizza un ciclo while per cercare e cancellare gli elementi con valore corrispondente a v. Il ciclo continua finché search trova un elemento (e) con il valore v e e non è NULL.
		cout<<"Cancello un elemento con valore "<<v<<endl;
		l=delete_elem(l,e);					//Chiama delete_elem per rimuovere l'elemento trovato e dalla lista e aggiorna il puntatore alla lista l.
	}
	cout<<"Fine cancellazione!!"<<endl;
	return l;								//Restituisce il puntatore alla lista aggiornata, dopo aver rimosso tutti gli elementi con il valore v.
}

//Funzione per la navigazione tra gli elementi presenti all'interno di una lista
void naviga(elem* e) {                              //Prende un puntatore a un elemento della lista (elem* e) come argomento
	char scelta;                                    //Dichiara una variabile scelta di tipo char per memorizzare l'input dell'utente.
	cout<< "Trovato!!";
	do {
		cout<< "Cosa vuoi fare (B per backward (muoversi indietro), F per forward (muoversi avanti), S per stop)"<<endl;
		cin>>scelta;
	    if(scelta=='F' && tail(e)!=NULL) {          //Se l'utente sceglie 'F' e l'elemento corrente ha un successivo (tail(e) != NULL), stampa il valore del successivo elemento e aggiorna e per puntare al successivo.
	    	cout<<head(tail(e))<<endl;
	    	e=tail(e);
        }
	    else
	    	if(scelta=='B' && prev(e) !=NULL) {     //Se l'utente sceglie 'B' e l'elemento corrente ha un precedente (prev(e) != NULL), stampa il valore del precedente elemento e aggiorna e per puntare al precedente.
	    		cout<<head(prev(e))<<endl;
	    		e=prev(e);
            }
	    else cout<<"Elemento non esistente!!"<<endl;    //Se l'utente sceglie 'F' ma non c'è un successivo o sceglie 'B' ma non c'è un precedente, stampa un messaggio di errore.
    }		
    while(scelta!='S');                                 //Il ciclo continua finché l'utente non inserisce 'S' per fermarsi.
}

//Main

int main()
{
    int n, v;               //Numero di elementi (n), valore da inserire o cercare (v)
    int scelta;             //La scelta dell'utente (scelta) e il 
    lista testa=NULL;       //Il puntatore alla testa della lista (testa)
    elem* ris;              //Puntatore all'elemento trovato (ris).
    do {
    	cout<<"Cosa vuoi fare?"<<endl;
    	cout<<"1: Creare una lista"<<endl;
    	cout<<"2: Cancellare valori dalla lista"<<endl;
    	cout<<"3: Stampare la lista"<<endl;
    	cout<<"4: Cercare valori nella lista"<<endl;
    	cout<<"5: Esci"<<endl;
    	cin>>scelta;
    	switch(scelta) {
    	    case 1:         //L'utente specifica il numero di elementi, e la lista viene creata chiamando crealista(n).
                cout << "Inserire il numero di elementi da inserire nella lista" << endl;
    		    cin >> n;
    		    testa = crealista(n);
    		break;
    		case 2:         //L'utente specifica il valore da cancellare, e la funzione cancella(testa, v) viene chiamata per rimuovere tutti gli elementi con quel valore.
                cout<<"Inserire il valore da cancellare:"<<endl;
    		    cin>>v;
    		    testa=cancella(testa,v);
    		break;
    		case 3:         //Viene chiamata la funzione stampalista(testa) per stampare il contenuto della lista. 
                stampalista(testa);
    		break;
    		case 4:         //L'utente specifica il valore da cercare, e se l'elemento viene trovato, viene chiamata la funzione naviga(ris) per permettere la navigazione tra gli elementi.
                cout << "Valore da cercare"<<endl;
    		    cin>>v;
   			    ris=search(testa,v);
    		    if(ris!=NULL)
    			    naviga(ris);
    		    else
    			    cout<<"Valore non presente"<<endl;
    		break;
    		case 5:         //Messaggio di uscita
                cout<<"Ciao ciao!!"<<endl;}
    	}
		while(scelta!=5);
		//Non dimenticare di deallocare la memoria della lista quando non serve più (deallocare la memoria della lista prima di terminare il programma è importante per evitare perdite di memoria)
        while (testa != NULL) {     //Il ciclo continua fino a quando testa non è NULL
            elem* temp = testa;     //Viene creato un puntatore temporaneo temp che punta all'elemento attuale della testa.
            testa = tail(testa);    //La testa viene aggiornata per puntare al prossimo elemento della lista (tail(testa)).
            delete temp;            //Il nodo puntato da temp viene deallocato usando delete.
        }
    return 0;
}