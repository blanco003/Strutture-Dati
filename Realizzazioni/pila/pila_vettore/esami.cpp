#include "pilav.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*  TRACCIA : ✔
    -Data una pila di interi, implementare in c++ una funzione che restituisca una
    nuova pila i cui elementi corrispondano a quelli presenti nella pila data e siano
    ordinati dall’alto (top della pila) al basso. 
*/

Pila<int> reverse(Pila<int> &P){
    Pila<int> temp;
    while(!P.pilaVuota()){
        temp.inPila(P.leggiPila());
        P.fuoriPila();
    }
    return temp;
}



//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/* TRACCIA : ✔
    -Data una pila di elementi di tipo intero, implementare un metodo in c++ che
    elimini dalla pila tutti gli elementi maggiori di un certo intero k (l’ordinamenti
    degli elementi della pila risultante deve corrispondere a quello della pila data in input)
*/

void elimina_maggiori(Pila<int> &P, int k){

    // creiamo una pila di appoggio
    Pila<int> temp;

    while(!P.pilaVuota()){
        // se sono minori gli inseriamo nella pila temporanea
        if(P.leggiPila() <= k){
            temp.inPila(P.leggiPila());
        }
        P.fuoriPila();
    }

    // ora temp contiene tutti gli elementi richiesti ma in ordine inverso dunque rimettiamo in P
    while(!temp.pilaVuota()){
        P.inPila(temp.leggiPila());
        temp.fuoriPila();
    }
}



//----------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------

/* TRACCIA : ✔
    Implementare le seguenti funzioni che operano sul tipo di dati stack<T>. !!! Si noti che all’uscita
    dalle funzioni lo stato dello stack passato deve coincidere con quello data in input !!! .

    - void remove (stack<T> &S, T k) : rimuove dallo stack S tutte le occorenze di k
    - int count (stack<T> &S, T k) : restituisce il numero di occorrenze di k
    - stack<T> reverse (stack<T> &S) :  restituisce uno stack che contiene in ordine inverso gli elementi di S

*/

template <class T>
void remove(Pila<T> &S, T k){
    Pila<T> temp;

    while(!S.pilaVuota()){
        if(S.leggiPila() != k){
            temp.inPila(S.leggiPila());
        }
        S.fuoriPila();
    }

    while(!temp.pilaVuota()){
        S.inPila(temp.leggiPila());
        temp.fuoriPila();
    }
}

template <class T>
int count(Pila<T> &S, T k){

    Pila<T> temp;
    int count = 0;

    while(!S.pilaVuota()){
        if(S.leggiPila() == k){
           count++;
        }
        temp.inPila(S.leggiPila());
        S.fuoriPila();
    }

    while(!temp.pilaVuota()){
        S.inPila(temp.leggiPila());
        temp.fuoriPila();
    }

    return count;
}

template <class T>
Pila<T> reverse_stack(Pila<T> &S){
    Pila<T> temp;
    while(!S.pilaVuota()){
        temp.inPila(S.leggiPila());
        S.fuoriPila();
    }
    // si dovrebbe rimettere S nello stato iniziale
    return temp;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------