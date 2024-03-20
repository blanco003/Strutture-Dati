#include "AlberoN.h"
#include "./strutture_appoggio/codavt.h"
#include "./strutture_appoggio/single_linked_list.h"
#include <vector>
using namespace std;

AlberoN<int> get_albero(){
   AlberoN<int> T;
   T.insRadice(11);

   T.insPrimoFiglio(T.Radice(),4);
   T.insPrimoFiglio(T.Radice(),2);
   T.insPrimoFiglio(T.Radice(),6);

   T.insPrimoFiglio(T.primoFiglio(T.Radice()),7);
   T.insPrimoFiglio(T.primoFiglio(T.Radice()),8);

   T.insPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.Radice())),10);
   T.insPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.Radice())),12);
   T.insPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.Radice())),8);
   T.insPrimoFiglio(T.fratelloSuccessivo(T.primoFiglio(T.Radice())),6);

   T.insPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice()))),20);
   T.insPrimoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice()))),6);

   T.insPrimoFiglio(T.primoFiglio(T.primoFiglio(T.Radice())),30);

   T.insPrimoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice())))),40);
   T.insPrimoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice())))),2);
   T.insPrimoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice())))),1);
   T.insPrimoFiglio(T.primoFiglio(T.fratelloSuccessivo(T.fratelloSuccessivo(T.primoFiglio(T.Radice())))),20);

   return T;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione POCHI_FIGLI_PARI(...) che prenda in input un albero n-ario di numeri interi e restitutisca
   una lista contenente i valori dei nodi aventi meno di 3 figli aventi valore pari
*/

void esplora_pochi_figli_pari(AlberoN<int> &T,AlberoN<int>::Nodo n,Linked_List<int> &lista){

   // se il nodo corrente non è foglia visitiamo anche i suoi figli 
   if(!T.foglia(n)){

      int count_figli_pari = 0;
      AlberoN<int>::Nodo m = T.primoFiglio(n);

      while(!T.ultimoFratello(m) && count_figli_pari < 3){ // se ha gia piu di 3 figli pari è inutile continuare a contarli
        
         if(T.leggiNodo(m)%2==0){
            count_figli_pari++;
            esplora_pochi_figli_pari(T,m,lista); // effettuiamo la visita del figlio con lo stesso metodo
         }
         m = T.fratelloSuccessivo(m);

      }

      // controlliamo l'ultimo figlio escluso dal while
      if(T.leggiNodo(m)%2==0){
            count_figli_pari++;
      }
      esplora_pochi_figli_pari(T,m,lista);
     
      // se abbiamo trovato meno di 3 figli inseriamo il nodo della lista
      if(count_figli_pari < 3){
         lista.insert(T.leggiNodo(n),lista.begin());
      }


   }else{
      // se è foglia sicuramente avra meno di 3 figli con valore padi dunque lo inseriamo nella lista
      lista.insert(T.leggiNodo(n),lista.begin());
   }
}

