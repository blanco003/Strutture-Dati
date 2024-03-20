#ifndef ALBERON_H
#define ALBERON_H

#include <iostream>
#include <cassert>  

#include "./strutture_appoggio/codavt.h"

using namespace std;

template<class I>
class AlberoN;

// classe Nodo dell'albero N-Ario
template<class I>
class TreeNodo {

	friend class AlberoN<I>;

	// sovraccarica operatore != di confronto tra 2 nodi
	bool operator != (TreeNodo n){
		if(_elemento != n->_elemento || _padre != n->_padre || _primoFiglio != n->_primoFiglio || _fratelloSuccessivo != n->_fratelloSuccessivo){
			return true;
		}
		return false;
	}

	// sovraccarica operatore == di confronto tra 2 nodi
	bool operator == (TreeNodo n){
		if(_elemento == n->_elemento && _padre != n->_padre == _primoFiglio != n->_primoFiglio && _fratelloSuccessivo == n->_fratelloSuccessivo){
			return true;
		}
		return false;
	}	

	private:
		I _elemento;
		TreeNodo<I> * _padre = nullptr;
		TreeNodo<I> * _primoFiglio = nullptr;
	 	TreeNodo<I> * _fratelloSuccessivo = nullptr;	
};


template<class I>
class AlberoN {
 public:

	typedef I elemento;
	typedef TreeNodo<I>* Nodo;

	// costruttore
	AlberoN(){
		creaAlbero();
	};

	// operatori
	void creaAlbero () ;
	bool alberoVuoto () const ;
	void insRadice (elemento) ;
	Nodo Radice () const ;
	Nodo padre (Nodo) const ;
	bool foglia (Nodo) const ;
	Nodo primoFiglio (Nodo) const ;
	bool ultimoFratello (Nodo) const ;
	Nodo fratelloSuccessivo (Nodo) const ;
	void cancSottoAlbero (Nodo);
	void insFirstSubTree(Nodo,AlberoN &);
	void insSubTree(Nodo,AlberoN &);
	void insPrimoFiglio(Nodo, elemento);  
	void insFratello(Nodo, elemento);  
	void copia(Nodo,Nodo);
	void scriviNodo (Nodo, elemento) ;
	elemento leggiNodo (Nodo) const ;

	// Visite 
	void preVisita(Nodo n) const;  
	void postVisita(Nodo n) const;
	void inVisita(Nodo,int) const;
	void visitaAmpiezza(Nodo n) const;
	void dfs_con_stampa_livelli(Nodo,int) const;
	void bfs_con_stampa_livelli(Nodo) const;
	void stampa(Nodo n) const; 


 	private:
		Nodo _Radice;

};

template <class I>
void AlberoN<I>::creaAlbero(){
	_Radice = nullptr;
}

template <class I>
bool AlberoN<I>::alberoVuoto() const{
	return(_Radice==nullptr);
}

template <class I>
void AlberoN<I>::insRadice (elemento i){
	_Radice=new TreeNodo<I>();
	_Radice->_elemento=i;
}

template <class I>
typename AlberoN<I>::Nodo AlberoN<I>::Radice () const{
	return _Radice;
}

template <class I>
typename AlberoN<I>::Nodo AlberoN<I>::padre (Nodo n) const{
	if (n->_padre!=nullptr)
		return n->_padre;
}

template <class I>
bool AlberoN<I>::foglia(Nodo n) const{
	return (n->_primoFiglio==nullptr);
}

template <class I>
typename AlberoN<I>::Nodo AlberoN<I>::primoFiglio (Nodo n) const{
	if (!foglia(n)){
		return n->_primoFiglio;
	}
}

template <class I>
bool AlberoN<I>::ultimoFratello (Nodo n) const {
	return (n->_fratelloSuccessivo==nullptr);
}

template <class I>
typename AlberoN<I>::Nodo AlberoN<I>::fratelloSuccessivo (Nodo n) const{
	if (!ultimoFratello(n)){
		return n->_fratelloSuccessivo;
	}
}


// inserisce un Nodo come primoFiglio di n
template <class I>
void AlberoN<I>::insPrimoFiglio(Nodo n, elemento el){
	Nodo newNodo=new TreeNodo<I>();
	newNodo->_elemento=el;
	newNodo->_fratelloSuccessivo=n->_primoFiglio;
	newNodo->_padre=n;
	n->_primoFiglio=newNodo;
}

