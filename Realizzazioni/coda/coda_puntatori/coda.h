#ifndef _CODAP_
#define _CODAP_
using namespace std;
#include <iostream>

template <class T>
class Coda {
public:

    class Cella {
    public:
        T v;
        Cella* next;
    };

    Coda() {
        testa = coda = nullptr;
    }

    ~Coda() {
        while (!Codavuota()) {
            Fuoricoda();
        }
    }

    bool Codavuota() {
        return (testa == nullptr);
    }

    // inseriesce un elemento in fine alla coda
    void Incoda(T e) {
        Cella* tmp = new Cella;
        tmp->v = e;
        tmp->next = nullptr;
        if (Codavuota()) {
            testa = coda = tmp;
        }
        else {
            coda->next = tmp;
            coda = tmp;
        }
    }

    // legge l'elemento in testa alla coda, ovvero quello entrato prima di tutti in fila
    T Leggicoda() {
  
      if(Codavuota()) {
            cout<<"\nCoda vuota !";
            return T();
       }
    
        return testa->v;
    }   

    // rimuove l'elemento in testa, ovvero quello entrato prima di tutti in fila
    void Fuoricoda() {
        if (!Codavuota()) {
             Cella* tmp = testa;
             testa = testa->next;
             delete tmp;
        }
    }

    void stampaCoda(){
        Cella* temp = testa;
        if(Codavuota()){
            cout<<"\nCoda vuota !";
            return;
        }

        cout<<"\nCoda : (TESTA) [";
        while(temp != coda->next){
            cout<<temp->v<<" ";
            temp = temp->next;
        }
        cout<<"] (CODA)";
    }



private:
    Cella* testa;
    Cella* coda;
};

#endif //_CODAP_