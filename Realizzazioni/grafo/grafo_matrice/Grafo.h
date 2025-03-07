#ifndef GRAFO_H
#define GRAFO_H

#include "./strutture_appoggio/list_vector.h"

// classe Arco pesato
template<class P, class N>
class Arco_ {
  public:
	  N nodo1;
	  N nodo2;
	  P peso;
};

template<class E, class P, class N>
class Grafo {
  public:
	  typedef E Etichetta;
	  typedef P Peso;
	  typedef N Nodo;

	  typedef Arco_<Peso, Nodo> Arco;
	  typedef List_vector<Nodo*> ListaNodi;
	  typedef typename List_vector<Nodo*>::position ListaNodiPos;
	  typedef List_vector<Arco> ListaArchi;

	  virtual bool vuoto() const = 0;
	  virtual void insNodo(Nodo&) = 0;
	  virtual void insArco(Nodo, Nodo, Peso) = 0;
	  virtual void cancNodo(Nodo) = 0;
	  virtual void cancArco(Nodo, Nodo) = 0;
	  //	virtual bool esisteNodo(Nodo) = 0;
	  //	virtual bool esisteArco(Arco) = 0;
	  virtual ListaNodi Adiacenti(Nodo) const = 0;
	  virtual ListaNodi list_nodi() const = 0;
	  virtual Etichetta leggiEtichetta(Nodo) const = 0;
	  virtual void scriviEtichetta(Nodo, Etichetta) = 0;
	  virtual Peso leggiPeso(Nodo, Nodo) const = 0;
	  virtual void scriviPeso(Nodo, Nodo, Peso) = 0;

	  virtual int numNodi() = 0;
	  virtual int numArchi() = 0;

	  virtual ~Grafo(){};
};


#endif
