#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

// classe astratta listaLinare

template< class T, class P >
class Linear_list{
 public:
	typedef T value_type;   // tipo degli elementi contenuti nella lista
	typedef P position; 

	//virtual = l'operatore DEVE essere implementato nella classe che eredita
	//const = l'operatore non modifica la lista

	// operatori
	virtual void create() = 0; //inizializzatore
	virtual bool empty() const = 0; 
	virtual value_type read(position) const = 0;
	virtual void write(const value_type & x, position p) = 0; // scrive c nella posizione p
	virtual position begin() const = 0;  // restituisce l'iteratore al primo elemento
	virtual bool end(position) const = 0; // vero se la posizione in input è l'ultima della lista
	virtual position next(position) const = 0; // restituisce l'iteratore alla posizione successiva
	virtual position previous(position) const = 0; // restituisce l'iteratore alla posizione precedente
	virtual void insert(const value_type &, position) = 0; // inserisce un elemento
	virtual void erase(position pos) = 0; // elimina l'elemento alla posizione data
	
	// funzioni di servizio
	//friend ostream& operator<< <T,P>(ostream&, const Linear_list<T,P>&);

	/* Altre funzioni di servizio implementabili */
	/*
		virtual int size() const;  // returns the size of the list
		virtual void push_front(const value_type &); // insert a new element at the beginning
		virtual void push_back(const value_type &); // insert a new element at the end
		virtual void pop_front(); // removes the first element
		virtual void pop_back(); // removes the last element
		virtual void clear(); // erases all the elements
	*/

};

/* sovraccarica <<. Attenzione se il tipo restituito da read non è primitivo, allora
 * anche per questo tipo bisogna sovraccaricare l'operatore << 
 */
template< class T, class P >
ostream& operator<<(ostream& os, const Linear_list<T,P> &l){
	typename Linear_list<T,P>::position p;
	p = l.begin(); //p è inizialiazzato con l'iteratore al primo elemento
	os << "[";
	while (!l.end(p)){            //finche l'iteratore non è l'ultima posizone della lista
		if (p != l.begin())
			os << ", " << l.read(p);
		else
			os << l.read(p);
		p = l.next(p);     //l'iteratore viene aggioranto con la posizione dell'elemento successivo
	}
	os << "]";
	return os;
}

/*
template< class T, class P >
int Linear_list<T,P>::size() const{
   ....
}
*/

#endif // _LISTALIN_H

