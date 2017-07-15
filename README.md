# T3-IA
Trabalho de Inteligêncial Artificial

#### Alunos
  * Acácia dos Campos da Terra
  * João Pedro Winckler bernardi

#### Professor
  * José Carlos Bins Filho

# Descrição O trabalho consiste na criação de uma rede neural para
  reconhecimento de caracteres. Foram criados dois programas para tal, o
  primeiro responsável pela rede se encontra em 'main.cpp' e o segundo
  pega a saída do primeiro e transforma num arquivo .csv para uma melhor
  análise dos resultados, seu código está no arquivo 'csv.cpp'.

# Compilação Os programas podem ser compilado através do comando "make"
  no terminal.

# Execução A execução se dá através de um script './run.sh' que gera a
  saida num arquivo chamado 'res.csv'. Como parametros, podem ser
  passados -t, para realizar 1000 iterações de treinamento(o que pode
  levar certo tempo) e -r para reiniciar os neurônios da rede, que ao
  invés de pegar da memória o seu estado, são aleatorizados novamente.
  > ./run.sh [-r] [-t]

# Entrada A entrada é pega automaticamente do arquivo
  in/in.tes. Consiste de um inteiro N indicando quantos caracteres serão
  entrados e então N pares de caracteres representados numa matriz de
  tamanho 32 x 32 e qual caracter a matriz representa.

# Saída A saída mostrará como a rede está, e qual caracter cada neurônio
  reconhece. Ao fim da tabela, existe a informação da porcentagem de
  acerto da rede.