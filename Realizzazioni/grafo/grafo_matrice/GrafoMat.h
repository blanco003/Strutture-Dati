#ifndef GRAFOMAT_H
#define GRAFOMAT_H

#include "Grafo.h"
#include "vector"
#include "./strutture_appoggio/codavt.h"

using namespace std;

// classe per le informazione dell'arco pesato
template<class P>
class InfoArco {
  public:
	  P peso;
	  bool vuoto;

      //costruttore
	  InfoArco(){
		  vuoto = true;
	  }
};


//classe per informazioni sul nodo
template<class E, class P>
class InfoNodo {
  public:
	  E   etichetta;
	  bool vuoto;  //indica se il nodo è vuoto o contiene gia l'etichetta
	  bool temp_stato; // indica lo stato del nodo (se è già stato visitato o è ancora da visitare)
	  InfoArco<P>* archi; // archi uscenti dal nodo

	  InfoNodo(){
		  vuoto = true;
	  }

	  ~InfoNodo(){
		  if (!vuoto)
			  delete [] archi;
	  }


};



//classe Nodo
class NodoG{
  public:
      //costruttori
	  NodoG(int i){
		  nodoId = i;
	  }
	  NodoG(){}


	  int getId(){ return nodoId; }
	  void setId(int id) {nodoId = id;}

  private:
	  int nodoId;
};

//classe grafo
template<class E, class P>
class GrafoMat : public Grafo<E, P, NodoG > {
  public:
	
    typedef E Etichetta;
    typedef P Peso;
    typedef NodoG Nodo;
    typedef Arco_<Peso, Nodo> Arco;
    typedef Grafo<Etichetta, Peso, Nodo> Grafo_;
    typedef typename Grafo_::ListaNodi ListaNodi;
	typedef typename Grafo_::ListaNodiPos ListaNodiPos;

	//costruttore
    GrafoMat(int);

	//distruttore
    ~GrafoMat();

	//operatori
    bool vuoto() const;
    void insNodo(NodoG&);
    void insArco(Nodo, Nodo, Peso);
    void cancNodo(Nodo);
    void cancArco(Nodo, Nodo);


	bool esisteNodo(Nodo) const;
	bool esisteArco(Nodo,Nodo) const;

    ListaNodi Adiacenti(Nodo) const ;
    ListaNodi list_nodi() const ;

	//informazioni sui nodo
    Etichetta leggiEtichetta(Nodo) const;
    void scriviEtichetta(Nodo, Etichetta);


	//STATO: true = visitato, false = non visitato
	bool leggi_temp_stato(Nodo) const;
    void scrivi_temp_stato(Nodo, bool);

	//informazioni sugli archi
    Peso leggiPeso(Nodo, Nodo) const ;
    void scriviPeso(Nodo, Nodo, Peso) ;

    void set_all_states(); // setta tutti gli stati di visita a false (non visitati)

    //ALGORITMI DI VISITA
    void dfs(Nodo);
    void bfs(Nodo);

	int numNodi(){
		return nodi;
	};
	int numArchi(){
		return archi;
	};

 private:
    InfoNodo<E,P>* matrice;
    int dimensione; //numero massimo di nodi che può contenere il grafo
    int nodi;   //numero di nodi presenti attualmente
	int archi; //numero di archu presenti attualmente
};

// Costruttore
template<class E, class P>
GrafoMat<E, P>::GrafoMat(int dim) : dimensione(dim), nodi(0), archi(0) {
    matrice = new InfoNodo<E, P>[dimensione];
    for (int i = 0; i < dimensione; ++i) {
        matrice[i].archi = new InfoArco<P>[dimensione];
    }
}

// Distruttore
template<class E, class P>
GrafoMat<E, P>::~GrafoMat() {
    delete[] matrice;
}

// Verifica se il grafo è vuoto
template<class E, class P>
bool GrafoMat<E, P>::vuoto() const {
    return nodi == 0;
}