Linked_List<int> pochi_figli_pari(AlberoN<int> &T){

   Linked_List<int> lista;

   if(!T.alberoVuoto()){
      esplora_pochi_figli_pari(T,T.Radice(),lista);
   }

   return lista;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   Scrivere la funzione contiene_successivo(...) che prenda in input due alberi n-ari A1 e A2 e restituisca una lista 
   contenente i nodi di A1, il cui successivo è presente in A2. La funzione deve lavorare direttamente sugli alberi, non è
   consentito pertanto il "travaso" degli elementi dell'albero in due liste.

   Esempio: A1 contiene 1,5,7,8,4 e A2 contiene 11,7,5,4,2,9
   La lista da restituire avrà i valori 1,8,4

*/

bool esplora_secondo_albero(AlberoN<int> &A2, AlberoN<int>::Nodo n,int valore){

    // controlliamo se il nodo corrente contiene il successivo del valore da cercare
    if( A2.leggiNodo(n) == valore+1 ){
         return true;
    }

    // se il nodo non è foglia continuiamo a cercare nei suoi figli con lo stesso metodo
    if(!A2.foglia(n)){
      AlberoN<int>::Nodo m = A2.primoFiglio(n);
      while(!A2.ultimoFratello(m)){
           if(esplora_secondo_albero(A2,m,valore)){
               return true;
           }
           m = A2.fratelloSuccessivo(m);
      }
      
      if(esplora_secondo_albero(A2,m,valore)){
             return true;
      }
      
   }

   return  false;

}

void esplora_primo_albero(AlberoN<int> &A1, AlberoN<int> &A2, AlberoN<int>::Nodo n, Linked_List<int> &lista) {
   
    // esamiamo il nodo corrente
    if (esplora_secondo_albero(A2, A2.Radice(), A1.leggiNodo(n))) {

            lista.insert(A1.leggiNodo(n), lista.begin());
    }

    // se il nodo non è foglia effettuiamo la visita dei suoi figli con lo stesso metodo
    if(!A1.foglia(n)){

        AlberoN<int>::Nodo m = A1.primoFiglio(n);

        while (!A1.ultimoFratello(m)) {
            esplora_primo_albero(A1, A2, m, lista);
            m = A1.fratelloSuccessivo(m);
        }
        esplora_primo_albero(A1, A2, m, lista);

    }
}

Linked_List<int> contiene_successivo(AlberoN<int> &A1,AlberoN<int> &A2){
   Linked_List<int> lista;

   // se sono vuoti ovviamente non troveremo nessun successivo
   if(A2.alberoVuoto() || A1.alberoVuoto()){ 
      return lista;
   }

   esplora_primo_albero(A1,A2,A1.Radice(),lista);
   return lista;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione tantifigli(...) che prenda in input un albero n-ario e restituisca una lista contenente
   i valori dei nodi aventi piu di 3 figli
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void esplora_tanti_figli(AlberoN<int> &T,AlberoN<int>::Nodo n,Linked_List<int> &lista){

   if(!T.foglia(n)){
      int count = 0;
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m) && count < 3){
         count++;
         esplora_tanti_figli(T,m,lista);
         m = T.fratelloSuccessivo(m);
      }
      count++;
      esplora_tanti_figli(T,m,lista);      

      if(count > 3){
         lista.insert(T.leggiNodo(n),lista.begin());
      }
   }else{
      // se è foglia ovviamente non puo avere piu di 3 figli
   }
}

Linked_List<int> tanti_figli(AlberoN<int> &T){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
      esplora_tanti_figli(T,T.Radice(),lista);
   }
   return lista;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione differenza_alberi(...) che prenda in input 2 alberi n-ari A1 e A2 e restituisca una lista
   contenente i nodi presenti in A1 ma non in A2.

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ricerca nel secondo albero del valore del nodo esaminato nel primo albero
bool cerca_secondo_albero(AlberoN<int> &A2,AlberoN<int>::Nodo n,int valore){

   // esaminiamo il nodo corrente
   if(A2.leggiNodo(n) == valore){
      return true;
   }
   
   // se il nodo non è foglia continuiamo a cercare il valore nei figli con lo stesso metodo
   if(!A2.foglia(n)){
      AlberoN<int>::Nodo m = A2.primoFiglio(n);
      while(!A2.ultimoFratello(m)){
            if(cerca_secondo_albero(A2,m,valore)){
              return true;
            }
            m = A2.fratelloSuccessivo(m);
      }
      if(cerca_secondo_albero(A2,m,valore)){
         return true;
      }
   }

   return false;
}


// esplora i nodi del primo albero
void esplora_primo_albero_differenza(AlberoN<int> &A1,AlberoN<int> &A2,AlberoN<int>::Nodo n,Linked_List<int> &lista){

   // esaminiamo il nodo corrente
   if(!cerca_secondo_albero(A2,A2.Radice(),A1.leggiNodo(n))){
       lista.insert(A1.leggiNodo(n),lista.begin());
   }

   // se il nodo non è figlia effettuiamo la visita dei figli con lo stesso metodo
   if(!A1.foglia(n)){
      AlberoN<int>::Nodo m = A1.primoFiglio(n);
      while(!A1.ultimoFratello(m)){
         esplora_primo_albero_differenza(A1,A2,m,lista);
         m = A1.fratelloSuccessivo(m);
      }
      esplora_primo_albero_differenza(A1,A2,m,lista);
   }
}

