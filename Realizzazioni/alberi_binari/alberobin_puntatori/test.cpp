#include <iostream>
#include "Albero.h"
using namespace std;

int main(int argc, char *argv[]){

    BinAlbero<int> T;
    BinAlbero<int>::Nodo radice = new Cella<int>;

    //inserimento radice
    T.insBinRadice(radice);
    T.scriviNodo(T.binRadice(),1);

    //inserimento figlio sinistro e destro della radice
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(T.binRadice()),2);
    T.scriviNodo(T.figlioDestro(T.binRadice()),3);
    

    radice = T.figlioSinistro(T.binRadice()); // la radice è ora il figlio sinistro della radice di T

    //inserimento figlio sinistro e destro del figlio sinistro della radice di T
    T.insFiglioSinistro(radice);
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioSinistro(radice),4);
    T.scriviNodo(T.figlioDestro(radice),5);   

     
    radice = T.figlioDestro(T.binRadice()); // la radice è ora il figlio destro della radice di T

    //inserimento figlio destro del figlio destro della radice di T
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioDestro(radice),6);    

    radice = T.figlioDestro(T.figlioSinistro(T.binRadice()));
    T.insFiglioDestro(radice);
    T.scriviNodo(T.figlioDestro(radice),7);  
   
    cout << "BFS : " ;
    T.visitaAmpiezza(T.binRadice());
    cout << endl;

    cout << "DFS : " ;
    T.visitaPreordine(T.binRadice());
    cout << endl;

    cout << "DFS_CON_STAMPA_LIVELLI : " ;
    int livello_partenza = 0;
    T.dfs_con_stampa_livelli(T.binRadice(),livello_partenza);
    cout << endl;

    cout << "BFS_CON_STAMPA_LIVELLI : " ;
    T.bfs_con_stampa_livelli(T.binRadice());
    cout << endl;



    return EXIT_SUCCESS;
}