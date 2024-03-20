#include "coda.h"
#include <iostream>

int main() {
    Coda<int> C;
    C.Incoda(1);
    C.Incoda(2);
    C.Incoda(3);
    C.Incoda(4);
    C.Incoda(5);

    C.stampaCoda();
    cout<<"\nElemento in testa : "<<C.Leggicoda();

    C.Fuoricoda();
    C.Fuoricoda();
    C.stampaCoda();

    C.~Coda();
    C.stampaCoda();

    return 0;
}
