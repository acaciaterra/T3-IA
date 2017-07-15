all:
	g++ src/main.cpp -o rede -Wall -O2 -std=c++11
	g++ src/csv.cpp -o csv -Wall -O2 -std=c++11

rede: main.cpp
	g++ main.cpp -o rede -Wall -O2 -std=c++11

csv: csv.cpp
	g++ csv.cpp -o csv -Wall -O2 -std=c++11

clean:
	rm rede csv
