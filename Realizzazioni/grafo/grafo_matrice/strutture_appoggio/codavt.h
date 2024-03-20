#ifndef _CODAVT_
#define _CODAVT_
#include <iostream>
#include <cassert>

using namespace std;

template < class tipoelem > class Coda {
public:
       Coda(int);
       Coda();              
       ~Coda();
       void creaCoda();
       bool codaVuota();
       void fuoriCoda();
       tipoelem leggiCoda();
       void inCoda(tipoelem);
       void inCodaNDup(tipoelem);
       // servizio
       void stampaCoda();
       bool contiene(tipoelem);
private:
        tipoelem *elementi;
        int testa, lung, maxlung;
};

template <class tipoelem> Coda<tipoelem>::Coda(int n){
maxlung = n;
creaCoda();
}

template <class tipoelem> Coda<tipoelem>::Coda(){
maxlung = 100; // coda standard di 100 elementi
creaCoda();
}


template <class tipoelem> Coda<tipoelem>::~Coda(){
delete[] elementi;
}

template <class tipoelem> void Coda<tipoelem>::creaCoda(){
elementi = new tipoelem[maxlung];
testa = 0;
lung = 0;
}

template <class tipoelem> bool Coda<tipoelem>::codaVuota(){
return (lung == 0);
}

template <class tipoelem> tipoelem Coda<tipoelem>::leggiCoda(){
assert (!codaVuota());
return (elementi[testa]);
}

template <class tipoelem> void Coda<tipoelem>::fuoriCoda(){
assert(!codaVuota());
testa = (testa + 1) % maxlung;
lung--;
}

template <class tipoelem> void Coda<tipoelem>::inCoda(tipoelem a){
assert(lung != maxlung);
elementi[(testa+lung) % maxlung] = a;
lung++;
}

template <class tipoelem> void Coda<tipoelem>::stampaCoda(){
// lung � il numero di elementi nella coda
   if (!codaVuota())
   {
      int indice;
      for (int i=0; i<lung;i++)
      {
          indice = (testa + i) % maxlung;    
          cout << elementi[indice] << " ";   
      }
   }
   else 
      cout << "CODA VUOTA";   
}   

template <class tipoelem> bool Coda<tipoelem>::contiene(tipoelem e){
// lung � il numemero di elementi nella coda
bool trovato = false;
if (!codaVuota())
{
   int i=0;
   int indice;
   while (!trovato && i<lung)
   {
      indice = (testa + i) % maxlung;
      if (elementi[indice] == e)
         trovato=true;
      i++;            
   }   
}
return trovato;
}

template <class tipoelem> void Coda<tipoelem>::inCodaNDup(tipoelem a){
assert(lung != maxlung);
if (!contiene(a))
{
   elementi[(testa+lung) % maxlung] = a;
   lung++;
}
}
#endif // _CODAVT_H
