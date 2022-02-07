#include "utils.h"
/*
    Sieve of Erathostenes
    Functie care genereaza un vector cu toate numerele prime mai mici decat numarul n, primit ca parametru.
*/
int *erathostene_sieve(int n, int *k)
{
    int *prime = calloc(n + 1, sizeof(int));
    int *result = calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++)
    {
        prime[i] = 1;
    }

    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p] == 1)
        {
            for (int i = p * p; i <= n; i += p)
            {
                prime[i] = 0;
            }
        }
    }

    for (int p = 2; p <= n; p++)
    {
        if (prime[p] == 1)
        {
            result[*k] = p;
            (*k)++;
        }
    }
    free(prime);
    return result;
}

int main()
{
    for (int i = 17; i <= 18; i++)
    {
        char *input_file_name = create_input_filename(i);
        FILE *fin = fopen(input_file_name, "w");
        int *k = calloc(1, sizeof(int));
        int *prime = erathostene_sieve(NR_FOR_ERATHOSTENE_SIEVE, k);
        if (i == 17)
        {
            fprintf(fin, "%d\n", (*k)/2);
            for (int j = 0; j < (*k)/2; j++)
            {
                fprintf(fin, "%d ", prime[j]);
            }
            fprintf(fin, "\n");
        }
        else {
            fprintf(fin, "%d\n", (*k)/2);
            for (int j = (*k)/2; j < (*k); j++) 
            {
                fprintf(fin, "%d ", prime[j]);
            }
            fprintf(fin, "\n");
        }
        free(prime);
        free(k);
        free(input_file_name);
        fclose(fin);
    }
    return 0;
}