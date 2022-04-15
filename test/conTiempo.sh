#!/bin/sh
export CFLAGS="-I/usr/local/opt/openssl@1.1/include"
export NISTFLAGS="-I/usr/local/opt/openssl@1.1/include"
export LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"

cd ../kyber/ref

make shared

cd ../../test

gcc mainTiempo.c "../kyber/ref/libpqcrystals_fips202_ref.so" "../kyber/ref/libpqcrystals_kyber1024_ref.so" "../kyber/ref/randombytes.c" "../AES256/opensslaes.c" -lcrypto -lssl

echo "File \t File size \t  Encrypted File size \t Decrypted File size" > Results.txt
for file in ../AutomatedFuzzyVaultFingerprint/ExpOctubre/Vaults/*; do
    ./a.out ${file} >> Results.txt
done