Linked_List<int> differenza_alberi_lista(AlberoN<int> &A1,AlberoN<int> &A2){
   Linked_List<int> lista;
   if(!A1.alberoVuoto()){ // se A1 è vuoto ovviamente la lista sarà vuota siccome non abbiamo nessun elemento da confronare in A2
      esplora_primo_albero_differenza(A1,A2,A1.Radice(),lista);
   }
   return lista;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione presente(...) che prenda in input 2 alberi n-ari di interi P e Q, e un valore intero X e restituisca:
   - 2 se X è presente in entrambi gli alberi
   - 1 se X è presente in uno solo dei 2 alberi
   - 0 se è assente in entrambi gli alberi

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool esplora_presente(AlberoN<int> &T,AlberoN<int>::Nodo n,int x){

   if(T.leggiNodo(n)==x){
      return true;
   }

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         if(esplora_presente(T,m,x)){
            return true;
         }
         m = T.fratelloSuccessivo(m);
      }
      if(esplora_presente(T,m,x)){
         return true;
      }
   }
}

int presente(AlberoN<int> &P, AlberoN<int> &Q, int x) {
    if (esplora_presente(P, P.Radice(), x) && esplora_presente(Q, Q.Radice(), x)) {
        return 2;
    } else if (esplora_presente(P, P.Radice(), x) || esplora_presente(Q, Q.Radice(), x)) {
        return 1;
    }
    return 0;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione media_a_padre(..) che prenda in input un albero n-ario e aggiorni bottom-up il valore di tutti i nodi con 
   la media dei valori dei suoi figli. La funzione deve restituire il numero di nodi che non hanno subito un cambiamento di valore

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void esplora_albero_media(AlberoN<double> &T,AlberoN<double>::Nodo n,int &count){

   if(!T.foglia(n)){
      AlberoN<double>::Nodo m = T.primoFiglio(n);

      double temp_sum = 0; // somma dei figli del nodo n
      double num = 0; // numero di figli del nodo n

      //esploriamo i figli e aggiorniamo le variabili
      while(!T.ultimoFratello(m)){
         temp_sum += T.leggiNodo(m);
         num++;
         esplora_albero_media(T,m,count);
         m = T.fratelloSuccessivo(m);
      }

      temp_sum += T.leggiNodo(m);
      num++;
      esplora_albero_media(T,m,count);

      double media = temp_sum/num;
      
      //cout<<"\nSomma dei figli di ("<<T.leggiNodo(n)<<") = "<<temp_sum<<", numero di figli : "<<num<<", quindi media : "<<media;

      // controlliamo se l'albero contiene gia etichetta pari alla media
      if(T.leggiNodo(n) != media){
         T.scriviNodo(n,media);
      }else{
         count++;
      }

   }else{
      // se non ha figli ovviamente non viene modificato
      //cout<<"\nFoglia : ("<<T.leggiNodo(n)<<")";
      count++;
   }
}

int media_a_padre(AlberoN<double> &T){
   int count = 0;
   esplora_albero_media(T,T.Radice(),count);
   return count;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione differenza_alberi(..) che prenda in input 2 alberi n-ari T1 e T2 e restituisca la differenza in valore assoluto del 
   numero di nodi dei 2 alberi.
   Esempi :
   - se T1 ha 50 nodi e T2 ne ha 10, deve restituire 40
   - se T1 ha 40 nodi e T2 ne ha 60, deve restituire 20

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void count_nodes(AlberoN<int> &T,AlberoN<int>::Nodo n,int &count){

   count++;

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         count_nodes(T,m,count);
         m = T.fratelloSuccessivo(m);
      }
      count_nodes(T,m,count);
   }
}

