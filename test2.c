#include "utils.h"

int main()
{
    int k;
    double sum = 0, avg_time = 0;
    double *times = calloc(NR_OF_TESTS + 1, sizeof(double));
    double *correctnesses = calloc(NR_OF_TESTS + 1, sizeof(double));
    char *performance_filename = calloc(50, sizeof(char));
    printf("Introdu numarul de iteratii: ");
    scanf("%d", &k);

    for (int i = 1; i <= NR_OF_TESTS; i++)
    {
        int m = 0;
        int *n = calloc(1, sizeof(int)), *sequence, *sequence_of_primes;

        char *input_filename = create_input_filename(i);
        char *output_filename = create_output_filename(i);
        FILE *fin = fopen(input_filename, "r");
        FILE *fout = fopen(output_filename, "w");
        if (fin == NULL || fout == NULL)
        {
            printf("ERROR! can't open file\n");
            exit(1);
        }

        sequence = read_from_input_file(fin, n);

        sequence_of_primes = calloc((*n) + 1, sizeof(int));

        /*
            Pentru calculul timpilor:
                
        */
        clock_t start, end;
        start = clock();

        //int k = rand() % 100 + 90;
        for (int i = 0; i < (*n); i++)
        {
            if (isPrimeWithFermat(*(sequence + i), k) == 1)
            {
                *(sequence_of_primes + m) = *(sequence + i);
                m++;
            }
        }

        end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        times[i] = cpu_time_used;

        correctnesses[i] = check_correctness(sequence_of_primes, m, i);

        write_in_output_file(fout, sequence_of_primes, m);


        fclose(fin);
        free(n);
        free(sequence);
        free(input_filename);
        free(output_filename);
    }

    strcpy(performance_filename, "performances/fermat_performance");
    FILE *performance_file = fopen(performance_filename, "w");
    if (performance_file == NULL)
    {
        printf("ERROR! opening file\n");
        exit(1);
    }


    fprintf(performance_file, "Numarul de iteratii: %d\n", k);
    for (int i = 1; i <= NR_OF_TESTS; i++)
    {
        fprintf(performance_file, "Fermat time and correctness for test number %d : %f, %.2f\n", 
                        i, times[i], correctnesses[i]);
        sum += correctnesses[i];
        avg_time += times[i];
    }

    sum = sum / NR_OF_TESTS;
    avg_time = avg_time / NR_OF_TESTS;
    fprintf(performance_file, "Timpul mediu al algoritmului Fermat pentru un numar de %d iteratii este: %f\n", k, avg_time);
    fprintf(performance_file, "Probabilitatea ca algoritmul Fermat sa ne dea un rezultat corect pentru %d iteratii este de: %.2f\n", k, sum);

    free(times);
    free(correctnesses);
    fclose(performance_file);
    free(performance_filename);
    return 0;
}