#ifndef _ALBEROBST_H_
#define _ALBEROBST_H_
#include <iostream>
using namespace std;

template<class T>
class BST;

template <class T>
class Node{
    public:
        friend class BST<T>;
        // costruttore
        Node(T valore): elemento(valore), left(NULL), right(NULL) {}

        T get_elemento(){
            return elemento;
        }

        void set_elemento(T _elemento){
            elemento = _elemento;
        }
    private:
        T elemento;
        Node<T> *left;
        Node<T> *right;
};


// BST class
template <class T>
class BST{

    public:
        // tipi 
        typedef Node<T>* Nodo;

        // costruttore
        BST();     

        // distruttore
        ~BST();

        // operatori
        Nodo radice() const;   // restuisce la radice dell'albero
        void inserisci(Nodo n, T elemento);
        bool bilanciato(Nodo n); 
        int  altezza(Nodo n);
        void cancella(Nodo n);
        Nodo  nodoMax();
        Nodo  nodoMin();

        // visite
        void inOrder(Nodo n);
        void preOrder(Nodo n);
        void postOrder(Nodo n);
        
    private:
         Nodo _root;   
};

template <class T>
BST<T>::BST(){
        _root = NULL;
}

template <class T>
typename BST<T>::Nodo BST<T>::radice() const{
        return _root;
}

template <class T>
void BST<T>::inserisci(Nodo n,T elemento){
        if (!n){
                n = new Node(elemento);           
                _root = n;           
        }else{
                if (elemento < n->elemento){
                        if (!n->left){
                                Nodo nodo_temp = new Node(elemento);
                                n->left = nodo_temp;
                        }else{
                                inserisci(n->left, elemento);
                        }
                }else{
                        if (!n->right){
                                Nodo nodo_temp = new Node(elemento);                         
                                n->right = nodo_temp;
                        }else{
                            inserisci(n->right, elemento);
                        } 
                }
        }
}

template <class T>
int BST<T>::altezza(Nodo n){
        if (!n)
                return 0;
        return 1 + max(altezza(n->left) , altezza(n->right));
}

template <class T>
bool BST<T>::bilanciato(Nodo n){
        if (!n)
                return false;
        int leftHeight = altezza(n->left);
        int rightHeight = altezza(n->right);

        if (abs(leftHeight - rightHeight) > 1)
                return false;
        return true;
}

template <class T>
typename BST<T>::Nodo BST<T>::nodoMax(){
        if (!_root){
                cout <<  " albero BST vuoto !" << endl;
                return NULL;
        }
        Nodo n = _root;
        while(n->right)
                n = n ->right;
        return n;
}

template <class T>
typename BST<T>::Nodo BST<T>::nodoMin(){
        if (!_root)
        {
                cout <<  " albero BST vuoto !" << endl;
                return NULL;
        }
        Nodo n = _root;
        while(n->left)
                n = n ->left;
        return n;
}

template <class T>
void BST<T>::cancella(Nodo n) {
        if (!n)
                return;

        Nodo curn = n;
        Nodo leftn = n->left;
        Nodo rightn = n->right;
        delete(curn);
        cancella(leftn);
        cancella(rightn);
}

template <class T>
BST<T>::~BST(){
        cancella(radice());
}

template <class T>
void BST<T>::inOrder(Nodo n){
        if (!n)
                return;
        inOrder(n->left);
        cout << n->elemento << " " ;
        inOrder(n->right);
}

template <class T>
void BST<T>::preOrder(Nodo n){
        if (!n)
                return;
        cout << n->elemento << " ";
        preOrder(n->left);
        preOrder(n->right);
}

template <class T>
void BST<T>::postOrder(Nodo n){
        if (!n)
                return;
        postOrder(n->left);
        postOrder(n->right);
        cout << n->elemento << " ";
}



#endif /* _ALBEROBST_H_ */