int differenza_alberi(AlberoN<int> &T1,AlberoN<int> &T2){

   int count1 = 0; 
   if(!T1.alberoVuoto()){
      count_nodes(T1,T1.Radice(),count1);
   }
   
   int count2 = 0;
   if(!T2.alberoVuoto()){
      count_nodes(T2,T2.Radice(),count2);
   }
   
   cout<<"\ncount1 : "<<count1<<", count2 : "<<count2;
   return (abs(count2-count1));
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA:  ✔
   Scrivere la funzione lista_speciale(...) che prenda in input un albero n-ario di interi e restituisca una lista contenente i valori
   x tali che il medesimo valore x compaia almeno un altra volta nell'albero ad un livello inferiore (verso le foglie) rispetto al livello 
   in cui si trova x.

   Rifarlo con superiore (verso la radice) al posto di inferiore

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


bool visita_cerca(AlberoN<int> &T,AlberoN<int>::Nodo n,int valore,int livello_nodo,int livello_corrente){
  
   if(livello_corrente < livello_nodo){

      if(T.leggiNodo(n) == valore){
         return true;
      }

      if(!T.foglia(n)){
         AlberoN<int>::Nodo c = T.primoFiglio(n);
         while(!T.ultimoFratello(c)){
            if(visita_cerca(T,c,valore,livello_nodo,livello_corrente+1)){
               return true;
            }
            c = T.fratelloSuccessivo(c);
         }

         if(visita_cerca(T,c,valore,livello_nodo,livello_corrente+1)){
            return true;
         }
      }

   }
   return false;
}


void visita(AlberoN<int> &T,AlberoN<int>::Nodo n,int livello_corrente,Linked_List<int> &lista){

   // esamina nodo : cerca il valore del nodo corrente ad un livello inferiore ( verso le foglie )
   if(visita_cerca(T,T.Radice(),T.leggiNodo(n),livello_corrente,0)){ // 0 = livello radice 
      lista.insert(T.leggiNodo(n),lista.begin());
   }

   // se il nodo non è foglia, effettuiamo la visita dei figli con lo stesso metodo
   if(!T.foglia(n)){
      AlberoN<int>::Nodo c = T.primoFiglio(n);
      while(!T.ultimoFratello(c)){
         visita(T,c,livello_corrente+1,lista);
         c = T.fratelloSuccessivo(c);
      }
      visita(T,c,livello_corrente+1,lista);
   }

}

Linked_List<int> lista_speciale(AlberoN<int> &T){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
      visita(T,T.Radice(),0,lista);
   }
   return lista;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* -TRACCIA: ✔
   Scrivere la funzione somma_a_padre (…) che prenda in input un albero n-ario di interi e cambi il valore di
   ciascun nodo affinchè, al termine dell’esecuzione della funzione, ogni nodo contenga un valore uguale alla
   somma dei valori dei suoi figli.

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void visita_somma(AlberoN<int> &T,AlberoN<int>::Nodo n){
   if(!T.foglia(n)){
      int sum = 0;
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         sum += T.leggiNodo(m);
         visita_somma(T,m);
         m = T.fratelloSuccessivo(m);
      }
      sum += T.leggiNodo(m);
      visita_somma(T,m);

      T.scriviNodo(n,sum);
   }
}

void somma_a_padre(AlberoN<int> &T){
   if(!T.alberoVuoto()){
      visita_somma(T,T.Radice());
   }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione maggiori_in_entrambi(...) che prenda in input 2 alberi n-ari di interi P e Q, un valore intero X e un valore intero K
   e restituisca true se in entrambi gli alberi vi sono almeno K valori maggiori di X, false altrimenti
 
*/

bool maggiore_in_albero(AlberoN<int> &T,AlberoN<int>::Nodo n,int val,int num_volte,int &count){

   if(T.leggiNodo(n) > val){
       count++;
   }

   //controlliamo se abbiamo raggiunte il numero di volte necessarie
   if(count >= num_volte){
       return true;
   }

   
   //continuiamo ad esplorare i figli se il nodo non è foglia
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         if(maggiore_in_albero(T,m,val,num_volte,count)){
            return true;
         }
         m = T.fratelloSuccessivo(m);
      }
      if(maggiore_in_albero(T,m,val,num_volte,count)){
         return true;
      }
   }

   return false; // se abbiamo esplorato gia tutto l'albero e arriviamo alla fine vuol dire che non ci sonoa abbastanza valori 
}

