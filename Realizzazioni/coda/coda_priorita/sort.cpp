//ordinamento di un array di k elementi sfruttando la struttura coda con priorità
sort(int *A,int k){
    CodaP<int> C;
    for(int i=0; i<k; i++)
        C.inserisci(A[i]);
    int j=0;    
    while(!C.vuota()){
        A[j] = C.min();
        C.rimuovi_min();
        j++;
    }
}

//heap sort
heapsort(T *a,int n){
    for(int i=1;i<n;i++)
        fixUp(i);
    for(int i=1;i<n;i++){
        swap(a,0,n-i);
        fixDown(1,n-i-1);
    }
}