// inserisce un Nodo come fratello di n
template <class I>
void AlberoN<I>::insFratello(Nodo n, elemento el){
	Nodo newNodo=new TreeNodo<I>();
	newNodo->_elemento=el;
	newNodo->_fratelloSuccessivo=n->_fratelloSuccessivo;
	newNodo->_padre=n->_padre;
	n->_fratelloSuccessivo=newNodo;
}

template <class I>
void AlberoN<I>::scriviNodo (Nodo n, elemento el){
	n->_elemento=el;
}

template <class I>
typename AlberoN<I>::elemento AlberoN<I>::leggiNodo (Nodo n) const{
	return n->_elemento;
}

// funzione di servizio per la copia dei nodi
template<class T>
void AlberoN<T>::copia(Nodo n, Nodo daCopiare) {
    if (daCopiare != nullptr) {
        if (daCopiare->_fratelloSuccessivo != nullptr)
            copia(n, daCopiare->_fratelloSuccessivo);
        inserisciPrimoFiglio(n, daCopiare->_elemento);
        if (daCopiare->_primofiglio != nullptr)
            copia(primoFiglio(n), daCopiare->_primofiglio);

    }
}

//inserisce l'albero T come primofiglio del nodo n in input
template<class T>
void AlberoN<T>::insFirstSubTree(Nodo n, AlberoN<T> &T) {
    if (!alberoVuoto() && !T.alberoVuoto()) {
       Nodo r1 = new TreeNodo<T>();
       //creo un nuovo nodo e vi copio il contenuto della radice di a
        scriviNodo(r1,T.leggiNodo(T.Radice()));
        //se a non è foglia copio tutto il suo sottoalbero in r1
        if (!T.foglia(T.Radice())){
			copia(r1,T.primoFiglio(T.Radice()));
		} 
        //inserisco il nuovo albero come primoFiglio di n
        r1->_padre = n;
        r1->_fratelloSuccessivo = n->_primofiglio;
        n->_primofiglio = r1;
    } else throw std::out_of_range("UNO DEI DUE ALBERI E' VUOTO, OPERAZIONE IMPOSSIBILE");
}

//inserisce l'albero T come fratello successivo del nodo n in input
template<class T>
void AlberoN<T>::insSubTree(Nodo n, AlberoN<T> &T) {
    if (!alberoVuoto() && !T.alberoVuoto()) {
        if (n != _Radice) {
            //creo un nuovo nodo e vi copio il contenuto della radice di a
            Nodo r1 = new TreeNodo<T>();
            scriviNodo(r1,T.leggiNodo(T.Radice()));
            //se a non è foglia copio tutto il suo sottoalbero in r1
            if (!T.foglia(T.Radice())){
				copia(r1,T.primoFiglio(T.Radice()));
			} 
            //inserisco il nuovo albero come fratelloSuccessivo di n
            r1->_fratelloSuccessivo = n->_fratelloSuccessivo;
            r1->_padre = n->_padre;
            n->_fratelloSuccessivo = r1;

        } else{
			cout<<"\nErrore : la radice per definizione non ha fratelli";
		} 
    } else{
		cout<<"\nErrore : controlla che entrambi gli alberi non siano vuoti";
	}
}


// cancella tutti i nodi a partire dal sottoalbero radicato in n
template <class T> 
void AlberoN<T>::cancSottoAlbero(Nodo n) {
	if(!alberoVuoto()){
		
		// finche n ha ancora dei figli cancello tutti gli alberi che hanno come radice il primo figlio di n
		while(n->_primoFiglio != nullptr){
			cancSottoAlbero(n->_primoFiglio);
		}

		if( n != _Radice){
			// se il nodo non è la radice dell'albero e non ha fratelli allora aggiorno l'albero
			if(n->_fratelloSuccessivo == nullptr){
				n->_padre->_primoFiglio->_fratelloSuccessivo = nullptr;
			}
			// se il nodo non è radice ed è il primoFiglio allora aggiorno l'albero
			if(n->_padre->_primoFiglio == n){
				n->_padre->_primoFiglio = n->_fratelloSuccessivo;
			}
		}

		// cancello il nodo
		delete n;

	}else{
		cout<<"\nAlbero vuoto !";
	}
}

