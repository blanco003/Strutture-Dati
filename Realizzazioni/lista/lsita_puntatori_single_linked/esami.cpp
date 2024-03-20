#include "single_linked_list.h"
#include <vector>
using namespace std;


// -----------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
    scrivire una funzione trasforma che prenda in input una lista ed un valore intero x
    ed incrementi di x tutti gli elementi pari della lista 
*/

template <class T>
void trasforma(Linked_List<T> &list, int x){

    typename Linked_List<T>::position i = list.begin();

    while (!list.end(i)) {
        if (list.read(i) % 2 == 0) {
            list.write(list.read(i) + x, i);
        }
        i = list.next(i);
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
    scrivere una funzione accoda che prenda in input due liste L1 ed L2 e aggiunge in coda
    ad L2 tutti gli elementi di L1 che non sono già presenti in L2
*/

bool presente_lista2(Linked_List<int> &L2,int val){
    Linked_List<int>::position pos = L2.begin();
    while(!L2.end(pos)){
        if(L2.read(pos) == val){
            return true;
        }
        pos = L2.next(pos);
    }
    return false;
}

void accoda(Linked_List<int> &L1,Linked_List<int> &L2){

    Linked_List<int>::position pos = L1.begin();
    while(!L1.end(pos)){
        if(!presente_lista2(L2,L1.read(pos))){
            L2.insert(L1.read(pos),L2.last());
        }
        pos = L1.next(pos);
    }
    
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
    Data una lista di tipo intero implementare le seguenti funzioni:
    - int freq(List &L,int k) : restituisce il numero di occorrenze dei multipli di k nella lista
    - void hist(List &L) : stampa la frequenza di ogni elemento nella lista
    - void remp(List &L) : rimuove dalla lista tutti gli elementi seguiti da un numero dispari
*/

int freq(Linked_List<int> &L, int k){
    
    Linked_List<int>::position pos = L.begin();
    int count = 0;

    while(!L.end(pos)){
        if(L.read(pos) % k == 0){
            count++;
        }
        pos = L.next(pos);
    }
    return count;
}
void hist(Linked_List<int> &L) {
    if (L.empty()) {
        cout << endl << "lista vuota ! ";
        return;
    }

    Linked_List<int>::position pos = L.begin();
    vector<int> visited;

    while (!L.end(pos)) {

        //controlliamo se non abbiamo gia stampato la frequenza dell'elemento
        bool trovato = false;
        for (int i = 0; i < visited.size(); i++) {
            if (visited[i] == L.read(pos)) {
                trovato = true;
                break; 
            }
        }

        if (!trovato) {
            visited.push_back(L.read(pos));
            int count = 0;
            Linked_List<int>::position temp = L.begin();

            while (!L.end(temp)) {
                if (L.read(temp) == L.read(pos)) {
                    count++;
                }
                temp = L.next(temp);
            }

            cout << endl << "Frequenza dell'elemento (" << L.read(pos) << ") : " << count;
        }

        pos = L.next(pos);
    }
}


void remp(Linked_List<int> &L) {
    Linked_List<int>::position pos = L.begin();

    while (!L.end(pos)) {
        if (L.read(L.next(pos)) % 2 != 0) {
            Linked_List<int>::position temp_pos = pos;
            pos = L.next(pos);
            L.erase(temp_pos);
        }else{
            pos = L.next(pos);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA:
    Utilizzando una delle realizzazioni della ADT lista, realizzare in c++ la ADT ListaOrdinata.h per la memorizzazione ordinata di elementi 
    di tipo intero (gli elementi compaiano in modo ordinato e sono ammesse più copie dello stesso elemento). 
    Bisogna realizzare la nuova struttura facendo uso degli operatori della ADT lista.

    La ADT ListaOrdinata mette a disposizione i seguenti operatori:
    - inserisci(S,elemento) : inserisce l'elemento nella sequenza ordinata S
    - rimuovi(S,elemento) : rimuove la prima occorrenza dell'elemento dalla sequenza S
    - differenza(S1,S2) : restituisce una nuova sequenza ordinata ottenuta eliminando da S1 tutti gli elementi presenti in S2
    - sottolista(S1,S2) : restituisce true se la sottolista ordinata S1 è sottolista della lista ordinata S2, false altrimenti.
*/

//--------------------------------------------------------------------------------------------------------------------------------------------------------

/*  TRACCIA: ✔
    Data una lista di interi modificarla in modo da eliminare tutti gli elementi in
    cui il valore è un multiplo della rispettiva posizione ordinale occupata nella lista
*/

void elimina_mulipli_pos(Linked_List<int> &lista){
    Linked_List<int>::position pos = lista.begin();
    
    int count_p = 1;

    while(!lista.end(pos)){
        
        if(lista.read(pos) % count_p == 0){

           cout<<endl<<lista.read(pos)<<" da eliminare ";

           // salviamo la posizione da eliminare
           Linked_List<int>::position temp_pos = pos;

           pos = lista.next(pos);
           lista.erase(temp_pos);
           
        }else{
           pos = lista.next(pos);
        }

        count_p++;
        
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------