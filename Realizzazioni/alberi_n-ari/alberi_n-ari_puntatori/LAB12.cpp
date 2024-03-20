#include "AlberoN.h"
#include "./strutture_appoggio/codavt.h"

using namespace std;

/* LAB 12 : Alberi N-Ari

    • Realizzare la ADT Alberi n-ari mediante puntatori.
    • La profondità di un albero ordinato è il massimo livello delle sue foglie,
        implementare la funzione PROFONDITA che calcola la profondità di un albero T.
    • La largezza di un albero ordinato è il numero massimo di nodi che stanno tutti al medesimo livello,
        Implementare la funzione LARGHEZZA che calcola la larghezza di un albero T

*/

void esplora_depth(AlberoN<int> &T,AlberoN<int>::Nodo n,int depth,int &temp_max_depth){
    
    if(depth > temp_max_depth){
        temp_max_depth = depth;
    }

    if(!T.foglia(n)){
        AlberoN<int>::Nodo m = T.primoFiglio(n);
        while(!T.ultimoFratello(m)){
            esplora_depth(T,m,depth+1,temp_max_depth);
            m = T.fratelloSuccessivo(m);
        }
        esplora_depth(T,m,depth+1,temp_max_depth);
    }

}

int profondita(AlberoN<int> &T){
    if(T.alberoVuoto()){
        return -1;
    }
    
    int temp_max_depth = 0;   // rappresenta la profondita finale dell'albero
    int depth = 0;  // rappresenta l'altezza corrente dell'albero
    esplora_depth(T,T.Radice(),depth,temp_max_depth);
    return temp_max_depth;
}

int larghezza(AlberoN<int> &T){
    if(T.alberoVuoto()){
        return -1;
    }

    Coda<AlberoN<int>::Nodo> c;
	c.inCoda(T.Radice());

    int max_larghezza_temp = 1;  // se l'albero non è vuoto ha almeno larghezza 1 per la radice
    int num_nodi_livello_corrente = 1; // solo la radice
    int num_nodi_livello_successivo = 0;
   
    while(!c.codaVuota()){
        AlberoN<int>::Nodo m = c.leggiCoda();
        c.fuoriCoda();
        num_nodi_livello_corrente--;

        if(!T.foglia(m)){
            AlberoN<int>::Nodo figlio = T.primoFiglio(m);
            while(!T.ultimoFratello(figlio)){
                num_nodi_livello_successivo++;
                c.inCoda(figlio);
                figlio = T.fratelloSuccessivo(figlio);
            }
            c.inCoda(figlio);
            num_nodi_livello_successivo++;
        }

        if(num_nodi_livello_corrente == 0){
           
            if(max_larghezza_temp < num_nodi_livello_successivo){
                max_larghezza_temp = num_nodi_livello_successivo;
            }
            num_nodi_livello_corrente = num_nodi_livello_successivo;
            num_nodi_livello_successivo = 0;
        }
    }

    return max_larghezza_temp;

}

int main(){

	AlberoN<int> T;

	//inserimento radice
	T.insRadice(1);

	//inserimento figli della radice di T
	T.insPrimoFiglio(T.Radice(),4);
	T.insPrimoFiglio(T.Radice(),3);
	T.insPrimoFiglio(T.Radice(),2);


	T.insPrimoFiglio(T.primoFiglio(T.Radice()),6);
	T.insPrimoFiglio(T.primoFiglio(T.Radice()),5);

	T.insPrimoFiglio(T.primoFiglio(T.primoFiglio(T.Radice())),7);

	T.insPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice()))),9);
	T.insPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice()))),8);

	T.insPrimoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice())))),10);

	T.insPrimoFiglio(T.primoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice()))))),11);



	cout<<"DFS : ";
	T.preVisita(T.Radice());
	
	cout << endl<<"BFS : ";
	T.visitaAmpiezza(T.Radice());

	cout<< endl <<"Profondita : "<< profondita(T);
    cout<< endl <<"Larghezza : "<< larghezza(T);

	return 0;
}
