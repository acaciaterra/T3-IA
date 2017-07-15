#!/bin/bash
par=""
for i in $*; do
    echo $i;
    par="$par $i"
done;
echo $par;
./rede $par < in/in.tes > tmp.out;
./csv < tmp.out > res.csv
rm tmp.out
