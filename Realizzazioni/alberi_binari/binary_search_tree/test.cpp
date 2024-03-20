#include <iostream>
#include "bst.h"
using namespace std;

int main(){
    BST<int> T;
    T.inserisci(T.radice(),30);
    T.inserisci(T.radice(),50);
    T.inserisci(T.radice(),15);
    T.inserisci(T.radice(),20);
    T.inserisci(T.radice(),10);
    T.inserisci(T.radice(),40);
    T.inserisci(T.radice(),60);

    int h = T.altezza(T.radice());
    cout << "altezza : " << h << endl;

    BST<int>::Nodo mx = T.nodoMax();
    cout << "valore max : " << mx->get_elemento() << endl;

    BST<int>::Nodo mi = T.nodoMin();
    cout << "valore min : " << mi->get_elemento() << endl;

    if (T.bilanciato(T.radice()))
        cout << "albero BST bilanciato ! " << endl;
    else
        cout << "albero BST non bilanciato ! " << endl;

    cout << " Visita InOrdine : " << endl;
    T.inOrder(T.radice());
    cout << endl;
    cout << " Visita PreOrdine : " << endl;
    T.preOrder(T.radice());
    cout << endl;
    cout << " Visita PostOrdine : " << endl;
    T.postOrder(T.radice());
    cout << endl;

    return 0;
}