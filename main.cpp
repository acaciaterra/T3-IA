#include <bits/stdc++.h>
using namespace std;

#define INF 112345678
#define LAMBDA 1934
#define LEN 32
#define NEURONIOS 32
#define ALPHA 0.1
#define QTDTREINO 1000

double n[NEURONIOS][NEURONIOS][LEN * LEN]; //Matriz de NEURONIOS

void novosneuronios() {
    srand(time(NULL));
    for (int i = 0; i < NEURONIOS; i++)
        for (int j = 0; j < NEURONIOS; j++)
            for (int k = 0; k < LEN * LEN; k++)
                n[i][j][k] = (rand() % 1024) / (double) 1023;
}

double distsimilar(vector<double> a, double b[LEN * LEN]) {
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

void attVizinhanca(vector<double> in, int iBMU, int jBMU) {
    for (int i = 0; i < NEURONIOS; i++)
        for (int j = 0; j < NEURONIOS; j++) {
            double _const = LEN /  (8.0 * distBMU(iBMU, jBMU, i, j)) * ALPHA;
            for (int k = 0; k < LEN * LEN; k++)
                n[i][j][k] += ((in[k] - n[i][j][k]) * _const);
        }
}

pair<int, int> bmu(vector<double> in) {
  double menor = INF; int iBMU = 0, jBMU = 0;
  for (int i = 0; i < NEURONIOS; i++)
    for (int j = 0; j < NEURONIOS; j++) {
      double dist = distsimilar(in, n[i][j]);
      if (dist < menor) { iBMU = i; jBMU = j; menor = dist; }
    }
  return pair<int, int>(iBMU, jBMU);
}

void treina(vector<double> in) { //treina a partir de uma entrada dada
  pair<int, int> _bmu = bmu(in);
  attVizinhanca(in, _bmu.first, _bmu.second);
}

void loadmem() {
  FILE *f = fopen("mem/1", "r");
  for (int i = 0; i < NEURONIOS; i++)
    for (int j = 0; j < NEURONIOS; j++)
      for (int k = 0; k < LEN * LEN; k++) {
        fscanf(f, "%lf", &n[i][j][k]);
      }
  fclose(f);
}

void leTreino() {
  int i, j, k, tmp1;
  char tmp;
  vector<double> in(LEN * LEN);
  vector< pair < vector<double>, int > > entrada;
  FILE *f = fopen("in/in.tra", "r");
  if (f == NULL) { printf("Não foi possível ler arquivo de treinamento.\n"); return; }
  //Le entrada de treinamento
  for (i = 0; i < LAMBDA; i++) {
    for (j = 0; j < LEN; fscanf(f, "%c", &tmp), j++)
      for (k = 0; k < LEN; k++) {
        fscanf(f, "%c", &tmp);
        in[j * LEN + k] = tmp == '1';
      }
    fscanf(f, "%d ", &tmp1);
    entrada.push_back(pair< vector<double>, int>(in, tmp1));
    //treina(in);
  }
  fclose(f);
  //Realiza o treinamento
  for (j = 0; j < QTDTREINO; j++) {
    printf("%d/%d\n", j, QTDTREINO);
    random_shuffle(entrada.begin(), entrada.end());
    for (i = 0; i < (int)entrada.size(); i++) {
      treina(entrada[i].first);
      //printf("%d\n", entrada[i].second);
      //printf("%d: %d de %d\n", j, i, (int)entrada.size());
    }
  }
  //Guarda resultado do treinamento
  f = fopen("mem/1", "w");
  for (i = 0; i < NEURONIOS; i++)
    for (j = 0; j < NEURONIOS; j++) {
      for (k = 0; k < LEN * LEN; k++)
        fprintf(f, "%lf ", n[i][j][k]);
      fprintf(f, "\n");
    }
  fclose(f);
}

void identifica() {
  char tmp;
  int tot, i, j, k, num;
  vector<double> in(LEN * LEN);
  vector<pair<int, int>> mapa[10];
  scanf("%d ", &tot);
  for (i = 0; i < tot; i++) {
    for (j = 0; j < LEN; j++, getchar())
      for (k = 0; k < LEN; k++) {
        scanf("%c", &tmp);
        in[j * LEN + k] = tmp == '0' ? 0 : 1;
      }
    scanf("%d ", &num);
    mapa[num].push_back(bmu(in));
  }
  for (i = 0; i < 10; i++) {
    printf("%d", i);
    for (j = 0; j < (int)mapa[i].size(); j++)
      printf(" %d %d", mapa[i][j].first, mapa[i][j].second);
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
    srand(unsigned(time(0)));
    if ((argc > 1 && !strcmp(argv[1], "-n")) || (argc > 2 && !strcmp(argv[2], "-n"))) {
      //printf("Novos neuronios...\n");
      //getchar();
      novosneuronios();
    } else loadmem();
    //Treinar mtas vezes para mesma entrada e aleatorizar
    if ((argc > 1 && !strcmp(argv[1], "-t")) || (argc > 2 && !strcmp(argv[2], "-t"))) {
      //printf("Realizar treinamento...\n");
      //getchar();
      leTreino();
    }
    identifica();
    //Ler arquivo de teste e "reconhecer" quais neuronios estão de
    //felizes em ver a entrada
    
    /*for (i = 0; i < NEURONIOS; i++)
        for (j = 0; j < NEURONIOS; j++) {
            for (k = 0; k < LEN * LEN; k++)
                printf("%.2lf", n[i][j][k]);
            printf("\n");
            }*/
    return 0;
}
