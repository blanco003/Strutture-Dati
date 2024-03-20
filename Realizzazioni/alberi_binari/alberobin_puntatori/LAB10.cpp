#include <iostream>
#include "Albero.h"

using namespace std;

/*  LAB 10: Alberi Binari

    Fornire in un file color_bin_tree.cpp la realizzazione in C++ delle funzioni riportate di seguito
    che operano su alberi binari. L'insieme dei valori ammissibili per l'etichetta dei nodi dell'albero è il
    seguente {rosso, verde, bianco}.

    • int level red(bintree &T): calcola e restituisce il numero di nodi di livello pari il cui
      valore è "rosso" e che hanno almeno un figlio il cui valore è "bianco";

    • int green leafs(bintree &T): calcola e restituisce il numero di foglie il cui valore è
      "verde";
*/

void esplora_level_red(BinAlbero<int> &T,BinAlbero<int>::Nodo n,int &count,int livello_corrente){

    if(!T.sinistroVuoto(n)){
        esplora_level_red(T,T.figlioSinistro(n),count,livello_corrente+1);
    }

    //esamina nodo : verifica se il livello è pari, se l'etichetta è rosso (0) e se ha almeno un figlio con etichetta bianca (2)
    if( (livello_corrente %2 ==0) && T.leggiNodo(n) == 0 && (!T.sinistroVuoto(n) || !T.destroVuoto(n))){
        count++;
    }


    if(!T.destroVuoto(n)){
        esplora_level_red(T,T.figlioDestro(n),count,livello_corrente+1);
    }
}

int level_red(BinAlbero<int> &T){

    if(T.binAlberoVuoto()){
        return 0;
    }

    int count = 0;
    esplora_level_red(T,T.binRadice(),count,0);  // 0 rappresenta il livello corrente, ovvero il livello della radice
    return count;
}

void esplora_green_leafs(BinAlbero<int> &T, BinAlbero<int>::Nodo n,int &count){

    if(!T.sinistroVuoto(n)){
        esplora_green_leafs(T,T.figlioSinistro(n),count);
    }

    // esamina nodo : controlliamo che sia foglia, ovvero che non abbia figli, e che l'etichetta sia verde (1)

    if(T.sinistroVuoto(n) && T.destroVuoto(n) && T.leggiNodo(n)==1){
        count++;
    }

    if(!T.destroVuoto(n)){
        esplora_green_leafs(T,T.figlioDestro(n),count);
    }
}

int green_leafs(BinAlbero<int> &T){

    if(T.binAlberoVuoto()){
        return 0;
    }

    int count = 0;
    esplora_green_leafs(T,T.binRadice(),count);
    return count;
}




int main(int argc, char *argv[]){


    BinAlbero<int> T;
    BinAlbero<int>::Nodo radice = new Cella<int>;

    //Assumo che 0 = "rosso", 1 = "verde", 2 = "bianco"

    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),1);

    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),0);
    T.scriviNodo(T.figlioDestro(T.binRadice()),2);
    

    radice = T.figlioSinistro(T.binRadice()); 
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),1);
    T.scriviNodo(T.figlioDestro(radice),1);   

     
    radice = T.figlioDestro(T.binRadice());
    T.insFiglioSinistro(radice); 
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),0);   
    T.scriviNodo(T.figlioDestro(radice),1);    

    radice = T.figlioDestro(T.figlioSinistro(T.binRadice()));
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),2);
    T.scriviNodo(T.figlioDestro(radice),1);  


    radice = T.figlioSinistro(T.figlioDestro(T.binRadice()));
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioDestro(radice),2);


    radice = T.figlioSinistro(T.figlioDestro(T.figlioSinistro(T.binRadice())));
    T.insFiglioSinistro(radice);
    T.scriviNodo(T.figlioSinistro(radice),0);

    radice = T.figlioSinistro(T.figlioSinistro(T.figlioDestro(T.figlioSinistro(T.binRadice()))));
    T.insFiglioSinistro(radice);
    T.scriviNodo(T.figlioSinistro(radice),2);

    
    cout << "\nBFS : " ;
    T.visitaAmpiezza(T.binRadice());
    cout << endl;

    cout << "DFS : " ;
    T.visitaPreordine(T.binRadice());
    cout << endl;

    cout << "green_leafs : "<<green_leafs(T);
    cout << endl;

    cout << "level_red : "<<level_red(T);
    cout << endl;



    return EXIT_SUCCESS;
}