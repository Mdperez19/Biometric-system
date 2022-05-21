#!/bin/sh
export CFLAGS="-I/usr/local/opt/openssl@1.1/include"
export NISTFLAGS="-I/usr/local/opt/openssl@1.1/include"
export LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"

cd ../kyber/ref

make shared

cd ../../test

gcc mainTiempo.c "../kyber/ref/libpqcrystals_fips202_ref.so" "../kyber/ref/libpqcrystals_kyber1024_ref.so" "../kyber/ref/randombytes.c" "../AES256/opensslaes.c" tiempo.c -lcrypto -lssl

i=0
#echo "File\t\t Size \t  Encrypted \t Decrypted \t CPU \t\t Pulsos de Reloj \t\t Matlab \t\t Tiempo Total \t\t Diferencia" > Results.txt
echo "File,Size,Encrypted,Decrypted,CPU,Pulsos de Reloj del sistema,Matlab,Pulsos de Reloj de Matlab, Tiempo Total,Diferencia,Diferencia pulsos," > Results.csv
for file in ../AutomatedFuzzyVaultFingerprint/ExpOctubre/Vaults/*; do
    ./a.out ${file} ${i}>> Results.csv
    #sed ${i}'!d' ../AutomatedFuzzyVaultFingerprint/ExpOctubre/Resultados/tiempo.txt >> Results.txt
   i=$((i+1))
done
