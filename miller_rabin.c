#include "utils.h"

int MillerRabinTest(int d, int n){  
    /*
        Generam un numar a random in intervalul [2, n-2].
    */
    int a = 2 + rand()%(n-4);
    /*
        Complexitatea: O(log(d)), unde d reprezinta exponentul pentru care vom aplica operatia de modulare exponentiala.
        Am declarat x ca fiind long long deoarece in while vom face x = (x ^ 2) % n si pentru a fi sigur ca nu se sare
    peste dimensiunea MAX_INT-ului am declarat variabila ca fiind long long.
    */
    long long x = power(a, d, n);
    /*
        Conform algoritmului, daca rezultatul modularii exponentiale efectuate anterior este 1 sau n - 1 inseamna ca
    n este un numar compus.
    */
    if(x == 1 || x== n-1)
        return 1;
    while(d != n-1) {
        x = (x * x) % n;
        d *= 2;
        /*
            Daca x^2 % n == 1, inseamna ca numarul este compus.
            Altfel, daca x^2 % n == n-1, inseamna ca numarul este prim.
            Daca nu are loc niciunul dintre cazuri atunci dublam d-ul si continuam bucla.
        */
        if(x == 1)
            return 0;
        else if(x == n-1)
            return 1;
    }
    /*
        Daca am ajuns in acest punct inseamna ca n este compus
    */
    return 0;
}

/*
    Functia care verifica daca numarul n este prim, k este numarul de iteratii, adica cate numere 'a' generam pentru a face testul.
*/

int isPrimeWithMillerRabin(int n, int k){
    /*
        Tratam cazurile de baza:
            -> Daca n<=1 sau n==4 intoarcem 0, deoarece aceste numere nu sunt prime.
            -> Daca n==2 sau n==3 intoarcem 1, deoarece 2 si 3 sunt numere prime.
    */
    if (n <= 1 || n == 4)
        return 0;
    else if(n == 2 || n == 3)
        return 1;

    /*
        Complexitate: O(logn)
    */
    int d = d_calculator(n); 

    /*
        Complexitate: O(logk), unde k reprezinta numarul de pasi pe care ii facem(adica numarul de 'a' pe care ii generam)
    si care defineste de altfel si precizia algoritmului.
    */
    for(int i=0; i < k; i++){ 
        if(MillerRabinTest(d,n) == 0)
            return 0;
    }
    return 1;
}

