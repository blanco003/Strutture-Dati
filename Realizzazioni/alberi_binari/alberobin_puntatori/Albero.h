#ifndef _ALBEROBC_H_
#define _ALBEROBC_H_
#include "Cella.h"
#include "./strutture_appoggio/codavt.h"
#include <iostream>
using namespace std;


template <class T> 
class BinAlbero {
   public:

      // tipi
      typedef T tipoelem; 
      typedef Cella<T>* Nodo; 

      // costruttori
      BinAlbero(); 
      
      // operatori
      void creaBinAlbero(); //inizializza l'albero
      bool binAlberoVuoto() const;
      Nodo binRadice() const; 
      Nodo binPadre(Nodo) const;
      Nodo figlioSinistro(Nodo) const;
      Nodo figlioDestro(Nodo) const;
      bool sinistroVuoto(Nodo) const;
      bool destroVuoto(Nodo) const;
      void costrBinAlbero(BinAlbero<T>,BinAlbero<T>); 
      void cancSottoBinAlbero(Nodo);
      T leggiNodo(Nodo) const;
      void scriviNodo(Nodo, tipoelem);
      void insBinRadice(Nodo);
      void insFiglioSinistro(Nodo);
      void insFiglioDestro(Nodo);
      // ~BinAlbero(); //distruttore

      // visite dell'albero
      void visitaPreordine(Nodo) const; //DFS
      void visitaPostordine(Nodo) const;
      void visitaSimmetrica(Nodo) const;
      void visitaAmpiezza(Nodo) const ; //BFS
      void dfs_con_stampa_livelli(Nodo,int ) const;
      void bfs_con_stampa_livelli(Nodo) const;
      void stampa(Nodo, int) const;

   private:
      Nodo radice; 
};

//costruttore
template <class T> BinAlbero<T>::BinAlbero(){
   creaBinAlbero();
}

//inizializza la radice a null
template <class T> void BinAlbero<T>::creaBinAlbero(){
  radice=NULL;
}

template <class T> bool BinAlbero<T>::binAlberoVuoto() const {
    return (radice==NULL);
}

//restituisce il puntatore radice dell'albero
template <class T> Cella<T>* BinAlbero<T>::binRadice() const {
    return (radice);
}

//resitituisce, se il nodo in input non è la radice, il puntatore al nodo padre
template <class T> Cella<T>* BinAlbero<T>::binPadre(Nodo n) const  {
      if (n!=radice)
         return (n->getDAD());
      else
          return NULL;
}

//restituisce il puntatore al nodo figlio sinistro del nodo in input
template <class T> Cella<T>* BinAlbero<T>::figlioSinistro(Nodo n) const {
      return (n->getSX());
}

//restituisce il puntatore al nodo figlio destro del nodo in input
template <class T> Cella<T>* BinAlbero<T>::figlioDestro(Nodo n) const {
      return (n->getDX());
}

template <class T> bool BinAlbero<T>::sinistroVuoto(Nodo n) const {
      return (n->getSX()==NULL);
}

template <class T> bool BinAlbero<T>::destroVuoto(Nodo n) const {
      return (n->getDX()==NULL);
}

//inizializza, se non lo si è gia fatto, la radice dell'albero
template <class T> void BinAlbero<T>::insBinRadice(Nodo n){
   if (radice == NULL)
   {
      radice=n;
      radice->setSX(NULL);    // non ha figli
      radice->setDX(NULL);    // non ha figli           
      radice->setDAD(NULL);  // non ha genitore
   }
}

//inizializza il nodo figlio sinistro del nodo in input, se non lo si è gia fatto
template <class T> void BinAlbero<T>::insFiglioSinistro(Nodo n){
         if (sinistroVuoto(n))
         {
            n->setSX(new Cella<T>);
            n->getSX()->setDAD(n);  //il nodo padre sara il nodo in input
            n->getSX()->setSX(NULL);
            n->getSX()->setDX(NULL);
            
         }
}

//inizializza il nodo figlio destro del nodo in input, se non lo si è gia fatto
template <class T> void BinAlbero<T>::insFiglioDestro(Nodo n){
         if (destroVuoto(n))
         {
            n->setDX(new Cella<T>);
            n->getDX()->setDAD(n); //il nodo padre sara il nodo in input
            n->getDX()->setSX(NULL);
            n->getDX()->setDX(NULL);
         }
}

//legge il valore del nodo in input
template <class T> T BinAlbero<T>::leggiNodo(Nodo n) const {
   if (n != NULL)
      return (n->getElemento());
}