// Inserisce un nodo nel grafo
template<class E, class P>
void GrafoMat<E, P>::insNodo(NodoG& n) {
    if (nodi < dimensione) {
        matrice[n.getId()].vuoto = false;
        ++nodi;
    }
}

// Inserisce un arco nel grafo
template<class E, class P>
void GrafoMat<E, P>::insArco(Nodo nodo1, Nodo nodo2, Peso peso) {
    if (!matrice[nodo1.getId()].vuoto && !matrice[nodo2.getId()].vuoto) {
        if (matrice[nodo1.getId()].archi[nodo2.getId()].vuoto) {
            matrice[nodo1.getId()].archi[nodo2.getId()].vuoto = false;
            matrice[nodo1.getId()].archi[nodo2.getId()].peso = peso;
            ++archi;
        }
    }
}

// Cancella un nodo dal grafo
template<class E, class P>
void GrafoMat<E, P>::cancNodo(Nodo nodo) {
    if (!matrice[nodo.getId()].vuoto) {
        matrice[nodo.getId()].vuoto = true;
        for (int i = 0; i < dimensione; ++i) {
            if (!matrice[i].vuoto && !matrice[i].archi[nodo.getId()].vuoto) {
                matrice[i].archi[nodo.getId()].vuoto = true;
                --archi;
            }
        }
        --nodi;
    }
}

// Cancella un arco dal grafo
template<class E, class P>
void GrafoMat<E, P>::cancArco(Nodo nodo1, Nodo nodo2) {
    if (!matrice[nodo1.getId()].vuoto && !matrice[nodo2.getId()].vuoto &&
        !matrice[nodo1.getId()].archi[nodo2.getId()].vuoto) {
        matrice[nodo1.getId()].archi[nodo2.getId()].vuoto = true;
        --archi;
    }
}

// Verifica se un nodo esiste nel grafo
template<class E, class P>
bool GrafoMat<E, P>::esisteNodo(Nodo nodo) const {
    return !matrice[nodo.getId()].vuoto;
}

// Verifica se esiste un arco tra due nodi in input
template<class E, class P>
bool GrafoMat<E, P>::esisteArco(Nodo n1,Nodo n2) const {
    if (!matrice[n1.getId()].vuoto && !matrice[n2.getId()].vuoto &&
        !matrice[n1.getId()].archi[n2.getId()].vuoto) {
        return true;
    }
    return false; 
}

// Restituisce la lista dei nodi adiacenti a un nodo specificato
template<class E, class P>
typename GrafoMat<E, P>::ListaNodi GrafoMat<E, P>::Adiacenti(Nodo nodo) const {
    ListaNodi adiacenti;
    if (!matrice[nodo.getId()].vuoto) {
        for (int i = 0; i < dimensione; ++i) {
            if (!matrice[i].vuoto && !matrice[nodo.getId()].archi[i].vuoto) {
                adiacenti.insert(new NodoG(i), adiacenti.begin());
            }
        }
    }
    return adiacenti;
}

// Restituisce la lista di tutti i nodi nel grafo
template<class E, class P>
typename GrafoMat<E, P>::ListaNodi GrafoMat<E, P>::list_nodi() const {
    ListaNodi nodiList;
    for (int i = 0; i < dimensione; ++i) {
        if (!matrice[i].vuoto) {
            nodiList.insert(new NodoG(i), nodiList.begin());
        }
    }
    return nodiList;
}

// Restituisce l'etichetta di un nodo
template<class E, class P>
typename GrafoMat<E, P>::Etichetta GrafoMat<E, P>::leggiEtichetta(Nodo nodo) const {
    return matrice[nodo.getId()].etichetta;
}

// Scrive un'etichetta su un nodo
template<class E, class P>
void GrafoMat<E, P>::scriviEtichetta(Nodo nodo, Etichetta etichetta) {
    if (!matrice[nodo.getId()].vuoto) {
        matrice[nodo.getId()].etichetta = etichetta;
    }
}


// Restituisce lo stato di un nodo
template<class E, class P>
bool GrafoMat<E, P>::leggi_temp_stato(Nodo nodo) const {
    return matrice[nodo.getId()].temp_stato;
}