bool maggiori_in_entrambi(AlberoN<int> &P, AlberoN<int> &Q,int x,int k){
   int count = 0;
   if(maggiore_in_albero(P,P.Radice(),x,k,count) && maggiore_in_albero(Q,Q.Radice(),x,k,count)){
      return true;
   }
   return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   Scrivere la funzione ottieni_speciali(…) che prenda in input un albero di interi e un nodo e restituisca la lista
   dei discendenti di tale nodo che hanno un valore presente in almeno un altro nodo di livello inferiore
   (nota: inferiore = verso la radice, non verso le foglie)

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool cerca_discente(AlberoN<int> &T,AlberoN<int>::Nodo n,int valore,int livello_nodo, int livello_corrente){
   
   if(livello_corrente < livello_nodo){
      
   if(T.leggiNodo(n) == valore){
      return true;
   }

   // continua a cercare nei figli se non è foglia
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         if(cerca_discente(T,m,valore,livello_nodo,livello_corrente++)){
            return true;
         }
         m = T.fratelloSuccessivo(m);
      }
      if(cerca_discente(T,m,valore,livello_nodo,livello_corrente++)){
         return true;
      }
   }   

   }

   // se abbiamo sforato il livello massimo da cercare è inutile continuare a cercare nei livelli non corretti
   return false; 
}

void esplora_ottieni_speciali_disc(AlberoN<int> &T,AlberoN<int>::Nodo n,Linked_List<int> &lista,int liv_corrente){
   
   // esamina nodo
   if(cerca_discente(T,T.Radice(),T.leggiNodo(n),liv_corrente,0)){  // 0 rappresenta il livello della radice
      lista.insert(T.leggiNodo(n),lista.begin());
   }

   // esamina figli se non è foglia
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         esplora_ottieni_speciali_disc(T,m,lista,liv_corrente++);
         m = T.fratelloSuccessivo(m);
      }
      esplora_ottieni_speciali_disc(T,m,lista,liv_corrente++);
   }
}

Linked_List<int> ottieni_speciali_disc(AlberoN<int> &T,AlberoN<int>::Nodo n){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
      esplora_ottieni_speciali_disc(T,n,lista,0); // 0 rappresenta il livello corrente di partenza
   }
   return lista;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione aggiorna in cascata (...) che prenda in input un albero n-ario di interi P e lo aggiorni, spostandone i valori,
   in modo tale che ogni nodo contenga valori più piccoli di tutti i suoi figli.

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void esplora_aggiorna_in_cascata(AlberoN<int> &T,AlberoN<int>::Nodo n){
   if(!T.foglia(n)){
      int min = T.leggiNodo(n);
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         if(T.leggiNodo(m) < min){
            min = T.leggiNodo(m);
         }
         esplora_aggiorna_in_cascata(T,m);
         m = T.fratelloSuccessivo(m);
      }
      if(T.leggiNodo(m) < min){
         min = T.leggiNodo(m);
      }
      esplora_aggiorna_in_cascata(T,m);

      if(T.leggiNodo(n) > min){
         T.scriviNodo(n,min);
      }

   }
}

void aggiorna_in_cascata(AlberoN<int> &T){
   if(!T.alberoVuoto()){
      esplora_aggiorna_in_cascata(T,T.Radice());
   }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione incrementa_dispari(…) che prenda in input un albero e incrementi di 1 il valore dei nodi
   che si trovano ad un livello dispari e che abbiano almeno un figlio (si assume che la radice sia a livello 0 e non
   sia da aggiornare). La funzione deve restituire la lista dei nodi che hanno subito un cambiamento di valore. 

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void esplora_albero_dispari(AlberoN<int> &T,AlberoN<int>::Nodo n,int livello_corrente,Linked_List<int> &lista){

   // esamina nodo
   if(livello_corrente %2 != 0 && !T.foglia(n)){
         lista.insert(T.leggiNodo(n),lista.begin());
         T.scriviNodo(n,T.leggiNodo(n)+1);
   }

   // visita dei figli
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         esplora_albero_dispari(T,m,livello_corrente+1,lista);
         m = T.fratelloSuccessivo(m);
      }
      esplora_albero_dispari(T,m,livello_corrente+1,lista);
   }
   
}

