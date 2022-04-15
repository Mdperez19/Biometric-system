#!/bin/sh
export CFLAGS="-I/usr/local/opt/openssl@1.1/include"
export NISTFLAGS="-I/usr/local/opt/openssl@1.1/include"
export LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"

cd ../kyber/ref

make shared

cd ../../test

gcc mainTiempo.c "../kyber/ref/libpqcrystals_fips202_ref.so" "../kyber/ref/libpqcrystals_kyber1024_ref.so" "../kyber/ref/randombytes.c" "../AES256/opensslaes.c" tiempo.c -lcrypto -lssl

echo "File\t\t Size \t  Encrypted \t Decrypted \t Tiempo real \t CPU \t\t Pulsos de Reloj \t\t Matlab" > Results.txt
for file in ../AutomatedFuzzyVaultFingerprint/ExpOctubre/Vaults/*; do
    ./a.out ${file} >> Results.txt
    sed '5!d' ../AutomatedFuzzyVaultFingerprint/ExpOctubre/Resultados/tiempo.txt >> Results.txt
    echo '\n' >> Results.txt
done
