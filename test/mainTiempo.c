#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include <time.h>
#include "../AES256/opensslaes.h"
#include "../kyber/ref/api.h"
#include "../kyber/ref/fips202.h"
#include "../kyber/ref/randombytes.h"
int main(int argc, char const *argv[])
{
    double sumwtime, utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
    clock_t start_t, end_t, total_t; //para obtener pulsos de reloj

    uswtime(&utime0, &stime0, &wtime0);//Inicia el conteo
    start_t = clock();
    char nombre[100];
    unsigned char pk[pqcrystals_kyber1024_ref_PUBLICKEYBYTES] = "";
    unsigned char sk[pqcrystals_kyber1024_ref_SECRETKEYBYTES] = "";
    unsigned char ss[pqcrystals_kyber1024_ref_BYTES] = "";
    unsigned char ct[pqcrystals_kyber1024_ref_CIPHERTEXTBYTES] = "";
    unsigned char res_shake128[pqcrystals_kyber1024_BYTES] = "";
    // salida para el shake128
    unsigned char output[pqcrystals_kyber1024_BYTES] = "";
    unsigned char res_Kyber1024[pqcrystals_kyber1024_ref_CIPHERTEXTBYTES] = "";

    //?Adquision de datos del vault
    // Se adquiere el nombre del archivo a comprimir por medio de los argumentos en la ejecucion
    strcpy(nombre, argv[1]);
    // Se abre el archivo a comprimir con modo de lectura de bytes
    FILE *archivo = fopen(nombre, "rb");
    if (archivo == NULL)
    {
        printf("Error opening file :c\n");
        return 2;
    }
    //obtener substring del nombre
    memcpy(nombre,&nombre[52],10);
    nombre[10] = '\0';

    // Se posiciona en la posicion 0 y busca el final
    fseek(archivo, 0, SEEK_END);
    unsigned int tamano_archivo = ftell(archivo);
    // Se posiciona de nuevo en la posicion 0
    fseek(archivo, 0, SEEK_SET);
    // Se crea un arreglo del tamano del archivo para almacenar sus bytes
    unsigned char *vault = (unsigned char *)malloc(tamano_archivo);
    // Y otro para el texto cifrado del aes 256
    unsigned char *ciphertext = (unsigned char *)malloc(tamano_archivo);

    // Se leen y almacenan los bytes del archivo en el arreglo de vault

    fread(vault, sizeof(char), tamano_archivo, archivo);

    printf("%s\t%6d\t\t", nombre, tamano_archivo);
    // Se cierra el archivo a comprimir
    fclose(archivo);

    //? se obtiene el shake128 del vault
    shake128(output, pqcrystals_kyber1024_BYTES, vault, tamano_archivo);

    //? Kyber
    pqcrystals_kyber1024_ref_keypair(pk, sk);         // KeyGen
    pqcrystals_kyber1024_ref_enc(ct, ss, pk, output); // Encapsulate

    //? AES 256
    int resultado = encrypt(vault, strlen((unsigned char *)vault), ss, ss, ciphertext);

    int dlen = decrypt(ciphertext, resultado, ss, ss, vault);

    end_t = clock(); //termina el conteo
    uswtime(&utime1, &stime1, &wtime1);//Evalua los tiempos de ejecucion
    printf("%6d\t\t%6d\t\t", resultado, dlen);
    printf("%.5e\t\t",  wtime1 - wtime0);
	printf("%.5e\t\t",  utime1 - utime0);
    printf("%6ld\t\t\t",  end_t-start_t);

    return 0;
}
