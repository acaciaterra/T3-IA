all:
	g++ main.cpp -o rede -Wall -O2 -std=c++11
	g++ csv.cpp -o csv -Wall -O2 -std=c++11

rede: main.cpp
	g++ main.cpp -o rede -Wall -O2 -std=c++11

csv: csv.cpp
	g++ csv.cpp -o csv -Wall -O2 -std=c++11
