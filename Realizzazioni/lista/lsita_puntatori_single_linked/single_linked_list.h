#ifndef _SINGLE_LINKED_LIST_H
#define _SINGLE_LINKED_LIST_H

#include "linear_list.h"


template<class T>
class Linked_List;

template< class T >
class Node {

 friend class Linked_List<T>; //permette alla classe lista di accedere alla parte privata di N
 
 private:
	T _value; 	//valore dell'elemento
	Node<T> * _pNext;  //puntatore all'elemento successivo
};

template< class T >
class Linked_List : public Linear_list<T, Node<T>*>{ 
 public:
	typedef typename Linear_list<T, Node<T>*>::value_type value_type;
	typedef typename Linear_list<T, Node<T>*>::position position;

	// costruttori
	Linked_List();
	Linked_List(int);

	// costruttore per copia
	Linked_List(const Linked_List<T>& );

	//distruttore
	~Linked_List();

	// operatori
	void create();
	bool empty() const;
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
	position last() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void insert(const value_type &, position);
	void erase(position);
	int size() const;


	// sovraccarico di operatori
	Linked_List<T>& operator=(const Linked_List<T>&); // operatore di assegnamenti
	bool operator==(const Linked_List<T> &) const; // controlla l'uguaglianza di 2 liste
	 
 private:
	Node<T> * _pHead; //puntatore al primo elemento della lista (testa)
	int _length; // lunghezza della lista
};


//costruttore: alloca la memoria per un nuovo nodo, imposta la testa la nodo creato, e setta la lunghezza a 0
template< class T >
Linked_List< T >::Linked_List() {
	_pHead = new Node<T>;
	_pHead->_pNext = _pHead;
	_length = 0;
}

//costruttore di copia
template< class T >
Linked_List< T >::Linked_List(const Linked_List<T>& L) {
  _length = 0;

	_pHead = new Node<T>;
	_pHead->_pNext = _pHead;

	if (!L.empty()){
		position p = L.begin();
		for (int i=0;i<L.size();i++){
			insert(L.read(p), last());
			p = L.next(p);
		}
	}
}

//distruttore: dealloca la memoria di tutta la lista
template< class T >
Linked_List< T >::~Linked_List(){
	while(!empty())
		erase(begin());
	delete _pHead;
}

//inizializza la lunghezza a 0
template< class T >
void Linked_List< T >::create(){
	if (empty())
			_length = 0;
}


template< class T >
bool Linked_List< T >::empty() const {
	return(_pHead == _pHead->_pNext);   //se l'espressione booleana da true, ovvero se la il puntatore alla testa coincide con il successivo, la lista è vuota
}



//restituisce il puntatore al primo elemento della lista
template< class T >
typename Linked_List< T >::position
Linked_List< T >::begin() const {
	return (_pHead->_pNext);
}

//restituisce il puntatore all'ultimo elemento della lista
template< class T >
typename Linked_List< T >::position
Linked_List< T >::last() const {
	position p=begin();
	while (!end(p))
		p=next(p);
	return p;
}

//restituisce il puntatore all'elemento successivo
template< class T >
typename Linked_List< T >::position
Linked_List< T >::next(position p) const {
	return(p->_pNext);
}

//restituisce il puntatore all'elemento precedente
template< class T >
typename Linked_List< T >::position Linked_List< T >::previous(position p) const {
  position prev=begin();
	while (!end(prev) && next(prev)!=p)
    prev=next(prev);
	return prev;
}

//restituisce true se il puntatore in input rappresenta l'ultimo elemento
template< class T >
bool Linked_List< T >::end(position p) const {
	return(p == _pHead);
}

//legge l'elemento in posizione data
template< class T >
typename Linked_List< T >::value_type
Linked_List< T >::read(position p) const {
	if (!end(p))
		return(p->_value);
	else
		return -1;
}

//scrive il valore dell'elemento in posizione data
template< class T >
void Linked_List< T >::write(const value_type &a, position p) {
	if (!end(p))
    p->_value = a;
}

//inserisce un nuovo nodo in posizione data, (prima di p)
template< class T >
void Linked_List< T >::insert(const value_type &a, position p){
	position t = new Node<T>;
	t->_value = a;

	t->_pNext = p;
  position prev=previous(p);
	prev->_pNext = t;

	_length++;
}

//dealloca la memoria del nodo in posizione data
template< class T >
void Linked_List< T >::erase(position p){
	if (!empty() && !end(p)){
		position prev=previous(p);
		prev->_pNext = p->_pNext;
		delete p;
	}
}

//operatore di assegnamento, sovraccaricamento dell'operatore =
template<class T>
Linked_List<T>& Linked_List<T>::operator=(const Linked_List<T>& L){
	if (this != &L){ //evita autoassegnamenti
		_length = 0;

		_pHead = new Node<T>;
		_pHead->_pNext = _pHead;

		if (!L.empty()){
      		position p = L.begin();
			for (int i=0;i<L.size();i++) {
				insert(L.read(p), last());
				p = L.next(p);
			}
		}
	}
	return *this;
}

//controlla se 2 liste sono uguali, sovraccaricamento dell'operatore =
template<class T>
bool Linked_List<T>::operator==(const Linked_List<T> &L) const{
	if (L.size() != _length)
		return false;
	position p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->_value != pL->_value)
			return false;
		p = p->_pNext;
		pL = pL->_pNext;

	}
	return true;
}

// restituisce la lunghezza della lista
template<class T>
int Linked_List<T>::size() const{
	int c = 0;
	position p = begin();
	while(!end(p)){
		c++;
		p = next(p);
	}
	return c;
}



#endif // _SINGLE_LINKED_LIST_H








