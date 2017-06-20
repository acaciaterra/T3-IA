#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define MAX 1123456
#define QTD 10
#define LAMBDA 930
#define LEN 32

char vect[QTD][MAX];
char name[QTD][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

void getinfo() {
    int i, pos;
    FILE *f;
    char tmp[MAX], pasta[MAX] = {"mem/"};
    memset(vect, 0, sizeof(vect));
    pos = strlen(pasta);
    pasta[pos + 1] = '\0';
    for (i = 0; i < QTD; i++) {
        pasta[pos] = name[i][0];
        f = fopen(pasta, "r+");
        if (f == NULL) {
            printf("%s: deu merda...\n", pasta);
            continue;
        }
        while (fgets(tmp, sizeof(tmp), f) != NULL)
            { tmp[strlen(tmp) - 1] = '\0'; strcat(vect[i], tmp); }
        fclose(f);
    }
}

void att(int index, char in[MAX]) {
    for (int i = 0; i < LEN * LEN; i++)
        if (vect[index][i] != in[i])
            if (!(rand() % 4)) vect[index][i] = in[i]; //25 %
    char novo[LEN][LEN + 1];
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++)
            novo[i][j] = vect[index][j * LEN + i];
        novo[i][LEN] = '\0';
    }
    FILE *f;
    f = fopen(name[index], "w");
    for (int i = 0; i < LEN; i++)
        fprintf(f, "%s\n", novo[i]);
    fclose(f);
}

int best(int MU[QTD]) {
    int maior = 0;
    for (int i = 1; i < QTD; i++)
        if (MU[i] > MU[maior])
            maior = i;
    return maior;
}

int check(char in[MAX]) {
    int i, d, MU[QTD], bmu;
    memset(MU, 0, sizeof(MU));
    for (d = 0; d < QTD; d++)
        for (i = 0; i < LEN * LEN; i++)
            MU[d] += in[i] != vect[d][i];
    bmu = best(MU);
    att(bmu, in);
    return bmu;
}

void getin(char in[MAX], int &expout) {
    char tmp[MAX];
    in[0] = '\0';
    for (int i = 0; i < LEN; i++) {
        fgets(tmp, sizeof(tmp), stdin);
        tmp[strlen(tmp) - 1] = '\0';
        strcat(in, tmp);
    }
    scanf(" %d ", &expout);
}

void treina() {
    int i, expout, ret;
    char in[MAX] = {""};
    printf("E: expected output\nO: output\n\nE | O\n");
    for (i = 0; i < LAMBDA; i++) {
        getin(in, expout);
        ret = check(in);
        printf("%d | %d\n", expout, ret);
    }
}

int main(void) {
    getinfo(); // Recupera a informação das outras execuções.
    treina();
    return 0;
}