Linked_List<int> incrementa_dispari(AlberoN<int> &T){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
      esplora_albero_dispari(T,T.Radice(),0,lista); // 0 rappresenta il livello corrente della radice
   }
   return lista;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Dato un albero n-ario di elementi di tipo intero, implementare in C++ la
   funzione multipli(Tree<int>) che modifica l’etichetta di ogni nodo n
   dell’albero memorizzandoci il numero dei nodi pari presenti nel sottoalbero
   radicato in n.
*/


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void trova_count_pari(AlberoN<int> &T,AlberoN<int>::Nodo n,int &count_pari){
   if(T.leggiNodo(n) %2 == 0){
      count_pari++;
   }

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
         while (!T.ultimoFratello(m)){
               trova_count_pari(T,m,count_pari);
               m = T.fratelloSuccessivo(m);
         }
         trova_count_pari(T,m,count_pari); 
   } 
}

void esplora_albero_multipli(AlberoN<int> &T,AlberoN<int>::Nodo n){
   int count_pari = 0;
   trova_count_pari(T,n,count_pari);
   T.scriviNodo(n,count_pari);

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
         while (!T.ultimoFratello(m)){
               esplora_albero_multipli(T,m);
               m = T.fratelloSuccessivo(m);
         }
         esplora_albero_multipli(T,m); 
   }
   
}

void multipli(AlberoN<int> &T){
   esplora_albero_multipli(T,T.Radice());
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   -Dato un albero n-ario di elementi di tipo intero, implementare in C++ una
   funzione che calcoli, ispezionando l’albero in ordine simmetrico (invisita) con
   valore di i=1, il numero di nodi aventi come padre un nodo il cui valore è pari

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void count_invista_padre_pari(AlberoN<int> &T, AlberoN<int>::Nodo n,int i,int &count){
   
   if(T.foglia(n)){
      // esamina nodo
      cout<<" "<< T.leggiNodo(n);
      if(n != T.Radice()){ // dobbiamo controllare non sia la radice, altrimenti se tentiamo di accedere al padre crasha tutto
         if(T.leggiNodo(T.padre(n))%2==0){
            count++;
         }
      }      
	}else{
		
		AlberoN<int>::Nodo c =  T.primoFiglio(n);
		int k = 0;
		while(!T.ultimoFratello(c) && k<i){
				k=k+1;
				count_invista_padre_pari(T,c,i,count);
				c = T.fratelloSuccessivo(c);
			}

		if (T.ultimoFratello(c) && k<i){
			count_invista_padre_pari(T,c,i,count);
		}
			
      // esamina nodo
      cout<<" "<< T.leggiNodo(n);
      if(n != T.Radice()){ // dobbiamo controllare non sia la radice, altrimenti se tentiamo di accedere al padre crasha tutto
         if(T.leggiNodo(T.padre(n))%2==0){
            count++;
         }
      }

		while (!T.ultimoFratello(c)){
				count_invista_padre_pari(T,c,i,count);
				c = T.fratelloSuccessivo(c);
		}
		if (k==1){
			count_invista_padre_pari(T,c,i,count);
		}
			
		
	}	

 
}

  

int count_invista_padre_pari(AlberoN<int> &T){
   int count = 0;
   if(!T.alberoVuoto()){
      int i = 1;
      count_invista_padre_pari(T,T.Radice(),i,count);
   }
   return count;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA:  ✔
 
   -Dato un albero n-ario di elementi di tipo intero, implementare in C++ la
   funzione int max_level(Tree<int>) che restituisce in output il livello k
   dell’albero per il quale la somma di tutti i nodi del livello k è massima

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void max_level(AlberoN<int> &T, AlberoN<int>::Nodo n, int lvl_corrente,vector<int> &somme){

   // inizializziamo lo spazio necessario a contenere il livello
   while (somme.size() <= lvl_corrente) {
        somme.push_back(0);
   }

   somme[lvl_corrente] += T.leggiNodo(n);

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         max_level(T,m,lvl_corrente+1,somme);
         m = T.fratelloSuccessivo(m);
      }
       max_level(T,m,lvl_corrente+1,somme);
   }
   
}

