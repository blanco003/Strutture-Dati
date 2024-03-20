#include "GrafoMat.h"
#include <string>
#include "./strutture_appoggio/codavt.h"
#include "./strutture_appoggio/list_vector.h"
#include "./strutture_appoggio/single_linked_list.h"

using namespace std;

/* TRACCIA : ✔
    Scrivere la funzione adiacenti_rilevanti(..) che prenda in input:
    - un grafo G
    - un nodo del grafo N
    - un intero k
    e restituisca la lista dei nodi adiacenti al nodo N avente somma dei pesi degli archi uscenti maggiore di k.
*/

Linked_List<char> adiacenti_rilevanti(GrafoMat<char,int> &G,GrafoMat<char,int>::Nodo n,int k){

    Linked_List<char> list;  // contenente l'output
    GrafoMat<char,int>::ListaNodi list_1; // contiene gli adiacenti di n
    GrafoMat<char,int>::ListaNodi list_2; // contiene gli adiacenti degli adiacenti di n
    

    GrafoMat<char,int>::ListaNodiPos pos1;
    GrafoMat<char,int>::ListaNodiPos pos2;

    list_1 = G.Adiacenti(n); // adiacenti al nodo in input n
    pos1 = list_1.begin();

    // scorriamo gli adiacenti ad n
    while(!list_1.end(pos1)){

        GrafoMat<char,int>::Nodo u = *(list_1.read(pos1)); // leggo i nodi adiacenti ad n, ed inserisco i nodi adiacenti agli adiacenti ad n in list2
       
        list_2 = G.Adiacenti(u); // lista dei nodi adiacenti agli adiacenti di n
        pos2 = list_2.begin();

        int somma = 0;

        // scorriamo gli adiacenti degli adiacenti di n
        while(!list_2.end(pos2)){

            GrafoMat<char,int>::Nodo v; // nodo della lista degli adiacenti degli adiacenti ad n
            v = *(list_2.read(pos2));

            somma += G.leggiPeso(u,v); // sommiamo i pesi degli archi uscenti da u

            if(somma > k){
                list.insert(G.leggiEtichetta(u),list.begin());
                break;
            }

            pos2 = list_2.next(pos2);
        }

        pos1 = list_1.next(pos1);
    }
    return list;
}


/*
int main() {

    GrafoMat<char, int> grafo(10);

    // Add nodes
    NodoG n1(0), n2(1), n3(2), n4(3), n5(4), n6(5), n7(6), n8(7);

    grafo.insNodo(n1);
    grafo.insNodo(n2);
    grafo.insNodo(n3);
    grafo.insNodo(n4);
    grafo.insNodo(n5);
    grafo.insNodo(n6);
    grafo.insNodo(n7);



	grafo.scriviEtichetta(n1,'A');
	grafo.scriviEtichetta(n2,'B');
	grafo.scriviEtichetta(n3,'C');
	grafo.scriviEtichetta(n4,'D');
	grafo.scriviEtichetta(n5,'E');
    grafo.scriviEtichetta(n6,'F');
    grafo.scriviEtichetta(n7,'G');


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

    cout<<"\n DFS : \n";
    grafo.dfs(n1);
    cout<<"\n BFS : \n";
    grafo.bfs(n1);


    Linked_List<char> res ;
    res = adiacenti_rilevanti(grafo,n1,3);
    Linked_List<char>::position pos = res.begin();
    cout<<"\n\nAdiacenti rilevanti di A con k = 3 : ";
    while(!res.end(pos)){
        cout<<res.read(pos)<<" ";
        pos = res.next(pos);
    }

    return 0;
}
*/

//----------------------------------------------------------------------------------------------------------------------------------

/*  TRACCIA: ✔
    Scrivere la funzione aggiorna_adiacenti(..) che prenda in input un grafo G e un nodo del grafo N
    e aggiorni gli adiacenti del nodo N, scrivendo al loro interno la somma dei pesi dei rispettivi archi
    uscenti.

*/


