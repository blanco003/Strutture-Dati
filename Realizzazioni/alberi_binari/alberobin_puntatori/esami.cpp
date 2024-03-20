#include <iostream>
#include "Albero.h"
#include "./strutture_appoggio/single_linked_list.h"
#include <vector>

using namespace std;

//-------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA : ✔

    scrivere la funzione processa_pari che prenda in input un albero binario e:
    -crei una lista;
    -visiti l'albero (con una strategia a scelta) e aggiunga alla lista i valori pari contenuti nell'albero;
    -restituisca la lista
    Si crei dunque il main che crea l'albero di interi, chiama la funzione con l'albero in input e stampi la lsita
*/

void inVisita (const BinAlbero<int> &T, BinAlbero<int>::Nodo radice, Linked_List<int> &lista){
    // visita del sottoalbero sinistro
    if(!T.sinistroVuoto(radice))
        inVisita(T,T.figlioSinistro(radice),lista);

    // esamina nodo : se pari inseriscilo nella lista
    if(T.leggiNodo(radice) %2 ==0 )
        lista.insert(T.leggiNodo(radice),lista.begin());
    
    // visita del sottoalvbero destro
    if(!T.destroVuoto(radice))
        inVisita(T,T.figlioDestro(radice),lista);    
}

Linked_List<int> processa_pari(BinAlbero<int> &T){
    Linked_List<int> lista;
    if(!T.binAlberoVuoto()){
        inVisita(T,T.binRadice(),lista);
    }
    return lista;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/*  TRACCIA: ✔

    scrivere una funzione trova_comuni che prenda in input 2 alberi binari, copi in una lista gli elementi
    presenti in entrambi gli alberi e restituisca tale lista. Utilizzare una tecnica di visita a scelta per 
    individuare tali elementi

*/

bool check(const BinAlbero<int> &B2,BinAlbero<int>::Nodo u,int elemento){
    // visita sottoalbero sinitro del secondo albero
    if(!B2.sinistroVuoto(u)){
        if(check(B2,B2.figlioSinistro(u),elemento)){
            return true;
        }   
    }

    // esamina nodo : se uguale al valore da cercare restituisce true
    if(B2.leggiNodo(u) == elemento){
       return true;
    }

    // visita sottoalbero destro del secondo albero
    if(!B2.destroVuoto(u)){ 
        if(check(B2,B2.figlioDestro(u),elemento)){
            return true;
        }
    }

    return false;

}

void simmetrica(const BinAlbero<int> &B1,const BinAlbero<int> &B2,BinAlbero<int>::Nodo u,Linked_List<int> &list){
    // visita sottoalbero sinitro del primo albero
    if(!B1.sinistroVuoto(u)){
        simmetrica(B1,B2,B1.figlioSinistro(u),list);
    }

    // esamina nodo : controlliamo se nel secondo albero è presente il nodo corrente
    if(check(B2,B2.binRadice(),B1.leggiNodo(u))){
        list.insert(B1.leggiNodo(u),list.begin());
    }

        
    // visita sottoalbero destro del primo albero
    if(!B1.destroVuoto(u)){
        simmetrica(B1,B2,B1.figlioDestro(u),list);
    }
}

Linked_List<int> trova_comuni(const BinAlbero<int> &B1,const BinAlbero<int> &B2){
    Linked_List<int> list;
    if(!B1.binAlberoVuoto() && !B2.binAlberoVuoto()){
        simmetrica(B1,B2,B1.binRadice(),list);
    }
    return list;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   scrivere la funzione travasa che prenda in input solo un albero binario e,
   tramite una invisita copi tutti i valori pari dell'albero in una lista e la restituisca

*/

void invisita(const BinAlbero<int> &T, BinAlbero<int>::Nodo radice, Linked_List<int> &lista){

    // visita sottoalbero sinitro 
    if(!T.sinistroVuoto(radice))
        invisita(T,T.figlioSinistro(radice),lista);

    // esamina nodo: se pari inseriscilo nella lista
    if(T.leggiNodo(radice) %2 == 0 )
        lista.insert(T.leggiNodo(radice),lista.begin());
    
    // visita sottoalbero detro
    if(!T.destroVuoto(radice))
        invisita(T,T.figlioDestro(radice),lista);    
}

Linked_List<int> travasa(BinAlbero<int> &T){
    Linked_List<int> lista;
    if(!T.binAlberoVuoto()){
        inVisita(T,T.binRadice(),lista);
    }
    return lista;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   scrivere la funzione trasforma che prenda in input un albero binario, e tramite una visita simmetrica:
   - stampi il valore corrente del nodo visitato
   - se il nodo ha al più un figlio, ne incrementi il valore

   la funzione trasforma deve restituire la somma dei valori degli elementi aggioranti dell'albero

*/

void visitaSimmetrica(BinAlbero<int> &T, BinAlbero<int>::Nodo nodo,int &sum){

    // visita sottoalbero sinitro 
    if(!T.sinistroVuoto(nodo)){
        visitaSimmetrica(T,T.figlioSinistro(nodo),sum);
    }

    // esamino il nodo : stampalo, se ha al piu un figlio, ovvero se entrambi sono nulli o solo uno dei due è nullo, incrementa il suo valore
    cout<<"Nodo corrente : "<<T.leggiNodo(nodo)<<endl;
    if( ( (T.sinistroVuoto(nodo) && !T.destroVuoto(nodo)) ||  (!T.sinistroVuoto(nodo) && T.destroVuoto(nodo)) ) || (T.sinistroVuoto(nodo) && T.destroVuoto(nodo))){
        T.scriviNodo(nodo,T.leggiNodo(nodo)+1);
        sum += T.leggiNodo(nodo);
    }
    
    // visita sottoalbero destro
    if(!T.destroVuoto(nodo)){
        visitaSimmetrica(T,T.figlioDestro(nodo),sum);
    }    
}

int trasforma(BinAlbero<int> &T){
    int sum = 0;
    if(!T.binAlberoVuoto()){
        visitaSimmetrica(T,T.binRadice(),sum);
    }
    return sum;
}


//---------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔ 

   MEDIA_LIVELLI:
   Dato un albero binario che ha valori in R, scrivere una funzione che restituisca un vettore, dove l'elemento i-esimo
   corrisponde alla media dei nodi al livello i
*/

/* variabili usate:
   - livello : rapprenta il livello corrente analizzato
   - somme/medie : contiene momentaneamente la somma dei nodi di livello uguale, ed infine la media di essi
   - numNodi : contiene il numero di nodi all'i-esimo livello
*/

void media_livelli(BinAlbero<double> T, BinAlbero<double>::Nodo n, vector<double> &somme, vector<int> &numNodi, int livello) {

    // esaminiamo il sotto albero sinistro
    if(!T.sinistroVuoto(n)){
         media_livelli(T, T.figlioSinistro(n), somme, numNodi, livello+1);
    }   

    // esaminiamo nodo

    // inizialiazziamo lo spazio necessario a contenere il nodo in esame
    while (somme.size() <= livello) {
        somme.push_back(0);
        numNodi.push_back(0);
    }
    somme[livello] += T.leggiNodo(n);
    numNodi[livello]++;

    // esaminiamo il sotto albero destro
    if(!T.destroVuoto(n)){
         media_livelli(T, T.figlioDestro(n), somme, numNodi, livello+1);
    }   

}

vector<double> media_livelli_temp(BinAlbero<double> T){

    vector<double> medie;

    if (T.binAlberoVuoto()) {
        return medie;
    }

    vector<double> somme; // contiene temporaneamente le somme dell'i-esimo livello 
    vector<int> numNodi;  // contiene il numero di nodi dell'i-esimo livello
    
    media_livelli(T, T.binRadice(), somme, numNodi, 0); // 0 rappresenta il livello corrente
    
    // per ogni elemento i-esimo calcoliamo la sua media
    for (int i = 0; i < somme.size(); ++i) {
        if (numNodi[i] > 0) {
            medie.push_back(somme[i] / numNodi[i]);
        } else {
            medie.push_back(0);
        }
    }
    
    return medie;
}

/*
int main(){
    BinAlbero<double> T;
    BinAlbero<double>::Nodo radice = new Cella<double>;

    //inserimento radice
    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),0.3);

    //inserimento figlio sinistro e destro della radice
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),2.1);
    T.scriviNodo(T.figlioDestro(T.binRadice()),3.4);
    

    radice = T.figlioSinistro(T.binRadice()); // la radice è ora il figlio sinistro della radice di T

    //inserimento figlio sinistro e destro del figlio sinistro della radice di T
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),8.2);
    T.scriviNodo(T.figlioDestro(radice),4.7);   


     
    radice = T.figlioDestro(T.binRadice()); // la radice è ora il figlio destro della radice di T

    //inserimento figlio destro del figlio destro della radice di T
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),1.9);
    T.scriviNodo(T.figlioDestro(radice),2.4);    

    T.visitaAmpiezza(T.binRadice());
    
    

    vector<double> res;
    res = media_livelli_temp(T);

    cout<<endl<<"Media livelli : ";
    for(int i =0;i<res.size();i++){
        cout<<res[i]<<" ";
    }

}
*/

//-------------------------------------------------------------------------------------------------------------------------------------------


/* TRACCIA: ✔

    Scrivere la funzione trasforma_in_pari che prenda in input un albero binario e, tramite una visita simmetrica:
    - stampi il valore corrente del nodo visitato;
    - lo aggiorni, incrementandone il valore se il valore corrente è dispari;
    - se il nodo è stato aggiornato, stampi il nuovo valore.
    La funzione trasforma_in_pari deve restituire il numero di aggiornamenti effettuati.
*/

void visita_simmetrica(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count){

    // visita sottoalbero sinistro
    if(!T.sinistroVuoto(n)){
        visita_simmetrica(T,T.figlioSinistro(n),count);
    }

    // esamina nodo : stampalo, se il valore è dispari incrementalo e ristampalo
    cout<<endl<<"Nodo visitato : "<<T.leggiNodo(n);
    if(T.leggiNodo(n)%2 != 0){
        count++;
        T.scriviNodo(n,T.leggiNodo(n)+1);
        cout<<endl<<"Nodo incrementato : "<<T.leggiNodo(n);
    }

    // visita del sottoalbero destro
    if(!T.destroVuoto(n)){
        visita_simmetrica(T,T.figlioDestro(n),count);
    }
}

int trasforma_in_pari(BinAlbero<int> &T){
    int count = 0;
    visita_simmetrica(T,T.binRadice(),count);
    return count;
}

//-------------------------------------------------------------------------------------------------------------------------------------------


/* TRACCIA: ✔

    Scrivere la funzione trasforma_e_somma che prenda in input un albero binario e, tramite una previsita:
    - stampi il valore corrente del nodo visitato;
    - lo aggiorni, incrementandone il valore, se il valore corrente è pari.
    La funzione trasforma_e_somma deve restituire la somma degli elementi dell’albero aggiornato

*/

void pre_visita(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &sum){

    //esamina nodo
    cout<<endl<<"Nodo visitato : "<<T.leggiNodo(n);
    if(T.leggiNodo(n) %2 ==0){
        T.scriviNodo(n,T.leggiNodo(n)+1);
        sum += T.leggiNodo(n);
    }

    if(!T.sinistroVuoto(n)){
        pre_visita(T,T.figlioSinistro(n),sum);
    }

    if(!T.destroVuoto(n)){
        pre_visita(T,T.figlioDestro(n),sum);
    }
}

int trasforma_e_somma(BinAlbero<int> &T){
    int sum = 0;
    pre_visita(T,T.binRadice(),sum);
    return sum;
}

//-------------------------------------------------------------------------------------------------------------------------------------------


/* -TRACCIA ASD: ✔

    1) int odd(bintree<int> &T,int k) : calcola e restituisce il numero di nodi di livello k il cui valore è dispari.
    2) int even_leafs(bintree<int> &T) : calcola e restituisce il numero di foglie il cui valore è pari.
    3) int leafs_with_parent(bintree<int> &T) : calcola e restituisce il numero di foglie che hanno come genitore un nodo il cui valore è pari.

*/

void esplora_odd(BinAlbero<int> &T, BinAlbero<int>::Nodo n,int livello_corrente,int k,int &count){
    // esplora sottoalbero sinistro di n
    if(!T.sinistroVuoto(n)){
        esplora_odd(T,T.figlioSinistro(n),livello_corrente+1,k,count);
    }

    // esamina nodo n
    if((livello_corrente == k) && T.leggiNodo(n)%2 != 0){
        count++;
    }

    // esplora sottoalbero destro di n
    if(!T.destroVuoto(n)){
        esplora_odd(T,T.figlioDestro(n),livello_corrente+1,k,count);
    }    
}

int odd(BinAlbero<int> &T,int k){
    int count = 0;
    int livello_corrente = 0;
    esplora_odd(T,T.binRadice(),livello_corrente,k,count);    
    return count;
}

void esplora_even_leafs(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count){
    // esplora sottoalbero sinistro di n
    if(!T.sinistroVuoto(n)){
        esplora_even_leafs(T,T.figlioSinistro(n),count);
    }

    // esamina nodo n
    if(T.sinistroVuoto(n) && T.destroVuoto(n) && T.leggiNodo(n)%2 == 0){
        count++;
    }

    // esplora sottoalbero destro di n
    if(!T.destroVuoto(n)){
        esplora_even_leafs(T,T.figlioDestro(n),count);
    }     
}

int even_leafs(BinAlbero<int> &T){
    int count = 0;
    esplora_even_leafs(T,T.binRadice(),count);
    return count;
}

void esplora_leafs_with_parent(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count){
    // esplora sottoalbero sinistro di n
    if(!T.sinistroVuoto(n)){
        esplora_leafs_with_parent(T,T.figlioSinistro(n),count);
    }

    // esamina nodo n
    if(T.sinistroVuoto(n) && T.destroVuoto(n) && T.leggiNodo(T.binPadre(n))%2 == 0){
        count++;
    }

    // esplora sottoalbero destro di n
    if(!T.destroVuoto(n)){
        esplora_leafs_with_parent(T,T.figlioDestro(n),count);
    }     
}

int leafs_with_parent(BinAlbero<int> &T){
    int count = 0;
    esplora_leafs_with_parent(T,T.binRadice(),count);
    return count;
}


//-------------------------------------------------------------------------------------------------------------------------------------------


/* TRACCIA ASD:
    -Dato un albero binario di n nodi contare i sottoalberi che hanno somma dei nodi pari ad un intero k. Esempio:

             0
           /   \
         -6      2
           \    /  \
           11  -4  7
    Output : 4

*/
int sum_sub_tree(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &sum_sub){
    if(!T.sinistroVuoto(n)){
        sum_sub_tree(T,T.figlioSinistro(n),sum_sub);
    }

    // esamina nodo
    sum_sub += T.leggiNodo(n);
    
    if(!T.destroVuoto(n)){
        sum_sub_tree(T,T.figlioDestro(n),sum_sub);
    }
}

void esplora_test(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int k,int &count){
    if(!T.sinistroVuoto(n)){
        esplora_test(T,T.figlioSinistro(n),k,count);
    }

    // esamina nodo
    int sub_sum = 0;
    sum_sub_tree(T,n,sub_sum);
    cout<<"\nSomma del sottoalbero radicato in  "<<T.leggiNodo(n)<<" = "<<sub_sum;
    if(sub_sum == k){
        count++;
    }
    
    if(!T.destroVuoto(n)){
        esplora_test(T,T.figlioDestro(n),k,count);
    }
}


int esplora_test(BinAlbero<int> &T,int k){
    int count = 0;
    if(!T.binAlberoVuoto()){
        esplora_test(T,T.binRadice(),k,count);
    }
    return count;
}


/*
int main(){

    BinAlbero<int> T;
    BinAlbero<int>::Nodo radice = new Cella<int>;

    //inserimento radice
    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),0);

    //inserimento figlio sinistro e destro della radice
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),-6);
    T.scriviNodo(T.figlioDestro(T.binRadice()),2);
    

    radice = T.figlioSinistro(T.binRadice()); // la radice è ora il figlio sinistro della radice di T

  
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioDestro(radice),11);   

    radice = T.figlioDestro(T.binRadice());
      
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),-4);
    T.scriviNodo(T.figlioDestro(radice),7);   

   

    cout<<"BFS : "; T.visitaAmpiezza(T.binRadice());
    cout<<"\nDFS : "; T.visitaPreordine(T.binRadice());

    cout<<"\nSum all nodes : \n";
    sum_of_subtrees(T,T.binRadice());

}
*/
//-------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA ASD: ✔
    1) int d3(bintree<int> &T, int k) : calcola e restituisce il numero di nodi di livello k il cui valore è divisibile per 3.
    2) int lp(bintree<int> &T) : calcola e restituisce il numero di foglie il cui valore è pari.
    3) int l2p(bintree<int> &T) : calcola e restituisce il numero di foglie che hanno come genitore un nodo il cui valore è un multiplo di 5.

