#include "GrafoMat.h"
#include "./strutture_appoggio/list_vector.h"
#include "vector"

using namespace std;

/* LAB 13: Grafi

    • implementare la procedura int inDegree(Node N), per grafi orientati, che restituisce il numero di archi entranti in N

    • implementare la procedura int outDegree(Node N), per grafi orientati, che restituisce il numero di archi uscenti da N

    • implementare la procedura double meanOutDegree(), per grafi orientati, che restituisce la media del numero di archi uscenti per ogni nodo del grafo

    • implementare la procedura findPath(Node S, Node D) che stabilisce se esiste un path dal nodo S al nodo D, e in caso positivo lo stampa a video

*/
int outDegree(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n){

    int count = 0;

    if(!G.vuoto()){
        GrafoMat<int,int>::ListaNodi adj = G.Adiacenti(n);
        GrafoMat<int,int>::ListaNodiPos pos = adj.begin();
        while(!adj.end(pos)){
            count++;
            pos = adj.next(pos);
        }
    }

    return count;
}


bool dfsPercorso(GrafoMat<int,int>& grafo,GrafoMat<int,int>::Nodo nodoCorrente,GrafoMat<int,int>::Nodo nodoArrivo,vector<int> percorso) {
    grafo.scrivi_temp_stato(nodoCorrente, true);

    percorso.push_back(grafo.leggiEtichetta(nodoCorrente));

    if (grafo.leggiEtichetta(nodoCorrente) == grafo.leggiEtichetta(nodoArrivo)) {
        // Stampa il percorso
       // cout << "\nPercorso trovato";
        for (int i=0;i<percorso.size();i++){
            cout <<percorso[i]<<" ";
        }
        return true;
    }

    GrafoMat<int,int>::ListaNodi adiacenti = grafo.Adiacenti(nodoCorrente);
    GrafoMat<int,int>::ListaNodiPos pos = adiacenti.begin();

    while (!adiacenti.end(pos)) {
        GrafoMat<int,int>::Nodo nodoSuccessivo = *(adiacenti.read(pos));

        if (!grafo.leggi_temp_stato(nodoSuccessivo)) {
            if (dfsPercorso(grafo, nodoSuccessivo, nodoArrivo, percorso)) {
                return true;
            }
        }

        pos = adiacenti.next(pos);
    }

    percorso.pop_back();

    return false;
}


bool percorsoTraNodi(GrafoMat<int,int>& grafo,GrafoMat<int,int>::Nodo nodoPartenza,GrafoMat<int,int>::Nodo nodoArrivo) {
    grafo.set_all_states(); // Imposta tutti gli stati a false prima di iniziare la ricerca
    vector<int> percorso;
    return dfsPercorso(grafo, nodoPartenza, nodoArrivo, percorso);
}


//restituisce la media del numero di archi uscenti per ogni nodo del grafo
void esplora_meanOutDegree(GrafoMat<int,int> &G, GrafoMat<int,int>::Nodo n){

}

void meanOutDegree(GrafoMat<int,int> &G, GrafoMat<int,int>::Nodo n){
    if(G.vuoto()){
        return;
    }

    G.set_all_states();
    esplora_meanOutDegree(G,n);
}

int main() {

    GrafoMat<int, int> grafo(10);

    // Add nodes
    NodoG n1(0), n2(1), n3(2), n4(3), n5(4), n6(5), n7(6), n8(7);

    grafo.insNodo(n1);
    grafo.insNodo(n2);
    grafo.insNodo(n3);
    grafo.insNodo(n4);
    grafo.insNodo(n5);
    grafo.insNodo(n6);
    grafo.insNodo(n7);



	grafo.scriviEtichetta(n1,1);
	grafo.scriviEtichetta(n2,2);
	grafo.scriviEtichetta(n3,3);
	grafo.scriviEtichetta(n4,4);
	grafo.scriviEtichetta(n5,5);
    grafo.scriviEtichetta(n6,6);
    grafo.scriviEtichetta(n7,7);


    // Add edges
    grafo.insArco(n1, n2, 1);
    grafo.insArco(n1, n3, 2);
    grafo.insArco(n3, n2, 4);

    grafo.insArco(n3, n5, 2);
    grafo.insArco(n2, n7, 3);

    grafo.insArco(n3, n4, 1);
    grafo.insArco(n4, n2, 2);
    grafo.insArco(n4, n6, 1);

 

    grafo.set_all_states(); // setta tutti gli stati dei nodi a falsi, ovvero non visitati

   

    // Print the number of nodes and edges
    cout << "Number of nodes: " << grafo.numNodi() << endl;
    cout << "Number of edges: " << grafo.numArchi() << endl;

   // cout<<"\n DFS : \n";
   // grafo.dfs(n1);

   // grafo.set_all_states();

    // cout<<"\n BFS : \n";
   // grafo.bfs(n1);

    cout<<"\nOutDegree (1) : "<<outDegree(grafo,n1);
    cout<<"\nOutDegree (3) : "<<outDegree(grafo,n3);
    cout<<"\nOutDegree (7) : "<<outDegree(grafo,n7);

    cout<<endl;

    bool trovato1 = percorsoTraNodi(grafo,n1,n7);
    cout<<"    finPath (1,7) : "<<trovato1;
    cout<<endl;

    bool trovato2 = percorsoTraNodi(grafo,n2,n5);
    cout<<"    finPath (2,5) : "<<trovato2;
cout<<endl;

    bool trovato3 = percorsoTraNodi(grafo,n1,n6);
    cout<<"   finPath (1,6) : "<<trovato3;
cout<<endl;
    bool trovato4 = percorsoTraNodi(grafo,n3,n7);
    cout<<"   finPath (3,7) : "<<trovato4;
cout<<endl;



}