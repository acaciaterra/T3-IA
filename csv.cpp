#include <bits/stdc++.h>
using namespace std;

#define NEURONIOS 32

int identifica(int x, int y) {
  if ((x > 0 && x <= 4 && y <= 9 && y <= 12) || (x >= 5 && x < 12 && y > 5 && y < 15)) return 0;
  if (x > 8 && x <= 24 && y > 27) return 1;
  if ((x > 27 && y > 21) || (x > 24 && y > 25)) return 2;
  if (x >= 22 && y < 8) return 3;
  if ((x < 5 && y > 12 && y <= 26) || (x < 4 && y >= 27 && y < 29) || (x < 2 && y >= 29)) return 4;
  if (((x > 13 && x < 22 &&  y > 11 && y < 15)) || (x > 16 && x < 26 && y >= 14 && y <= 20) || (x > 19 && x < 23 && y == 21)) return 5;
  if ((x < 12 && y < 5) || (x < 5 && y < 9)) return 6;
  if (x >= 27 && y < 21) return 7;
  if ((x > 8 && x < 15 && y <= 20 && y > 16) || (x > 9 && x <= 19 && y > 20 && y < 27) || (x >= 20 && x < 28 && y > 21 && y < 25) || (x > 24 && x < 28 && y >= 20 && y <= 21)) return 8;
  if ((x > 12 && x < 22 &&  y < 9) || (x > 1 && x < 4 && y > 30) || (x >= 4 && x <= 8 && y > 26)) return 9;
  printf("UEPA");
  return -1;
}

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
      //set<int> x; int first = 1;
      num = 0; x = 0;
      for (k = 0; k < 10; k++){
        if (neu[i][j][k] > 0) {
          printf("(%d,%d),", k, neu[i][j][k]);
        }
        if (neu[i][j][k] > x) {
          x = neu[i][j][k];
          num = k;
        }
      }
              //if (neu[i][j][k] == 0) continue;
        /*if (x.find(k) == x.end()) {
          x.insert(k);
          printf("%s%d", first ? "": ",", k);
          first = 0;
          }*/
      //if (x) printf("%d;", num);
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
      printf(">>>%d\n", identifica(i, j));
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
    }
  }
  printf("\n\nTaxa de acerto: %lf%%\n;", certos * 100 / (double) (tot));
  return 0;
}
