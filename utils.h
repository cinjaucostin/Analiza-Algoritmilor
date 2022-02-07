#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NR_OF_TESTS 18
#define NR_FOR_ERATHOSTENE_SIEVE 5000

int power (long long b, unsigned int e, int p);
int d_calculator (int n);
int cmmdc (int a, int b);

/*
    Implementarea celor doi algoritmi.
*/
int MillerRabinTest (int d, int n);
int isPrimeWithMillerRabin (int n, int k);
int isPrimeWithFermat (int n, int k);

/*
    Pentru fisierele de testare.
*/
char *create_input_filename(int i);
char *create_output_filename(int i);
int *read_from_input_file(FILE *fin, int *n);
void write_in_output_file(FILE *fout, int *sequence_of_primes, int m);
char *create_reference_filename(int i);
double check_correctness(int *sequence_of_primes, int n, int test_number);

#endif