*/

void esplora_d3(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int livello_corrente,int livello_input,int &count){

    // esplora sottoalbero sinistro con lo stesso metodo
    if(!T.sinistroVuoto(n)){
        esplora_d3(T,T.figlioSinistro(n),livello_corrente+1,livello_input,count);
    }

    // esamina nodo : controllare se il livello corrente è quello richiesto e se il valore del nodo è divisibile per 3
    if(livello_corrente == livello_input && T.leggiNodo(n) %3 == 0){
        count++;
    }

    // esplora sottoalbero destro con lo stesso metodo
    if(!T.destroVuoto(n)){
        esplora_d3(T,T.figlioDestro(n),livello_corrente+1,livello_input,count);
    }
}

int d3(BinAlbero<int> &T, int k){
    int count = 0;
    if(!T.binAlberoVuoto()){
        esplora_d3(T,T.binRadice(),0,k,count);    // 0 rappresenta il livello corrente della radice
    }
    return count;
}

void esplora_lp(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count){
    
    // esplora sottoalbero sinistro con lo stesso metodo
    if(!T.sinistroVuoto(n)){
        esplora_lp(T,T.figlioSinistro(n),count);
    }

    // esamina nodo : controllare se il nodo è una foglia con valore pari
    if( (T.sinistroVuoto(n) && T.destroVuoto(n)) && T.leggiNodo(n) %2 == 0){
        count++;
    }

    // esplora sottoalbero destro con lo stesso metodo
    if(!T.destroVuoto(n)){
        esplora_lp(T,T.figlioDestro(n),count);
    }    
}