//scrive il valore nel nodo in input
template <class T> void BinAlbero<T>::scriviNodo(Nodo n, tipoelem a){
   if (n != NULL)
      n->setElemento(a);
}

//cancella tutti i nodi al di sotto del nodo in input
template <class T> void BinAlbero<T>::cancSottoBinAlbero(Nodo n){
      if (n!=NULL){

         if (!sinistroVuoto(n))
            cancSottoBinAlbero(figlioSinistro(n));

         if (!destroVuoto(n))
            cancSottoBinAlbero(figlioDestro(n));

         if (n != radice) {
            Nodo padre = binPadre(n);
            if (figlioSinistro(padre)==n){
               padre->setSX(NULL);
            }
            else{ 
               padre->setDX(NULL);
            }
         }   
         else
             radice = NULL;                  
      }
}

//DFS
template <class T> void BinAlbero<T>::visitaPreordine(Nodo n) const { 
      if (n!=NULL){
         cout << leggiNodo(n) << " "; // esamina nodo n
         visitaPreordine(figlioSinistro(n));
         visitaPreordine(figlioDestro(n));
      }
}

template <class T> void BinAlbero<T>::visitaPostordine(Nodo n) const {
      if (n!=NULL)
      {

         visitaPostordine(figlioSinistro(n));
         visitaPostordine(figlioDestro(n));
         cout << leggiNodo(n) << " "; // esamina nodo n
      }
}

template <class T> void BinAlbero<T>::visitaSimmetrica(Nodo n)  const {
      if (n!=NULL)
      {
         visitaSimmetrica(figlioSinistro(n));
         cout << leggiNodo(n) << " "; // esamina nodo n
         visitaSimmetrica(figlioDestro(n));         
      }
}

//BFS : ricerca in ampiezza
template <class T> 
void BinAlbero<T>::visitaAmpiezza(Nodo n) const {
      if (n!=NULL){
         Coda<Nodo> c;
         c.inCoda(n);
         while (!c.codaVuota()){
               Nodo nn=c.leggiCoda(); // visito un nodo ...
               cout << leggiNodo(nn) << " "; // esamino il nodo
               c.fuoriCoda();
               // ... e accodo i figli
               if (!sinistroVuoto(nn))
                   c.inCoda(figlioSinistro(nn)); 
               if (!destroVuoto(nn)) 
                  c.inCoda(figlioDestro(nn));
         }
      }
}


template <class T>
void BinAlbero<T>::dfs_con_stampa_livelli(Nodo n, int livello) const {
    if (binAlberoVuoto()) {
        cout << endl << "Albero vuoto!!" << endl;
    }

    if (n != NULL) {
        cout << endl << "Esamina nodo (" << leggiNodo(n) << ") al livello : " << livello; // esamina nodo n
        dfs_con_stampa_livelli(figlioSinistro(n),livello+1);
        dfs_con_stampa_livelli(figlioDestro(n),livello+1);
    }
}

template <class T>
void BinAlbero<T>::bfs_con_stampa_livelli(Nodo n) const {
      if (n!=NULL){

         int livello_corrente = 0;
         int nodi_livello_corrente = 1; //la radice
         int nodi_livello_successivo = 0;

         Coda<Nodo> c;
         c.inCoda(n);
         while (!c.codaVuota()){
              
               Nodo temp = c.leggiCoda();
               cout <<endl<<"esamina nodo ("<< leggiNodo(temp) << ") al livello : "<<livello_corrente; // esamina nodo n
               c.fuoriCoda();
               nodi_livello_corrente--;
               
               if (!sinistroVuoto(temp)){
                   c.inCoda(figlioSinistro(temp)); 
                   nodi_livello_successivo++;
               }
               if (!destroVuoto(temp)){
                  c.inCoda(figlioDestro(temp));
                  nodi_livello_successivo++;
               }

               if(nodi_livello_corrente==0){
                  livello_corrente++;
                  nodi_livello_corrente = nodi_livello_successivo;
                  nodi_livello_successivo = 0;
               }
               
         }
      }
}


//Funzioni di Serivizio
template <class T> void BinAlbero<T>::stampa(Nodo n, int livello) const {
   const int Nspaces=4;
   int spaces=livello*Nspaces;
   if (n != NULL)
   {
      for (int i=1;i<spaces;i++) 
          cout << " "; 
      cout << leggiNodo(n) << endl;
      livello++;
      if (!sinistroVuoto(n))
        stampa(figlioSinistro(n),livello);
      if (!destroVuoto(n))
         stampa(figlioDestro(n),livello);
   }      
}



#endif /* _ALBEROBC_H_ */