int max_level (AlberoN<int> &T){
   vector<int> somme;
   if(!T.alberoVuoto()){
      max_level(T,T.Radice(),0,somme); // 0 raprresenta il livello corrente, in questo caso quello della radice
   }
   
   
   int i_max = 0;
   int max = somme[0];

   // trova l'indice con la somma piu grande
   for(int i = 0; i < somme.size(); i++){
      if(somme[i] > max){
         max = somme[i];
         i_max = i;
      }
      cout<<endl<<"somma del livello "<<i<<" : "<<somme[i];
   }

   return i_max;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
/* TRACCIA: ✔
   -Dato un albero n-ario con nodi aventi etichetta di tipo intero, implementare
   un metodo in C++ che modifichi l’albero in modo tale che l’etichetta di ogni
   nodo n corrisponda alla somma dei valori delle etichette dei nodi del
   sottoalbero radicato in n.
*/

// trova la somma dell'albero radicato in n
void sum_sub_tree(AlberoN<int> &T,AlberoN<int>::Nodo n,int &temp_sum_sub_tree){

   temp_sum_sub_tree += T.leggiNodo(n);

   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while (!T.ultimoFratello(m)){
          sum_sub_tree(T,m,temp_sum_sub_tree);
          m = T.fratelloSuccessivo(m);
      }
      sum_sub_tree(T,m,temp_sum_sub_tree);
   }
}

void esplora_albero_sum(AlberoN<int> &T, AlberoN<int>::Nodo n){
   
   // esplora il nodo : trova la somma del sottoalbero radicato in n e scrivila nell'etichetta di n
   int temp_sum_sub_tree = 0;
   sum_sub_tree(T,n,temp_sum_sub_tree);
   T.scriviNodo(n,temp_sum_sub_tree);

   // visita dei figli se il nodo non è foglia
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         esplora_albero_sum(T,m);
         m = T.fratelloSuccessivo(m);
      }
      esplora_albero_sum(T,m);
   }
      
}

void nodo_somma_sottoalbero(AlberoN<int> &T){
   if(!T.alberoVuoto()){
      esplora_albero_sum(T,T.Radice());
   }  
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔

   Scrivere la funzione lista_speciale(...) che prenda in input un albero n-ario di interi e restituisca una lista contenente i valori
   x tali che esista, nell'albero, almeno un valore maggiore di x ad un livello superiore (rispetto al livello in cui si trova x)

   Rifarlo con inferiore al posto di superiore.

   SUPERIORE = verso la radice
   INFERIORE = verso le foglie

*/

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool lista_speciale_sup(AlberoN<int> &T,AlberoN<int>::Nodo n,int val,int lvl_nodo, int lvl_corrente){
  
   // continuiamo a cercare fin quando siamo in un livello minore del livello in input 
   if(lvl_corrente < lvl_nodo){

      // esamina nodo
      if(T.leggiNodo(n) > val){
         return true;
      }

      // se il nodo non è foglia continuiamo a cercare nei figli con lo stesso metodo
      if(!T.foglia(n)){
         AlberoN<int>::Nodo m = T.primoFiglio(n);
         while(!T.ultimoFratello(m)){
            if(lista_speciale_sup(T,m,val,lvl_nodo,lvl_corrente+1)){
               return true;
            }
            m = T.fratelloSuccessivo(m);
         }
         if(lista_speciale_sup(T,m,val,lvl_nodo,lvl_corrente+1)){
            return true;
         }
      }
   }

   // se il nodo non è foglia continuiamo a cercare

   return false;
}


void lista_speciale_sup(AlberoN<int> &T,AlberoN<int>::Nodo n,int lvl_corrente,Linked_List<int> &lista){
 
   // esamina nodo : visitiamo l'albero in cerca di un valore maggiore del nodo corrente ad un livello superiore del corrente
   if(lista_speciale_sup(T,T.Radice(),T.leggiNodo(n),lvl_corrente,0)){  // 0 rappresenta il livello da dove inziare a cercare, ovvero la radice
      lista.insert(T.leggiNodo(n),lista.begin());
   }

   // se il nodo non è foglia continuiamo a esplorare i figli con lo stesso metodo
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         lista_speciale_sup(T,m,lvl_corrente+1,lista);
         m = T.fratelloSuccessivo(m);
      }
      lista_speciale_sup(T,m,lvl_corrente+1,lista);
   }
}

