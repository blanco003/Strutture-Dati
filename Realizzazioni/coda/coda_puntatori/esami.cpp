#include "coda.h"
#include <iostream>

/* TRACCIA : 
   -Una struttura dati acquisisce numeri interi da 1 a 9 che inserisce in tre code secondo il seguente schema.
    Gli interi da 1 a 3 vengono inseriti nella prima coda, quelli da 4 a 6 nella seconda, e i restanti nella terza.
    La struttura mette a disposizione una serie di metodi che permettono di conoscere e cambiare il suo stato.
    Realizzare in C++ la seguente classe che implementa la struttura appena descritta.

class Bins{

    public:

        //inserisce l'intero k nella corrispondente coda
        void insert (int k);

        // effettua un fuoriCoda della coda C
        void delete (int c);

        //restituisce la media dei valori attulamente memorizzati nella coda c
        double mean (int c);

        // restituisce il numeri di elementi inseriti nella coda c
        int freq (int c);
    
    private:

        Coda<int> bins[3];

};

*/


class Bins{
    public:
        Bins();
        void insert (int k);
        void deleteElement(int c);
        double mean (int c);      
        int freq (int c);
        void stampa(int i);
    private:
        Coda<int> bins[3];
};

Bins::Bins() {
    // Inizializzazione delle code
    for (int i = 0; i < 3; ++i) {
        bins[i] = Coda<int>();  // Inizializza una nuova istanza di Coda
    }
}

void Bins::insert(int c){
    if(c>0 && c<=3){
        bins[0].Incoda(c);
    }else if(c>=4 && c<=6){
        bins[1].Incoda(c);
    }else{
        bins[2].Incoda(c);
    }
    
}

void Bins::stampa(int i){
    if(i >= 0 && i < 3){
        bins[i].stampaCoda();
    }
}

void Bins::deleteElement(int c){
    if(c >= 0 && c < 3){
        if(!bins[c].Codavuota()){
             cout<<"\nSto eliminando l'elemento "<<bins[c].Leggicoda()<<" dalla coda "<<c;
             bins[c].Fuoricoda();
             cout<<endl<<"eliminato";
        }
       
    }else{
        cout<<endl<<"errore input";
    }
}

double Bins::mean(int c) {
    if (c >= 0 && c < 3) {
        if (bins[c].Codavuota()) {
            return 0.0;
        }

        // Creiamo una copia della coda principale
        Coda<int> temp = bins[c];
        
        double sum = 0;
        double count = 0;

        // Estrai i valori dalla copia della coda e calcola la somma
        while (!temp.Codavuota()) {
            sum += temp.Leggicoda();
            temp.Fuoricoda();
            count++;
        }

        // Calcola la media utilizzando i valori estratti
        double media = sum / count;
        return media;
    } else {
        std::cout << "Errore input" << std::endl;
        return -1.0;
    }
}

int Bins::freq(int c){
     if (c >= 0 && c < 3) {

        if(bins[c].Codavuota()){
            return 0;
        }

        // creiamo una coda temporanea per non influenzare la coda in input
        Coda<int> temp = bins[c];
        int count = 0;

        while (!temp.Codavuota()) {
            temp.Fuoricoda();
            count++;
        }

        return count;
        
    }else{
        cout<<endl<<"errore input";
        return -1;
    }
}

/*
int main() {

    Bins myBins;
    // Inserisci alcuni numeri nelle code
    
    myBins.insert(2);
    myBins.insert(3);
    myBins.insert(1);
    myBins.insert(4);
    myBins.insert(5);
    myBins.insert(3);
    myBins.insert(4);
    myBins.insert(9);
    myBins.insert(5);
    myBins.insert(6);
    myBins.insert(8);
    cout<<endl;

    // stampa code
    for(int i = 0; i < 3; i++){
        cout << "\nCoda " << i + 1;
        myBins.stampa(i);
    }

    // numero di elementi in ogni coda
    for(int i = 0; i < 3; i++){
        cout << "\nFreq " << i + 1 << ": " << myBins.freq(i);
    }

    // numero di elementi in ogni coda
    for(int i = 0; i < 3; i++){
        cout << "Delete " << i + 1 << endl;
        myBins.deleteElement(i);
    }


    cout<<"fine";

    return 0;
}
*/