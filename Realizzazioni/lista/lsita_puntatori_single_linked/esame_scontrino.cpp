#include <iostream>
using namespace std;

/*  TRACCIA :
    
    Si vuole progettare il tipo scontrino, facendo uso di liste, per la memorizzazione del corrispettivo totale di spesa,
    quantità e descrizione di quanto acquistato. Dopo aver definito ed implementato il tipo prodotto (in modo da memorizzare nome e
    prezzo del prodotto), realizzare e completare, aggiungendo altri metodi o campi, in C++ la seguente classe per la rappresentazione di scontrini. 

class scontrino{
    public:
        // aggiunge un prodotto allo scontrino 
        //void aggiungi (prodotto v);

        // rimuove un prodotto dallo scontrino 
        //void rimuovi (prodotto v);

        //restituisce il totale di spesa 
        //double totale ();

        //restituisce il prodotto più costoso 
        //prodotto costoso ();

        // stampa lo scontrino 
        //void stampa();
    private:
        list <prodotto> S;
};

*/

class Prodotto{

        friend class scontrino;

         private:
            int prezzo;
            string nome;
            Prodotto* next;
         public:
            Prodotto();

            void set_prezzo(int p){
                prezzo = p;
            }

            string set_nome(string n){
                nome = n;
            }

            int get_prezzo(){
                return prezzo;
            }

            string get_nome(){
                return nome;
            }
    };


class scontrino : public Prodotto{

    public:

        void aggiungi (Prodotto p){
            Prodotto *temp = new Prodotto;
            temp->prezzo = p.get_prezzo();
            temp->nome = p.get_nome();
            temp->next = nullptr;
            if(testa == nullptr){
                testa = temp;
            }else{
                Prodotto *t = new Prodotto;
                t = testa;
                while(t != nullptr){
                    
                }
            }
        };
        void rimuovi (Prodotto);
        double totale ();
        Prodotto costoso ();
        void stampa();
    private:
        Prodotto* testa;
        int lunghezza;
};

int main(){


    cout<<"ciao";
}