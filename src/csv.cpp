/* Alunos: Acácia dos Campos da Terra e João Pedro Winckler Bernardi
    Professor: José Carlos Bins Filho
    Disciplina: Inteligência Artificial
    Descrição: O trabalho consiste na criação de uma rede neural para
    reconhecimento de caracteres. Foram criados dois programas para tal,
    o primeiro responsável pela rede se encontra em 'main.cpp' e o
    segundo pega a saída do primeiro e transforma num arquivo .csv para
    uma melhor análise dos resultados, seu código está no arquivo
    'csv.cpp'.
 */
#include <bits/stdc++.h>
using namespace std;

#define NEURONIOS 32

int main(void) {
  char tmp;
  int i, j, k, num, x, y;
  int neu[NEURONIOS][NEURONIOS][10];
  memset(neu, 0, sizeof(neu));
  for (i = 0; i < 10; i++) {
    scanf("%d", &num);
    while (getchar() != '\n') {
      scanf("%d %d", &x, &y);
      neu[x][y][num]++;
    }
  }
  for (i = 0; i < NEURONIOS; i++) {
    for (j = 0; j < NEURONIOS; j++) {
      //set<int> s; int first = 1;
      num = 0; x = 0;
      for (k = 0; k < 10; k++) {
        /* if (neu[i][j][k] > 0) {
          printf("(%d,%d),", k, neu[i][j][k]);
          }*/
        if (neu[i][j][k] > x) {
          x = neu[i][j][k];
          num = k;
          }
        //}
        //if (neu[i][j][k] == 0) continue;
      }
      if (x) printf("%d", num);
      //else
      printf(";");
    }
    printf("\n");
  }
  int certos = 0, tot = 0;
    for (i = 0; i < NEURONIOS; i++) {
    for (j = 0; j < NEURONIOS; j++) {
      num = 0; x = 0;
      for (k = 0; k < 10; k++)
        if (neu[i][j][k] > x) {
          x = neu[i][j][k];
          num = k;
        }
      if (x == 0) continue;
      for (k = 0; k < 10; k++) {
        if (k == num) certos += neu[i][j][k];
        tot+= neu[i][j][k];
      }
      
      /*printf(">>>%d\n", identifica(i, j));
      if (identifica(i, j) != -1) {
        certos += neu[i][j][identifica(i, j)];
      } else if(identifica(j, i) != -1) {
        certos += neu[i][j][identifica(j, i)];
      } else {
        printf("<<<%d\n", identifica(j, i));
        printf("Problema no neuronio [%d,%d]. Identificado %d\n", i, j, num);
        for (int m = 0; m < 10; m++){
          printf("(%d,%d);", m, neu[i][j][m]);
        }
        printf("\n");
      }
      for (k = 0; k < 10; k++)
        tot += neu[i][j][k];
      */
    }
  }
  printf("\n\nTaxa de acerto: %lf%%\n;", certos * 100 / (double) (tot));
  return 0;
}
