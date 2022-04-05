export CFLAGS="-I/usr/local/opt/openssl@1.1/include"
export NISTFLAGS="-I/usr/local/opt/openssl@1.1/include"
export LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"

cd ../kyber/ref

make shared

cd ../../test

gcc main.c "../kyber/ref/libpqcrystals_fips202_ref.so" "../kyber/ref/libpqcrystals_kyber1024_ref.so" "../kyber/ref/randombytes.c" "../AES256/opensslaes.c" -lcrypto -lssl

./a.out  ../Biometric-System/resultados/Vault2.txt