//Ricerca in profondità (DFS)
template <class T> 
void AlberoN<T>:: preVisita(Nodo n) const{
		cout<< " "<< leggiNodo(n);
		if(!foglia(n)){
			 Nodo m = primoFiglio(n);
			 while(!ultimoFratello(m)){
					preVisita(m);
					m = fratelloSuccessivo(m);
			 }
			 preVisita(m);
		}
};

template <class T> 
void AlberoN<T>::dfs_con_stampa_livelli(Nodo n,int livello_corrente) const{

		cout<<"\nEsamino il nodo ("<< leggiNodo(n)<<") al livello : "<<livello_corrente;

		if(!foglia(n)){
			 Nodo m = primoFiglio(n);
			 while(!ultimoFratello(m)){
					dfs_con_stampa_livelli(m,livello_corrente+1);
					m = fratelloSuccessivo(m);
			 }
			 dfs_con_stampa_livelli(m,livello_corrente+1);
		}
}

template <class T> 
void AlberoN<T>:: postVisita(Nodo n) const{
		if(!foglia(n)){
			 Nodo m = primoFiglio(n);
			 while(!ultimoFratello(m)){
					postVisita(m);
					m = fratelloSuccessivo(m);
			 }
			 postVisita(m);
		}
		cout<< " "<< leggiNodo(n);
};


//BFS
template <class T> 
void AlberoN<T>:: visitaAmpiezza(Nodo n) const{
	Coda<Nodo> c;
	c.inCoda(Radice());

    while (!c.codaVuota()) {
		Nodo nodoCorrente = c.leggiCoda();
		c.fuoriCoda();
        cout << " " <<leggiNodo(nodoCorrente);

		if(!foglia(nodoCorrente)){
        	Nodo figlio = primoFiglio(nodoCorrente);
			while(!ultimoFratello(figlio)){
				c.inCoda(figlio);
				figlio = fratelloSuccessivo(figlio);
			}
		c.inCoda(figlio);

		}
		
    }
}

template <class T> 
void AlberoN<T>::bfs_con_stampa_livelli(Nodo n) const{

	Coda<Nodo> c;
	c.inCoda(Radice());

	int livello_corrente = 0;
	int nodi_livello_corrente = 1;
	int nodi_livello_successivo = 0;

    while (!c.codaVuota()) {
		Nodo nodoCorrente = c.leggiCoda();
		c.fuoriCoda();

        cout<<"\nEsamino il nodo ("<< leggiNodo(nodoCorrente)<<") al livello : "<<livello_corrente;
		nodi_livello_corrente--;

		if(!foglia(nodoCorrente)){
        	Nodo figlio = primoFiglio(nodoCorrente);
			while(!ultimoFratello(figlio)){
				c.inCoda(figlio);
				nodi_livello_successivo++;
				figlio = fratelloSuccessivo(figlio);
			}
		c.inCoda(figlio);
		nodi_livello_successivo++;
		}

		if(nodi_livello_corrente == 0){
			livello_corrente++;
			nodi_livello_corrente = nodi_livello_successivo;
			nodi_livello_successivo = 0;
		}
		
    }
}


template <class T>
void AlberoN<T>::inVisita(Nodo u,int i) const{
	if(foglia(u)){
		cout<<" "<< leggiNodo(u);
	}else{
		
		Nodo c =  primoFiglio(u);
		int k = 0;
		while(!ultimoFratello(c) && k<i){
				k=k+1;
				inVisita(c, i);
				c = fratelloSuccessivo(c);
			}

		if (ultimoFratello(c) && k<i){
			inVisita(c,i);
		}
			
		cout<<" "<< leggiNodo(u);

		while (!ultimoFratello(c)){
				inVisita(c, i);
				c = fratelloSuccessivo(c);
		}
		if (k==1){
			inVisita(c,i);
		}
	
	}	
} 


template <class I>
void AlberoN<I>::stampa(Nodo n) const {
	using namespace std;
	Nodo p;
	cout << n->_elemento << ":";
	if (!foglia(n)) {
		p=primoFiglio(n);
		while (!ultimoFratello(p)) {
			cout << " " << p->_elemento;
			p=fratelloSuccessivo(p);
		}
		cout << " " << p->_elemento << endl;
		p=primoFiglio(n);
		while (!ultimoFratello(p)) {
			stampa(p);
			p=fratelloSuccessivo(p);
		}
		stampa(p);
	} else {
		cout << endl;
	}
}



#endif  /* _ALBERON_H_ */
