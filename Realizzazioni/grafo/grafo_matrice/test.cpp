#include "GrafoMat.h"
#include "./strutture_appoggio/list_vector.h"
#include "./strutture_appoggio/codavt.h"
#include <string>

using namespace std;


void temp_bfs(GrafoMat<int,int> &g, GrafoMat<int,int>::Nodo n){ 
    Coda<GrafoMat<int,int>::Nodo> c;
    c.inCoda(n);

    while(!c.codaVuota()){
        NodoG u = c.leggiCoda();
        c.fuoriCoda();

        if(g.leggi_temp_stato(u)==false){
            g.scrivi_temp_stato(u,true);
            cout<<endl<<"Esamino nodo ("<<g.leggiEtichetta(u)<<") e ora e' marcato con "<<g.leggi_temp_stato(u);
        }
        

        GrafoMat<int,int>::ListaNodi adj = g.Adiacenti(u);
        GrafoMat<int,int>::ListaNodiPos pos = adj.begin();

        while(!adj.end(pos)){

            GrafoMat<int,int>::Nodo v = *(adj.read(pos));

            if(g.leggi_temp_stato(v)==false){
                c.inCoda(v);
            }else{
                cout<<endl<<"Nodo ("<<g.leggiEtichetta(v)<<") gia visitato";
            }

            pos = adj.next(pos);
        }

    }

}


void temp_dfs(GrafoMat<int,int> &g, GrafoMat<int,int>::Nodo n){

    g.scrivi_temp_stato(n,true);
	cout<<endl<<"Esamino nodo ("<<g.leggiEtichetta(n)<<") e ora e' marcato con "<<g.leggi_temp_stato(n);
	

	GrafoMat<int,int>::ListaNodi lista_adj = g.Adiacenti(n);
	GrafoMat<int,int>::ListaNodiPos pos = lista_adj.begin();

	while(!lista_adj.end(pos)){

		GrafoMat<int,int>::Nodo nodo = *(lista_adj.read(pos));

        if(g.leggi_temp_stato(nodo)==false){
            temp_dfs(g,nodo);
        }else{
            cout<<endl<<"Nodo ("<<g.leggiEtichetta(nodo)<<") gia visitato";
        }
		pos = lista_adj.next(pos);
		

	}
}

/*

void set_all_states(GrafoMat<int,int> &g){

    GrafoMat<std::string, int>::ListaNodi nodiList = g.list_nodi();
	GrafoMat<std::string, int>::ListaNodiPos pos_list = nodiList.begin();

	while(!nodiList.end(pos_list)){
		NodoG nodo = *(nodiList.read(pos_list));
        g.scrivi_temp_stato(nodo,false);
		pos_list = nodiList.next(pos_list);
	}
    return;
}

}*/


int main() {
    // Create a graph using GrafoMat
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
    grafo.insNodo(n8);



	grafo.scriviEtichetta(n1,0);
	grafo.scriviEtichetta(n2,1);
	grafo.scriviEtichetta(n3,2);
	grafo.scriviEtichetta(n4,3);
	grafo.scriviEtichetta(n5,4);
    grafo.scriviEtichetta(n6,5);
    grafo.scriviEtichetta(n7,6);
    grafo.scriviEtichetta(n8,7);

/*
    grafo.scrivi_temp_stato(n1,false);
    grafo.scrivi_temp_stato(n2,false);
    grafo.scrivi_temp_stato(n3,false);
    grafo.scrivi_temp_stato(n4,false);
    grafo.scrivi_temp_stato(n5,false);
    grafo.scrivi_temp_stato(n6,false);
    grafo.scrivi_temp_stato(n7,false);
    grafo.scrivi_temp_stato(n8,false);
*/


    // Add edges
    grafo.insArco(n1, n2, 10);
    grafo.insArco(n1, n3, 15);
    grafo.insArco(n2, n4, 20);
    grafo.insArco(n3, n4, 25);
    grafo.insArco(n4, n5, 30);
    grafo.insArco(n4, n6, 35);
    grafo.insArco(n5, n7, 40);
    grafo.insArco(n3, n8, 45);
    grafo.insArco(n6, n8, 50);

    grafo.set_all_states(); // setta tutti gli stati dei nodi a falsi, ovvero non visitati

    cout<<"leggi peso (3,4) :"<<grafo.leggiPeso(n4,n5)<<endl;

    // Print the number of nodes and edges
    std::cout << "Number of nodes: " << grafo.numNodi() << std::endl;
    std::cout << "Number of edges: " << grafo.numArchi() << std::endl;

	
    cout<<endl<<"----------------------------------------------"<<endl;
// Display nodes adjacent to a specific node
GrafoMat<std::string, int>::ListaNodi adiacenti = grafo.Adiacenti(n1);
GrafoMat<std::string, int>::ListaNodiPos pos = adiacenti.begin();
std::cout << "Nodes adjacent to Node 1: ";
int count = 0;
while (!adiacenti.end(pos)) {
    NodoG* nodo = adiacenti.read(pos);
    std::cout << grafo.leggiEtichetta(*nodo) << " ";
    count++;
    pos = adiacenti.next(pos);
}

std::cout << "\ncount adj = " << count;
cout<<endl<<"----------------------------------------------";

    // Display labels of nodes
    GrafoMat<std::string, int>::ListaNodi nodiList = grafo.list_nodi();
	GrafoMat<std::string, int>::ListaNodiPos pos_list = nodiList.begin();
    std::cout << "\nNode labels: ";

	int c = 0;

	while(!nodiList.end(pos_list)){
		NodoG nodo = *(nodiList.read(pos_list));
		cout<<endl<<"Etichetta ("<<grafo.leggiEtichetta(nodo)<<"), visitato :"<<grafo.leggi_temp_stato(nodo);
		pos_list = nodiList.next(pos_list);
		c++;
	}

	cout<<"\ncount n = "<<c;

    cout<<"\n----------------------------------------------";

    cout<<"\nDFS : ";
    temp_dfs(grafo,n1);
    cout<<"\nfine dfs";


    cout<<"\n----------------------------------------------";

    grafo.set_all_states(); // dopo dfs risettiamo tutti gli stati


    cout<<"\nBFS : ";
    temp_bfs(grafo,n1);
    cout<<"\nfine bfs";
    cout<<"\n----------------------------------------------";
    return 0;
}