Linked_List<int> lista_speciale_sup(AlberoN<int> &T){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
      lista_speciale_sup(T,T.Radice(),0,lista);
   }
   return lista;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ?

   Scrivere la funzione max_a_nonno(..) che prenda in input un albero n-ario e aggiorni il valore di tutti i nodi con il massimo valore tra
   sè stesso e i suoi "nipoti". La funzione deve restituire il numero di nodi che non hanno subito un cambiamento di valore.
   Esempi:
   - se un nodo contiene il valore 5 e i suoi nipoti contengono i valori 3,1,4,2,1,1,0 al termine della funzione tale nodo conterrà 5
   - se un nodo contiene il valore 5 e i suoi nipoti contengono i valori 4,2,7,1,9,2 al termine della funzione tale nodo conterrà 9

*/

void post_visita(AlberoN<int> &T,AlberoN<int>::Nodo n, int &num_nodi_invariati){
   // visita ricorsiva di tutti i nodi
   if(!T.foglia(n)){
      AlberoN<int>::Nodo c = T.primoFiglio(n);
      while(!T.ultimoFratello(c)){
         post_visita(T,c,num_nodi_invariati);
         c = T.fratelloSuccessivo(c);
      }
      post_visita(T,c,num_nodi_invariati);
   }

   // esamina nodo 
   int max_valore = T.leggiNodo(n);

   if(!T.foglia(n)){
      AlberoN<int>::Nodo v = T.primoFiglio(n);

      // visita i figli del nodo del nodo n
      while(!T.ultimoFratello(v)){

         if(!T.foglia(v)){
            // visita i nipoti del nodo n
            AlberoN<int>::Nodo  k = T.primoFiglio(v);

            while(!T.ultimoFratello(k)){
               if(max_valore < T.leggiNodo(k)){
                  max_valore = T.leggiNodo(k);
               }
               k = T.fratelloSuccessivo(k);
            }
         }
         v = T.fratelloSuccessivo(v);
      }
   }

   if(max_valore == T.leggiNodo(n)){
         num_nodi_invariati++;
   }else{
         T.scriviNodo(n,max_valore);
   }
}

int max_a_nonno(AlberoN<int> &T){
   int num_nodi_invariati = 0;
   post_visita(T,T.Radice(),num_nodi_invariati);
   return num_nodi_invariati;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/* TRACCIA: ✔
   Scrivere la funzione costante_a_livello_k(...) che prenda in input un Albero A, un intero k e un valore v e imposti
   a v il valore di tutti i nodi al livello k. La funzione deve restituire la lista dei nodi che NON hanno subito un cambiamento di valore,
   inclusi quelli al livello k che avevano già un valore pari a v.

*/

void costante_a_livello_k(AlberoN<int> &T, AlberoN<int>::Nodo n,int livello_corrente,int k, int v,Linked_List<int> &lista){
   
   //esamina nodo
   if(livello_corrente == k){
      // controlliamo se il nodo ha valore v
      if(T.leggiNodo(n) != v){
         T.scriviNodo(n,v);
      }else{
         lista.insert(T.leggiNodo(n),lista.begin());
      }
   }else{
      lista.insert(T.leggiNodo(n),lista.begin());
   }

   // se il nodo non è foglia esplora i suoi figli con lo stesso metodo
   if(!T.foglia(n)){
      AlberoN<int>::Nodo m = T.primoFiglio(n);
      while(!T.ultimoFratello(m)){
         costante_a_livello_k(T,m,livello_corrente+1,k,v,lista);
         m = T.fratelloSuccessivo(m);
      }
      costante_a_livello_k(T,m,livello_corrente+1,k,v,lista);
   }
}

Linked_List<int> costante_a_livello_k(AlberoN<int> &T,int k,int v){
   Linked_List<int> lista;
   if(!T.alberoVuoto()){
         costante_a_livello_k(T,T.Radice(),0,k,v,lista); // 0 rappresenta il livello corrente, in questo caso quello della radice
   }
   return lista;
}

int main(){
   AlberoN<int> T = get_albero();

   T.visitaAmpiezza(T.Radice());
   cout<<endl;


}