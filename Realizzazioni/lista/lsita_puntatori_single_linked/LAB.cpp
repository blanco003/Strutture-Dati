#include "single_linked_list.h"
using namespace std;


/* LAB 5:
    Implementare
    • una funzione int lunghezza(Lista) per calcolare la lunghezza di una lista;
    • una funzione void inverti(Lista &) in grado di invertire l'ordine di una lista L senza utilizzare una lista di supporto;
    • una funzione bool palindoma(Lista) che stabilisca se una lista è palindroma.
*/

int lunghezza(Linked_List<int> lista){
    int count = 0;
    Linked_List<int>::position pos = lista.begin();
    while(!lista.end(pos)){
        count++;
        pos = lista.next(pos);
    }
    return count;
}

void inverti(Linked_List<int> &lista){
    Linked_List<int>::position left;
    Linked_List<int>::position right;

    left = lista.begin();
    right = lista.begin();

    // trovo l'ultima posizione
    while(!lista.end(lista.next(right))){
        right = lista.next(right);
    }

    Linked_List<int>::value_type val;
    while(left != right && right != lista.previous(left)){
        val = lista.read(left);
        lista.write(lista.read(right),left);
        lista.write(val,right);
        left = lista.next(left);
        right = lista.previous(right);
    } 
}

bool palindoma(Linked_List<int> lista){
    Linked_List<int>::position left;
    Linked_List<int>::position right;

    left = lista.begin();
    right = lista.begin();

    // trovo l'ultima posizione
    while(!lista.end(lista.next(right))){
        right = lista.next(right);
    }    

    bool pal = true;

    while(left != right && right != lista.previous(left) && pal){
        if(lista.read(left) != lista.read(right)){
            pal = false;
        }
        
        left = lista.next(left);
        right = lista.previous(right);
    }

    return pal;
}

/* LAB 7:
    1) Sovraccaricare l'operatore != in modo che l'espressione x != y restituisca true se e solo se le due liste x e y sono diverse

    2) Definire e implementare nell'interfaccia i seguenti metodi:
        • clear(): rende la lista vuota

        • num_elements(p1, p2): calcola il numero di elementi compresi fra le posizioni p1 e p2

        • exchange(p1, p2): scambia l'elemento in posizione p1 con quello in posizione p2

        • move_min_max(): quando la lista è di elementi di tipo intero, sposta, nel modo più efficiente possibile, 
          il massimo in ultima posizione, e il minimo in prima posizione

        • Scrivere una funzione che elimini da una lista L1 tutti gli elementi presenti nella lista L2. 

    3)Implementare il metodo Lista::insertionSort che ordina la lista utilizzando l'algoritmo di ordinamento
       per inserzione (Nota: non cancellare ne creare nuovi nodi)
*/

bool operator!=(Linked_List<int> &L1,Linked_List<int> &L2){
    Linked_List<int>::position pos1 = L1.begin();
    Linked_List<int>::position pos2 = L2.begin();
    while(!L1.end(pos1) || !L2.end(pos2)){
        if(L1.read(pos1) != L2.read(pos2)){
            return true;
        }
        pos1 = L1.next(pos1);
        pos2 = L2.next(pos2);
    }
    if((L1.end(pos1) && !L2.end(pos2)) || !(L1.end(pos1) && L2.end(pos2))){
        return true;
    } 
    return false;
}


void clear(Linked_List<int> &lista){
    Linked_List<int>::position pos = lista.begin();
    Linked_List<int>::position temp_pos;
    while(!lista.end(pos)){
        temp_pos = pos;
        pos = lista.next(pos);
        lista.erase(temp_pos);
    }
}

int num_elements(Linked_List<int> &lista,Linked_List<int>::position p1,Linked_List<int>::position p2){

    bool checkp1 ,checkp2, prec; 
    checkp1 = checkp2 = prec = false; 

    // checkp1 e checkp2 indicano se le posizioni in input sono posizioni della lista
    // prec indica che p1 è stato trovato prima di p2

    Linked_List<int>::position ap = lista.begin();


    while(!lista.end(ap)){
        if( ap == p1){
            checkp1 = true;
            if(!checkp2){
                prec = true;
            }
        }

        if(ap == p2){
            checkp2 = true;
        }

        ap = lista.next(ap);
    }

    
    int count = 0;
    // se abbiamo trovato entrambe le posizioni e p1 viene prima di p2 contiamo quante posizioni ci sono nel mezzo
    if( checkp1 && checkp2 && prec){
        Linked_List<int>::position p = p1;
        count++;

        while(p != p2){
            count++;
            p = lista.next(p);
        }
    }

    return count;
}

void exchange(Linked_List<int> &lista,Linked_List<int>::position p1,Linked_List<int>::position p2){
    // diamo per scontato che le posizioni siano valide all'interno della lista
    Linked_List<int>::value_type val = lista.read(p1);
    lista.write(lista.read(p2),p1);
    lista.write(val,p2);
}


void move_min_max(Linked_List<int> &lista){
    Linked_List<int>::position min_pos, max_pos, iter, last_pos;
    int min, max;
    
    if(!lista.empty()){
        min = max = lista.read(lista.begin());
        min_pos = max_pos = lista.begin();

        iter = lista.next(lista.begin());
        while(!lista.end(iter)){
            
            if(lista.read(iter) > lista.read(max_pos)){
                max_pos = iter;
                max = lista.read(iter);
            }

            if(lista.read(iter) < lista.read(min_pos)){
                min_pos = iter;
                min = lista.read(iter);
            }

            last_pos = iter;
            iter = lista.next(iter);
        }

        //sfruttando l'operatore exchange definito in precedenza
        exchange(lista,lista.begin(),min_pos);
        exchange(lista,last_pos,max_pos);
    }
}


void remove_L2(Linked_List<int> &L1, Linked_List<int> L2){
    Linked_List<int>::value_type val;
    Linked_List<int>::position p1, p2;
    
    if(!L1.empty() && !L2.empty()){
        p1 = L1.begin();
        while(!L1.end(p1)){

            val = L1.read(p1);
            p2 = L2.begin();

            while(!L2.end(p2)){
                if(L2.read(p2) == val){
                    L1.erase(p1);
                    break;
                }
                p2 = L2.next(p2);
            }

            p1 = L1.next(p1);
        }
    }
}

int main(){
    Linked_List<int> lista1;
    lista1.insert(1,lista1.begin());
    lista1.insert(2,lista1.begin());
    lista1.insert(3,lista1.begin());
    lista1.insert(3,lista1.begin());
    lista1.insert(2,lista1.begin());
    lista1.insert(1,lista1.begin());

    cout<<"\nLista1 : "<<lista1;
    cout<<"\nLista1 Palindroma : "<<palindoma(lista1);
    cout<<endl;

    Linked_List<int> lista2;
    lista2.insert(1,lista2.begin());
    lista2.insert(2,lista2.begin());
    lista2.insert(3,lista2.begin());



    cout<<"\nLista2 : "<<lista2;
    inverti(lista2);
    cout<<"\nLista2 Reversed : "<<lista2;
     cout<<endl;

    bool diverse = lista1 != lista2;
    cout<<"\nOperatore !=  :"<<diverse;
     cout<<endl;

    //remove_L2(lista1,lista2);
    cout<<"\nLista1 Prima : "<<lista1;
    clear(lista1);
    cout<<"\nLista1 Dopo clear: "<<lista1;
    cout<<endl;
    


}
