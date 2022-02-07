#include "utils.h"

/*
    Functii auxiliare pentru cei doi algoritmi de testare a primalitatii
*/
/*
    Calculeaza b^e % p in O(loge), unde e este exponentul.
*/
int power(long long b, unsigned int e, int p)
{
    long long res = 1;
    /*
        In cazul in care b este mai mare decat p actualizam valoarea lui b
    */
    b = b % p;
    /*
        Cazul in care operatia anterioara a avut ca rezultat 0 (adica b == p)
    */
    if (b == 0)
        return 0;
    while (e > 0)
    {
        if (e & 1)
        {
            res = (res * b) % p;
        }

        e = e >> 1;
        b = (b * b) % p;
    }
    return res;
}

/*
    Complexitatea functiei este O(log(d)), cum d este egal cu n-1 inseamna ca avem o complexitate O(log(n)), unde n este
numarul pentru care vrem sa aplicam testul de primalitate
*/
int d_calculator(int n)
{
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    return d;
}

/*
    Functie care calculeaza cel mai mare divizor comun a doua numere.
    Ne va fi utila in algoritmul lui Fermat in care vom avea nevoie sa calculam daca doua numere sunt sau nu prime intre ele.
*/
int cmmdc(int a, int b)
{
    if (a < b)
        return cmmdc(b, a);
    else if (a % b == 0)
        return b;
    else
        return cmmdc(b, a % b);
}

/*
    Functii auxiliare pentru citire/scriere din/in fisiere
*/

/*
    Functia care intoarce un string cu numele unui fisier de intrare in functie de numarul acestuia
*/
char *create_input_filename(int i)
{
    char *buffer = calloc(10, sizeof(char));
    char *path_to_input_file = calloc(20, sizeof(char));
    strcpy(path_to_input_file, "in/test");
    sprintf(buffer, "%d.in", i);
    strcat(path_to_input_file, buffer);
    free(buffer);
    return path_to_input_file;
}

/*  
    Functia care intoarce un string cu numele unui fisier de iesire in functie de numarul acestuia
*/
char *create_output_filename(int i)
{
    char *buffer = calloc(10, sizeof(char));
    char *path_to_output_file = calloc(20, sizeof(char));
    strcpy(path_to_output_file, "out/test");
    sprintf(buffer, "%d.out", i);
    strcat(path_to_output_file, buffer);
    free(buffer);
    return path_to_output_file;
}

/*
    Functia care ne citeste din fisierul de input numerele asupra carora va trebui sa aplicam unul dintre cei doi algoritmi.
*/
int *read_from_input_file(FILE *fin, int *n)
{
    /*
        Recomandarea pentru format-ul input-ului:
            -pe prima linie un numar intreg ce reprezinta numarul de elemente al secventei ce urmeaza sa o citim;
            -pe a doua linia secventa de numere asupra carora va trebui sa aplicam unul dintre teste;
    */
    int *sequence;
    fscanf(fin, "%d", n);
    sequence = calloc((*n) + 1, sizeof(int));
    for (int i = 0; i < (*n); i++)
    {
        fscanf(fin, "%d ", sequence + i);
    }
    fscanf(fin, "\n");
    return sequence;
}

/*
    Functie care ne scrie in fisierul de output toate numerele prime gasite in secventa de numere luata din input.
*/
void write_in_output_file(FILE *fout, int *sequence_of_primes, int m)
{
    /*
        Recomandarea de afisare data in cerinta temei:
            -pe prima linie valoarea numarului M, care reprezinta cate numere prime am gasit in secventa de input;
            -secventa de numere prime gasite in secventa primita ca input;
    */
    fprintf(fout, "%d\n", m);
    for (int i = 0; i < m; i++)
    {
        fprintf(fout, "%d ", *(sequence_of_primes + i));
    }
    fprintf(fout, "\n");
    fclose(fout);
    free(sequence_of_primes);
}

/*
    Functie care ne creeaza numele unui fisier de ref
*/
char *create_reference_filename(int i)
{
    char *buffer = calloc(10, sizeof(char));
    char *path_to_output_file = calloc(20, sizeof(char));
    strcpy(path_to_output_file, "ref/test");
    sprintf(buffer, "%d.ref", i);
    strcat(path_to_output_file, buffer);
    free(buffer);
    return path_to_output_file;
}

/*
    Functie care primeste o secventa de numere prime(secventa obtinuta in urma rularii unui anumit test) si
verifica cate din numerele din aceasta secventa se regasesc si in ref-ul definit pentru respectivul test.
*/
double check_correctness(int *sequence_of_primes, int n, int test_number)
{
    int k = 0;
    double correctness = 0;
    int *n_correct = calloc(1, sizeof(int));
    char *ref_file_name = create_reference_filename(test_number);
    FILE *refin = fopen(ref_file_name, "r");

    if (refin == NULL)
    {
        printf("ERROR! opening file\n");
        exit(1);
    }

    int *correct_sequence = read_from_input_file(refin, n_correct);

    fclose(refin);

    /*
        Inseamna ca secventa gasita de noi are mai putine elemente decat secventa corecta asa ca vom numara
    cate elemente din secventa noastra se regasesc si in secventa corecta pentru a realiza o anumita probabilitate.
        O observatie ar fi fost ca am fi putut face direct n/n_correct si obtineam o probabilitate, dar poate printre
    cele n numere gasite de noi cu ajutorul algoritmilor se afla si numere compuse nu doar numere prime.
    */
    if (*n_correct == 0 && n == 0)
    {
        correctness = 100;
        return correctness;
    }
    if (n < *n_correct)
    {
        for (int i = 0; i < n; i++)
        {
            if (sequence_of_primes[i] == correct_sequence[i])
                k++;
        }
    }
    else if (n == *n_correct)
    {
        for (int i = 0; i < n; i++)
        {
            if (sequence_of_primes[i] == correct_sequence[i])
                k++;
        }
    }
    else if (n > *n_correct)
    {
        if (*n_correct == 0)
        {
            return 0;
        }
        else
        {
            for (int i = 0; i < *n_correct; i++)
            {
                if (sequence_of_primes[i] == correct_sequence[i])
                    k++;
            }
            if (k == 0)
                return 0;
            else
            {
                k = k - (n - (*n_correct));
            }
        }
    }

    correctness = (double)k / (*n_correct);

    correctness *= 100; //Pentru a obtine un procent

    return correctness;
}

