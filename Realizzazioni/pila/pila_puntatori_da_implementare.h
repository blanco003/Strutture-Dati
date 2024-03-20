template <class T>

class cella{
private:
   T valore;
   cella *next;
}


class Pila{

public: 
    Pila(){
        testa = nullptr;
    }

    -Pila(){
        delete
    }

    bool pilavuta(){
        return (testa==nullptr);
    }   

    T leggipila(){
        return testa->valore;
    }

    void impila(T e){
        cella *tmp = new cella;
        tmp->next = testa;
        testa = tmp;
    }

    void fuoripila(){
        cella *tmp = testa;
        testa = testa->next;
        delete tmp;
    }


private:
    cella *next;
}