int lp(BinAlbero<int> &T){
    int count = 0;
    if(!T.binAlberoVuoto()){
        esplora_lp(T,T.binRadice(),count);
    }
    return count;
}

void esplora_l2p(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count){
    
    // esplora sottoalbero sinistro con lo stesso metodo
    if(!T.sinistroVuoto(n)){
        esplora_l2p(T,T.figlioSinistro(n),count);
    }

    // esamina nodo : controllare se il nodo è una foglia con valore pari
    if( (T.sinistroVuoto(n) && T.destroVuoto(n)) && T.leggiNodo(T.binPadre(n)) %5 == 0){
        count++;
    }

    // esplora sottoalbero destro con lo stesso metodo
    if(!T.destroVuoto(n)){
        esplora_l2p(T,T.figlioDestro(n),count);
    }    
}

int l2p(BinAlbero<int> &T){
    int count = 0;
    if(!T.binAlberoVuoto()){
        esplora_l2p(T,T.binRadice(),count);
    }
    return count;
}

//-------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

    -Dato un albero binario T di nodi con valore intero ed un intero k scrivere una funzione che
    restituisce la somma dei valori di tutte le foglie che si trovano ad una profondità maggiore di k

*/

void somma_foglie_maggiori_k(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int livello_corrente, int profondita,int &sum){

    // esamina sotto alebero di sinistra
    if(!T.sinistroVuoto(n)){
         somma_foglie_maggiori_k(T,T.figlioSinistro(n),livello_corrente+1,profondita,sum);
    }

    // esamina nodo
    cout<<"\nEsamino nodo : "<<T.leggiNodo(n)<< " al livello : "<<livello_corrente;
    if((livello_corrente > profondita) && (T.sinistroVuoto(n) && T.destroVuoto(n))){
        sum += T.leggiNodo(n);
        cout<<"\nSomma il nodo : "<<T.leggiNodo(n);
    }

    // esamina sotto alebero di destra
    if(!T.destroVuoto(n)){
         somma_foglie_maggiori_k(T,T.figlioDestro(n),livello_corrente+1,profondita,sum);
    }
}

int somma_foglie_maggiori_k(BinAlbero<int> &T,int profondita){
    int sum = 0;
    if(!T.binAlberoVuoto()){
        somma_foglie_maggiori_k(T,T.binRadice(),0,profondita,sum); // 0 rappresenta il livello corrente della radice
    }
    return sum;
}

int main(){
    BinAlbero<int> T;
    BinAlbero<int>::Nodo radice = new Cella<int>;

    //inserimento radice
    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),0);

    //inserimento figlio sinistro e destro della radice
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),-6);
    T.scriviNodo(T.figlioDestro(T.binRadice()),2);
    

    radice = T.figlioSinistro(T.binRadice()); // la radice è ora il figlio sinistro della radice di T

  
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioDestro(radice),11);   

    radice = T.figlioDestro(T.binRadice());
      
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),-4);
    T.scriviNodo(T.figlioDestro(radice),7);   

   

    cout<<"BFS : "; T.visitaAmpiezza(T.binRadice());
    cout<<"\nDFS : "; T.visitaPreordine(T.binRadice());

    cout<<"\nSum all nodes :";
    int c = esplora_test(T,5);
    cout<<"\nCount sum sub tree : "<<c;
}