void aggiorna_adiacenti(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n){
  
  GrafoMat<int,int>::ListaNodi adiacenti = G.Adiacenti(n); // lista contenente gli adicenti ad n
  GrafoMat<int,int>::ListaNodi adiacenti_adiacenti; // lista che conterrà gli adiacenti degli adiacenti ad n

  GrafoMat<int,int>::ListaNodiPos pos1 = adiacenti.begin();

 // scorriamo gli adicenti ad n
  while(!adiacenti.end(pos1)){

        GrafoMat<int,int>::Nodo u = *(adiacenti.read(pos1)); // nodo generico adiacente ad n

        adiacenti_adiacenti = G.Adiacenti(u);

        GrafoMat<int,int>::ListaNodiPos pos2 = adiacenti_adiacenti.begin();

        int somma_pesi = 0; // conterra la somma dei pesi degli archi uscenti da u

        // scorriamo gli adiacenti degli adiacenti ad n
        while(!adiacenti_adiacenti.end(pos2)){

            GrafoMat<int,int>::Nodo v = *(adiacenti_adiacenti.read(pos2)); // nodo generico adiacente ad un adicente di n

            //contiamo i pesi degli archi uscenti di u
            somma_pesi += G.leggiPeso(u,v);

            pos2 = adiacenti_adiacenti.next(pos2);
        }

        G.scriviEtichetta(u,somma_pesi);

        pos1 = adiacenti.next(pos1);
  }

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione raggiungibili(… ) che prenda in input:
   - un grafo G
   - un nodo del grafo N
   - un intero k
   e restituisca la lista dei nodi distinti raggiungibili dal nodo N in al più k passi. 
*/

void visita_k_passi(GrafoMat<char,int> &G, GrafoMat<char,int>::Nodo &n,int num_passi_max,Linked_List<char> &lista,int num_passi_fatti){

    // controlliamo se abbiamo ancora passi a disposizione
    if(num_passi_fatti < num_passi_max){

        GrafoMat<char,int>::ListaNodi adiacenti = G.Adiacenti(n); // lista contenente gli adiacenti ad n
        GrafoMat<char,int>::ListaNodiPos pos = adiacenti.begin();

        // scorriamo gli adiacenti ad n
        while(!adiacenti.end(pos)){

            GrafoMat<char,int>::Nodo u = *(adiacenti.read(pos)); // nodo generico adiacente ad n

            // se non è già stato visitato, inseriamolo nella lista e impostiamolo come visitato
            if(G.leggi_temp_stato(u)==false){
                lista.insert(G.leggiEtichetta(u),lista.begin());
                G.scrivi_temp_stato(u,true);
            }

            // effettuaiamo la visita del nodo con lo stesso metodo, incrementando i passi fatti
            visita_k_passi(G,u,num_passi_max,lista,num_passi_fatti+1);

            pos = adiacenti.next(pos);
        }
    }

}

Linked_List<char> raggiungibili(GrafoMat<char,int> &G, GrafoMat<char,int>::Nodo &n, int k){
    G.set_all_states();
    Linked_List<char> lista;
    visita_k_passi(G,n,k,lista,0); // 0 rappresenta il numero di passi compiuti, ovviamente si parte fermi cioè 0
    return lista;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

/*

    -Implementare una classe in C++ che fornisca i seguenti metodi che operano sui grafi orientati.
    Ogni nodo del grafo è etichettato con il nome di uno dei seguenti colori: rosso,verde o bianco.
    
    1) sameColorPath(Node n1,Node n2) : restituisce true se esiste un path che collega il nodo n1 al nodo n2 e
       tutti i nodi presenti in tale path sono dello stesso colore, false altrimenti.

    2) uniformColorPath(Node n1,Node n2) : restituisce true se esiste un path checollega il nodo n1 al nodo n2 ed
       ogni nodo presente in tale path è etichettato con un colore diverso da quello con cui è etichettato il nodo precedente,
       false altrimenti.

*/

bool esplora_same_color(GrafoMat<string,int> &g,GrafoMat<string,int>::Nodo NodoCorrente,GrafoMat<string,int>::Nodo NodoArrivo,string colore){

    if(NodoCorrente.getId() == NodoArrivo.getId()){
        return true;
    }

    g.scrivi_temp_stato(NodoCorrente,true);

    GrafoMat<string,int>::ListaNodi adiacenti = g.Adiacenti(NodoCorrente);
    GrafoMat<string,int>::ListaNodiPos pos = adiacenti.begin();

    while(!adiacenti.end(pos)){
        GrafoMat<char,int>::Nodo u = *(adiacenti.read(pos));
        if(!g.leggi_temp_stato(u)){
            g.scrivi_temp_stato(u,true);
            if(g.leggiEtichetta(u) == colore){
                if(esplora_same_color(g,u,NodoArrivo,colore)){
                    return true;
                }
            }
        }
        pos = adiacenti.next(pos);
    } 

    return false;

}
    
bool sameColorPath(GrafoMat<string,int> &g,GrafoMat<string,int>::Nodo NodoPartenza,GrafoMat<string,int>::Nodo NodoArrivo){
   g.set_all_states();
   string colore;
   if(g.leggiEtichetta(NodoPartenza)==g.leggiEtichetta(NodoArrivo)){
    colore = g.leggiEtichetta(NodoPartenza);
    return esplora_same_color(g,NodoPartenza,NodoArrivo,colore);
   }
   return false;
}

bool eslpora_uniform_color(GrafoMat<string,int> &g,GrafoMat<string,int>::Nodo NodoCorrente,GrafoMat<string,int>::Nodo NodoArrivo,string colore_corrente){
    
    if(NodoCorrente.getId() == NodoArrivo.getId()){
        return true;
    }

    g.scrivi_temp_stato(NodoCorrente,true);

    GrafoMat<string,int>::ListaNodi adiacenti = g.Adiacenti(NodoCorrente);
    GrafoMat<string,int>::ListaNodiPos pos = adiacenti.begin();

    while(!adiacenti.end(pos)){
        GrafoMat<string,int>::Nodo u;
        u = *(adiacenti.read(pos));
        if(!g.leggi_temp_stato(u)){
            g.scrivi_temp_stato(u,true);
            if(g.leggiEtichetta(u) != colore_corrente){
                if(eslpora_uniform_color(g,u,NodoArrivo,g.leggiEtichetta(u))){
                    return true;
                }
            }
        }
        pos = adiacenti.next(pos);
    }

    return false;
}

bool uniformColorPath(GrafoMat<string,int> &g,GrafoMat<string,int>::Nodo NodoPartenza,GrafoMat<string,int>::Nodo NodoArrivo){
    g.set_all_states();
    return eslpora_uniform_color(g,NodoPartenza,NodoArrivo,g.leggiEtichetta(NodoPartenza));
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*
    TRACCIA: ✔

    -Implementare una classe in C++ che fornisca i seguenti metodi che operano su grafi orientati.
    Ogni nodo del grafo è etichettato con un valore intero.

    1) countSame(Node n1) : restituisce il numero di nodi raggiungibili da n1 e aventi la sua stessa etichetta.

    2) meanN2(Node n1) : restituisce la media dei valori delle etichette dei nodi raggiungibili da n1 con cammini di lunghezza 2
    
*/

void esplora_media_2(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n,int passi_fatti,double &media,int &num){
   


        GrafoMat<int,int>::ListaNodi adiacenti = G.Adiacenti(n);
        GrafoMat<int,int>::ListaNodiPos pos = adiacenti.begin();

        while(!adiacenti.end(pos)){
           
            GrafoMat<int,int>::Nodo u = *(adiacenti.read(pos));
             
             if(passi_fatti == 1){ // assunto che per cammino di lunghezza 2 voglia dire fare il primo passo(0) e il secondo (1)
                
                if(!G.leggi_temp_stato(u)){
                     G.scrivi_temp_stato(u,true);
                     num++;
                     media += G.leggiEtichetta(u);
                }
            }else{
                // continuiamo ad esplorare
                if(!G.leggi_temp_stato(u)){
                     G.scrivi_temp_stato(u,true);
                     esplora_media_2(G,u,passi_fatti+1,media,num);
                }
            }

            pos = adiacenti.next(pos);

        }

    
}

double meanN2(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n){
    G.set_all_states();
    double media = 0;
    int num = 0;
    esplora_media_2(G,n,0,media,num);
    cout<<"\n\nSomma : "<<media<<", num : "<<num;
    return media/num;
}

void esplora_count_same(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n,int valore,int &count){
    GrafoMat<int,int>::ListaNodi adiacenti = G.Adiacenti(n); // lista che contiene gli adiacenti ad n
    GrafoMat<int,int>::ListaNodiPos pos = adiacenti.begin();

    //impostiamo il nodo n come visitato
    G.scrivi_temp_stato(n,true);

    // controlliamo se il nodo ha la stessa etichetta da cercare
    if(G.leggiEtichetta(n)==valore){
        count++;
    }

    //scorriamo la lista dei nodi adiacenti ad n
    while(!adiacenti.end(pos)){

        GrafoMat<int,int>::Nodo u = *(adiacenti.read(pos)); // nodo generico adiacente ad n

        // se il nodo u non è già stato visitato effettuiamo la visita del nodo con lo stesso metodo
        if(!G.leggi_temp_stato(u)){
            G.scrivi_temp_stato(u,true);
            esplora_count_same(G,u,valore,count);
        }

        pos = adiacenti.next(pos);
    }

}

int countSame(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo n){
    G.set_all_states(); // impostiamo tutti i nodi come non visitati
    int count = 0;
    esplora_count_same(G,n,G.leggiEtichetta(n),count);
    return count;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------

/*  TRACCIA : ✔

    -Dato un grafo orientato i cui archi hanno peso 1 o –1, implementare un metodo in C++ che dati due nodi a e b 
    individui il numero di cammini da a a b tale che, gli archi nella sequenza corrispondente ad ogni cammino siano
    etichettati con 1. Inoltre fornire la media della lunghezza dei cammini individuati.

*/

void esplora_camminini_uno(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo corrente,GrafoMat<int,int>::Nodo arrivo,double &count,int lunghezza,double &media){

    if(G.leggiEtichetta(corrente)==G.leggiEtichetta(arrivo)){
        count++;
        media += lunghezza;
        cout<<"\nTrovato percorso di lunghezza : "<<lunghezza;
    }

    G.scrivi_temp_stato(corrente,true);

    GrafoMat<int,int>::ListaNodi adiacenti = G.Adiacenti(corrente);
    GrafoMat<int,int>::ListaNodiPos pos = adiacenti.begin();

    //scorriamo tutti i nodi adicenti al nodo corrente e se non sono stati gia visitati ed hanno peso 1 esploriamoli con la stessa visita
    while(!adiacenti.end(pos)){

        GrafoMat<int,int>::Nodo u = *(adiacenti.read(pos));
        if(!G.leggi_temp_stato(u)){
            G.scrivi_temp_stato(u,true);
            if(G.leggiPeso(corrente,u)==1){
                esplora_camminini_uno(G,u,arrivo,count,lunghezza+1,media);
            }
        }

        pos = adiacenti.next(pos);
    }

    G.scrivi_temp_stato(corrente,false);
}

double cammini_uno(GrafoMat<int,int> &G,GrafoMat<int,int>::Nodo partenza,GrafoMat<int,int>::Nodo arrivo){
    G.set_all_states();
    double count = 0;
    double media = 0;
    esplora_camminini_uno(G,partenza,arrivo,count,0,media);
    cout<<"\nNumero di percorsi trovati : "<<count;
    cout<<"\nMedia delle lunghezze trovate : "<<media/count;
    return count;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* 
    TRACCIA: ✔
    
    Dato un intero sum e due nodi a e b, determina se esiste un cammino semplice,
    ovvero senza nodi ripetuti e aventi le seguenti proprietà:  

    1) parte dal nodo a e termina sul nodo b
    2) la somma delle etichette dei nodi nella sequenza dei nodi del cammino è minore dell'intero sum dato in input

    bool sumPath(int sum, node a, node b);
*/

bool sumPath(GrafoMat<int,int> &G,int sum,GrafoMat<int,int>::Nodo current_node,GrafoMat<int,int>::Nodo final_node,int current_sum){

    cout<<"\nEsploro nodo "<<G.leggiEtichetta(current_node)<<" , somma corrrente : "<<current_sum;

    if(G.leggiEtichetta(current_node) == G.leggiEtichetta(final_node)){  
            if(current_sum < sum){
                return true;
            }
    }

    // impostiamo il nodo come visitato
    G.scrivi_temp_stato(current_node,true);

    // esploriamo gli adiacenti
    GrafoMat<int,int>::ListaNodi adiacenti = G.Adiacenti(current_node);
    GrafoMat<int,int>::ListaNodiPos pos = adiacenti.begin();

    while(!adiacenti.end(pos)){
        GrafoMat<int,int>::Nodo nodo = *(adiacenti.read(pos));
        // se il nodo non è gia stato visitato esploriamo il nodo con lo stesso metodo
        if(G.leggi_temp_stato(nodo) == false){
            // incrementiamo il costo del cammino
            current_sum += G.leggiEtichetta(nodo);
            if(sumPath(G,sum,nodo,final_node,current_sum)){
                return true;
            }
            // decrementiamo il costo del cammino quando torniamo al livello precedente
            current_sum -= G.leggiEtichetta(nodo);
        }
        pos = adiacenti.next(pos);
    }

    // se arriviamo alla fine e non abbiamo altri nodi da esplorare vuol dire che non esiste il percorso desiderato
    return false;
}

bool sumPath(GrafoMat<int,int> &G,int sum,GrafoMat<int,int>::Nodo a,GrafoMat<int,int>::Nodo b){
    if(G.vuoto()){
        return false;
    }
    G.set_all_states();
    return sumPath(G,sum,a,b,0);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){
    GrafoMat<int,int> g(10);
    GrafoMat<int,int>::Nodo n1(1),n2(2),n3(3),n4(4),n5(5),n6(6),n7(7),n8(8);

    g.insNodo(n1);
    g.insNodo(n2);
    g.insNodo(n4);
    g.insNodo(n3);
    g.insNodo(n5);
    g.insNodo(n6);
    g.insNodo(n7);
    g.insNodo(n8);

    g.scriviEtichetta(n1,1);
    g.scriviEtichetta(n2,2);
    g.scriviEtichetta(n3,3);
    g.scriviEtichetta(n4,4);
    g.scriviEtichetta(n5,5);
    g.scriviEtichetta(n6,6);
    g.scriviEtichetta(n7,7);
    g.scriviEtichetta(n8,8);

    g.insArco(n1,n2,1);
    g.insArco(n2,n8,2);
    g.insArco(n1,n3,3);
    g.insArco(n3,n4,4);
    g.insArco(n3,n5,5);
    g.insArco(n2,n6,6);
    g.insArco(n5,n7,7);
    g.insArco(n8,n7,8);
    g.insArco(n4,n7,9);


    g.set_all_states();
   
    cout << "Number of nodes: " << g.numNodi() << endl;
    cout << "Number of edges: " << g.numArchi() << endl;

    g.bfs(n1);
    aggiorna_adiacenti(g,n1);
    cout<<"\n Aggiornati adiacenti";
    g.bfs(n1);
}


