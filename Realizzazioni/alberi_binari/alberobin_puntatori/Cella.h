#ifndef _CELLA_H
#define _CELLA_H
#include <iostream>
using namespace std;

// classe cella usata come Nodo per l'implementazione dell'albero binario
template <class T> class Cella{

  public:
    //tipi
    typedef T tipoelem;

    //costruttori
    Cella(); 
    Cella(tipoelem);

    //operatori
    void setElemento(tipoelem);   
    tipoelem getElemento() const;   
    void setSX(Cella<T>*);    
    void setDX(Cella<T>*);
    void setDAD(Cella<T>*);
    Cella<T>* getSX() const;
    Cella<T>* getDX() const;
    Cella<T>* getDAD() const;

    //sovraccarica operatori
    bool operator ==(Cella<T>);
    bool operator <=(Cella<T>);

  private:
    tipoelem elemento;
    Cella<T>* SX;
    Cella<T>* DX;
    Cella<T>* DAD;
};


// costruttori
template <class T> 
Cella<T>::Cella(){
         SX=NULL;
         DX=NULL;
         DAD=NULL;
}

template <class T> 
Cella<T>::Cella(tipoelem e){
  elemento = e;
}

template <class T> 
void Cella<T>::setElemento(tipoelem label){
  elemento = label;
}

template <class T>  
T Cella<T>::getElemento() const{
    return elemento;
}

template <class T> 
void Cella<T>::setSX(Cella<T>* p){
  SX=p;
}

template <class T> 
void Cella<T>::setDX(Cella<T>* p){
  DX=p;
}

template <class T> 
void Cella<T>::setDAD(Cella<T>* p){
  DAD=p;
}

template <class T>
Cella<T>* Cella<T>::getSX() const{
  return SX;
}

template <class T> 
Cella<T>* Cella<T>::getDX() const{
  return DX;
}
  
template <class T> 
Cella<T>* Cella<T>::getDAD() const{
  return DAD;
}
  

template <class T> 
bool Cella<T>::operator<=(Cella<T> cella){
  return (getElemento == cella.getElemento);
}

template <class T> 
bool Cella<T>::operator==(Cella<T> cella){
  return (getElemento <= cella.getElemento);
}

#endif // _CELLA_H
