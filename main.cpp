#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define INF 112345678
#define LAMBDA 930
#define LEN 32
#define NEURONIOS 32
#define ALPHA 0.1

double n[NEURONIOS][NEURONIOS][LEN * LEN]; //Matriz de NEURONIOS

// void att(int index, char in[MAX]) {
//     for (int i = 0; i < LEN * LEN; i++)
//         if (vect[index][i] != in[i])
//             if (!(rand() % 4)) vect[index][i] = in[i]; //25 %
//     char novo[LEN][LEN + 1];
//     for (int i = 0; i < LEN; i++) {
//         for (int j = 0; j < LEN; j++)
//             novo[i][j] = vect[index][j * LEN + i];
//         novo[i][LEN] = '\0';
//     }
//     FILE *f;
//     f = fopen(name[index], "w");
//     for (int i = 0; i < LEN; i++)
//         fprintf(f, "%s\n", novo[i]);
//     fclose(f);
// }

void novosneuronios() {
    srand(time(NULL));
    for (int i = 0; i < NEURONIOS; i++)
        for (int j = 0; j < NEURONIOS; j++)
            for (int k = 0; k < LEN * LEN; k++)
                n[i][j][k] = (rand() % 1000) / (double) 1000;
}

double distsimilar(double a[LEN * LEN], double b[LEN * LEN]) {
    double ret = 0, dif;
    for (int i = 0; i < LEN * LEN; i++) {
        dif = a[i] - b[i];
        ret += (dif * dif);
    }
    return ret;
}

int distBMU(int a, int b, int i, int j) {
    int ret = (a - i) * (a - i) + (b - j) * (b - j);
    return ret + 1;
}

void attVizinhanca(double in[LEN * LEN], int iBMU, int jBMU) {
    for (int i = 0; i < NEURONIOS; i++)
        for (int j = 0; j < NEURONIOS; j++) {
            double _const = LEN /  (2.0 * distBMU(iBMU, jBMU, i, j)) * ALPHA;
            for (int k = 0; k < LEN * LEN; k++)
                n[i][j][k] += ((in[k] - n[i][j][k]) * _const);
        }
}

void treina(double in[LEN * LEN]) { //treina a partir de uma entrada dada
    double menor = INF; int iBMU = 0, jBMU = 0;
    for (int i = 0; i < NEURONIOS; i++)
        for (int j = 0; j < NEURONIOS; j++) {
            double dist = distsimilar(in, n[i][j]);
            if (dist < menor) { iBMU = i; jBMU = j; menor = dist; }
            attVizinhanca(in, iBMU, jBMU);
        }
}

int main(void) {
    novosneuronios();
    FILE *f = fopen("in/1", "r");
    if (f == NULL) { printf("Não foi possível ler entrada.\n"); return 0; }
    int i, j, k;
    double in[LEN * LEN];
    char tmp; int tmp1;
    for (i = 0; i < LAMBDA; i++) {
        printf("%d\n", i);
        for (j = 0; j < LEN; getchar(), j++)
            for (k = 0; k < LEN; k++) {
                fscanf(f, "%c", &tmp);
                in[j * LEN + k] = tmp == '1';
            }
        fscanf(f, "%d ", &tmp1);
        treina(in);
    }

    for (i = 0; i < NEURONIOS; i++)
        for (j = 0; j < NEURONIOS; j++) {
            for (k = 0; k < LEN * LEN; k++)
                printf("%.2lf", n[i][j][k]);
            printf("\n");
        }
    return 0;
}
