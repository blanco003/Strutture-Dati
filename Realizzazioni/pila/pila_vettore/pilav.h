#ifndef _PILAV_H
#define _PILAV_H
using namespace std;
#include <iostream>

const int MAXLUNGH=100; // capacita max pila


template<class T>
class Nodo{
  public:


    Nodo(){};
    
    // inizializza un nodo
    Nodo(T label){
      elemento = label;
    }

    // distruttore nodo
    ~Nodo(){
      // TODO
    }

    // scrivi elemento nel nodo
    void setElemento(T label){
      elemento = label;
    }


    T getElemento() const {
       return elemento;
    }

    // sovraccarico operatore ==  : compara membro a membro 2 nodi e restituisce true se uguali
    bool operator ==(Nodo &n){
        return (n.getElemento() == elemento);
    }


  private:
    T elemento;
};

template<class T>
class Pila{
   
  public:
    Pila();
    ~Pila();
    void creaPila();
    bool pilaVuota() const;
    T leggiPila() const;
    void fuoriPila();
    void inPila(T);
    void stampaPila() const;
  private:
    Nodo<T> elementi[MAXLUNGH];
    int testa;
};


// costruttore : inizializza la pila
template<class T>
Pila<T>::Pila(){
  creaPila();
}

// distruttore : dealloca tutta la memoria utlizzata
template<class T>
Pila<T>::~Pila(){
  while(!pilaVuota()){
    fuoriPila();
  }
}

// inizializza la pila
template<class T>
void Pila<T>::creaPila(){
  for (int i=0;i<MAXLUNGH;i++){
      elementi[i].setElemento(0);
   }
  testa=0;
}

template<class T>
bool Pila<T>::pilaVuota() const{
    return testa==0; 
}

// leggi l'elemento in testa alla pila
template<class T>
T Pila<T>::leggiPila() const{
  return (elementi[testa-1].getElemento());
}

// estrae l'elemento in testa alla pila e lo cancella
template<class T>
void Pila<T>::fuoriPila(){
  if (!pilaVuota()){
      testa-=1; // scaliamo semplicemente la testa senza cancellare niente
  }else{
      cout<<"nessun elemento nella pila"<<endl;
  }
}

// aggiunge un elemento in cima alla pila
template<class T>
void Pila<T>::inPila(T el){
  if (testa==MAXLUNGH){
      cout<<"raggiunta capacita' massima della pila"<<endl;
  }else{
      elementi[testa].setElemento(el);
      testa++;
  }
}

template<class T>
void Pila<T>::stampaPila() const{
  int i;
  for (i = 0; i< testa; i++)
    cout <<  elementi[i].getElemento() << " ";
}

#endif // _PILAV_H
