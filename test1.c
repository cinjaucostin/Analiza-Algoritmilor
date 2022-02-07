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

        /*
            Partea de deschidere a fisierelor de input si output.
        */
        char *input_filename = create_input_filename(i);
        char *output_filename = create_output_filename(i);
        FILE *fin = fopen(input_filename, "r");
        FILE *fout = fopen(output_filename, "w");
        /*
            Daca nu s-a putut deschide unul dintre fisierele de intrare sau iesire programul se opreste
        */
        if (fin == NULL || fout == NULL)
        {
            printf("ERROR! opening file\n");
            exit(1);
        }

        /*
            Citirea datelor din fisierul de input.
        */
        sequence = read_from_input_file(fin, n);

        sequence_of_primes = calloc((*n) + 1, sizeof(int));

        /*
            Pentru calculul timpilor
        */
        clock_t start, end;
        start = clock();

        for (int i = 0; i < (*n); i++)
        {
            /*
                Aceasta parte de implementare poate fi modificata pentru etapa urmatoare astfel incat sa putem face niste comparatii
            cat mai precise intre cei doi algoritmi, pentru un numar de iteratii fixat.
            */
            if (isPrimeWithMillerRabin(*(sequence + i), k) == 1)
            {
                *(sequence_of_primes + m) = *(sequence + i);
                m++;
            }
        }

        /*
            Introducem in vectorul de timpi timpul utilizat de algoritm pentru a rula asupra testului cu numarul i.
        */
        end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        times[i] = cpu_time_used;

        /*
            Verificam corectitudinea unui test.
        */
        correctnesses[i] = check_correctness(sequence_of_primes, m, i);

        /*
            Scriere rezultatului in fisierul de output.
        */
        write_in_output_file(fout, sequence_of_primes, m);

        /*
            Inchiderea fisierelor folosite si eliberarea memoriei ocupate.
        */
        fclose(fin);
        free(n);
        free(sequence);
        free(input_filename);
        free(output_filename);
    }


    /*
        Deschidem fisierul in care vom scrie performantele algoritmului.
    */
    strcpy(performance_filename, "performances/miller-rabin_performance");
    FILE *performance_file = fopen(performance_filename, "w");
    if (performance_file == NULL)
    {
        printf("ERROR! opening file\n");
        exit(1);
    }


    fprintf(performance_file, "Numarul de iteratii: %d\n", k);
    for (int i = 1; i <= NR_OF_TESTS; i++)
    {
        fprintf(performance_file, "Miller-Rabin time and correctness for test number %d : %f, %.2f\n", 
                        i, times[i], correctnesses[i]);
        sum += correctnesses[i];
        avg_time += times[i];
    }

    sum = sum / NR_OF_TESTS;
    avg_time = avg_time / NR_OF_TESTS;
    fprintf(performance_file, "Timpul mediu al algoritmului Miller-Rabin pentru un numar de %d iteratii este: %f\n", k, avg_time);
    fprintf(performance_file, "Probabilitatea ca algoritmul Miller-Rabin sa ne dea un rezultat corect pentru %d iteratii este de: %.2f\n", k, sum);

    free(times);
    free(correctnesses);
    fclose(performance_file);
    free(performance_filename);
    return 0;
}