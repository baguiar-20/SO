#!/bin/bash

# gcc -o tbl tbl.c
# ./tbl 10

for ((i=1; i< 1000; i++)) do # numero de paginas
    gcc -o tbl tbl.c
    ./tbl ${i} 10000 >> tam_paginaOtimizado.txt
done