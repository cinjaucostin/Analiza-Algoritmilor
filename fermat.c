#include "utils.h"

int isPrimeWithFermat(int n, int k){
    /*
        Complexitate pentru if-uri: O(1)
    */
    if (n<=1 || n == 4)
        return 0;
    else if(n ==2 || n == 3)
        return 1;
    /*
        Complexitatea for-ului este: O(log(k)).
        Observatie: Cu cat avem un numar k mai mare, adica un numar de iteratii mai mare, cu atat timpul de executie creste dar
    obtinem si o precizie mai buna a rezultatului.
        In cel mai rau caz se pot face k iteratii, exista si cazuri in care algoritmul se opreste mai repede(atunci cand intra pe unul dintre
    cele doua if-uri).
    */
    for(int i = 0; i < k; i++) {
        /*
            Generam un numar 'a' random in intervalul [2, n-4].
        */
        int a = 2 + rand()%(n-4);
        /*
            Daca numarul 'a' si n pentru care trebuie sa realizam testul nu sunt prime intre ele, in mod cert n este un numar 
        compus si intoarcem 0.
        */
        if(cmmdc(n, a) != 1)
            return 0;
        /*
            Complexitate: O(log(n))
            Observatie: Dupa cum ne spune si algoritmul definit in introducere: daca a^(n-1) % n != 1 ne oprim si intoarcem 
        0 deoarece n este un numar compus.
            Daca rezultatul operatiei de mai devreme este egal cu 1, continuam algoritmul pentru un alt 'a'.
        */
        if(power(a, n-1, n) != 1)
            return 0;
    }
    return 1;
}