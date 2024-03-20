#include "AlberoN.h"

using namespace std;

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
	
	/*
	cout << endl;
	T.postVisita(T.Radice());
	cout << endl;
	*/


	cout << endl<<"BFS : ";
	T.visitaAmpiezza(T.Radice());

	cout << endl<<"DFS con stampa livelli : ";
	T.dfs_con_stampa_livelli(T.Radice(),0);

	cout << endl<<"BFS con stampa livelli : ";
	T.bfs_con_stampa_livelli(T.Radice());

	cout<< endl <<"done";

	return 0;
}