// Scrive lo stato di un nodo, lo imposta a visitato (true) o ancora da visitare (false)
template<class E, class P>
void GrafoMat<E, P>::scrivi_temp_stato(Nodo nodo, bool x) {
    if (!matrice[nodo.getId()].vuoto) {
        matrice[nodo.getId()].temp_stato = x;
    }
}

// Restituisce il peso di un arco
template<class E, class P>
typename GrafoMat<E, P>::Peso GrafoMat<E, P>::leggiPeso(Nodo nodo1, Nodo nodo2) const {
    if (!matrice[nodo1.getId()].vuoto && !matrice[nodo2.getId()].vuoto &&
        !matrice[nodo1.getId()].archi[nodo2.getId()].vuoto) {
        return matrice[nodo1.getId()].archi[nodo2.getId()].peso;
    }
    return Peso(); // Ritorna un valore di default se l'arco non esiste
}

// Scrive il peso di un arco
template<class E, class P>
void GrafoMat<E, P>::scriviPeso(Nodo nodo1, Nodo nodo2, Peso peso) {
    if (!matrice[nodo1.getId()].vuoto && !matrice[nodo2.getId()].vuoto &&
        !matrice[nodo1.getId()].archi[nodo2.getId()].vuoto) {
        matrice[nodo1.getId()].archi[nodo2.getId()].peso = peso;
    }
}

// imposta tutti i nodi come non visitati (false)
template<class E, class P>
void GrafoMat<E,P>::set_all_states(){

    ListaNodi lista_nodi = list_nodi();
	ListaNodiPos pos = lista_nodi.begin();

	while(!lista_nodi.end(pos)){
		NodoG nodo = *(lista_nodi.read(pos));
        scrivi_temp_stato(nodo,false);
		pos = lista_nodi.next(pos);
	}
    return;
}


// PRIMA DI CHIAMARE DFS CHIAMARE set_all_states() prima per impostare tutti i nodi a false, siccome e' ricorsiva non possiamo farlo dentro
template<class E, class P>
void GrafoMat<E,P>::dfs(Nodo n){

    //sarebbe da controllare se il grafo non è vuoto
    scrivi_temp_stato(n,true);
	cout<<endl<<"Esamino nodo ("<<leggiEtichetta(n)<<") e ora e' marcato con "<<leggi_temp_stato(n);
	

	ListaNodi lista_adj = Adiacenti(n);
	ListaNodiPos pos = lista_adj.begin();

	while(!lista_adj.end(pos)){

		Nodo nodo = *(lista_adj.read(pos));

        if(leggi_temp_stato(nodo)==false){
            dfs(nodo);
        }else{
            cout<<endl<<"Nodo ("<<leggiEtichetta(nodo)<<") gia visitato";
        }
		pos = lista_adj.next(pos);
		

	}
}

template<class E, class P>
void GrafoMat<E,P>::bfs(Nodo n){ 

    //sarebbe da controllare se il grafo non è vuoto
    //prima di inziare settiamo tutti i nodi come non visitati
    set_all_states();

    Coda<Nodo> c;
    c.inCoda(n);

    while(!c.codaVuota()){
        Nodo u = c.leggiCoda();
        c.fuoriCoda();

        if(leggi_temp_stato(u)==false){
            scrivi_temp_stato(u,true);
            cout<<endl<<"Esamino nodo ("<<leggiEtichetta(u)<<") e ora e' marcato con "<<leggi_temp_stato(u);
        }
        
        ListaNodi adj = Adiacenti(u);
        ListaNodiPos pos = adj.begin();

        // scorriamo i nodin adiacenti ad u ed inseriamoli in coda
        while(!adj.end(pos)){
            Nodo v = *(adj.read(pos));
            if(leggi_temp_stato(v)==false){
                c.inCoda(v);
            }else{
                cout<<endl<<"Nodo ("<<leggiEtichetta(v)<<") gia visitato";
            }
            pos = adj.next(pos);
        }

    }

}

#endif
