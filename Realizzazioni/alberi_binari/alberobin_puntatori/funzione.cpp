#include <iostream>
#include "Albero.h"

void esplora_foglie_al_livello(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int k,int lvl_corrente,int &count){
    // esplora, con lo stesso metodo, il sottoalbero sinistro se il figlio sinistro del nodo corrente non e' vuoto
    if(!T.sinistroVuoto(n)){
        esplora_foglie_al_livello(T,T.figlioSinistro(n),k,lvl_corrente+1,count);
    }

    // esamina nodo : se il nodo corrente n e' una foglia (entrambi i figli sono vuoti) e si trova al livello k incremento il count
       if(lvl_corrente == k && (T.sinistroVuoto(n) && T.destroVuoto(n)) ){
        count++;
    }

    // esplora, con lo stesso metodo, il sottoalbero destro se il figlio destro del nodo corrente non e' vuoto
    if(!T.destroVuoto(n)){
        esplora_foglie_al_livello(T,T.figlioDestro(n),k,lvl_corrente+1,count);
    }    
}

int foglie_al_livello(BinAlbero<int> &T,int k){
    int count = 0;
    if(!T.binAlberoVuoto()){
        esplora_foglie_al_livello(T,T.binRadice(),k,0,count); // 0 rappresenta il livello della radice
    }
    return count;
}

int main(){

    // creazione albero binario, e di un nodo chiamato radice per inserire i vari nodi
    BinAlbero<int> T;
    BinAlbero<int>::Nodo radice = new Cella<int>;

    //inserimento radice
    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),1);

    // ovviamente se l'albero non è vuoto ci saranno 0 foglie al livello 0

    //inserimento figlio sinistro e destro della radice
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),2);
    T.scriviNodo(T.figlioDestro(T.binRadice()),3);
    
    // figlio sinistro della radice foglia quindi ci aspettiamo 1 foglia (2) livello 1

    radice = T.figlioDestro(T.binRadice()); //radice è ora il figlio destro della radice di T
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),5);
    T.scriviNodo(T.figlioDestro(radice),6);   

    // non ci aspettiamo foglie di livello 2

    radice = T.figlioSinistro(T.figlioDestro(T.binRadice())); //radice è ora il figlio sinistro del figlio destro della radice dell'albero
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),7);
    T.scriviNodo(T.figlioDestro(radice),8);

    radice = T.figlioDestro(T.figlioDestro(T.binRadice())); //radice è ora il figlio sinistro del figlio destro della radice dell'albero
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),9);
    T.scriviNodo(T.figlioDestro(radice),10);

    // ci aspettiamo 4 foglie (7,8,9,10) di livello 3

    int count_foglie = foglie_al_livello(T,0);
    cout<<endl<<"Foglie al livello 0 : "<<count_foglie;

    count_foglie = foglie_al_livello(T,1);
    cout<<endl<<"Foglie al livello 1 : "<<count_foglie;

    count_foglie = foglie_al_livello(T,2);
    cout<<endl<<"Foglie al livello 2 : "<<count_foglie;

    count_foglie = foglie_al_livello(T,3);
    cout<<endl<<"Foglie al livello 3 : "<<count_foglie;

}