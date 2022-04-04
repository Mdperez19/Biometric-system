#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AES256/opensslaes.h"
#include "../kyber/ref/api.h"
#include "../kyber/ref/fips202.h"
#include "../kyber/ref/randombytes.h"
int main(int argc, char const *argv[])
{
    char nombre[1000];
    unsigned char pk[pqcrystals_kyber1024_ref_PUBLICKEYBYTES]="";
    unsigned char sk[pqcrystals_kyber1024_ref_SECRETKEYBYTES]="";
    unsigned char ss[pqcrystals_kyber1024_ref_BYTES]=""; 
    unsigned char ct[pqcrystals_kyber1024_ref_CIPHERTEXTBYTES]="";
    unsigned char res_shake128[pqcrystals_kyber1024_BYTES]="";
    //salida para el shake128
    unsigned char output[pqcrystals_kyber1024_BYTES]="";
    unsigned char res_Kyber1024[pqcrystals_kyber1024_ref_CIPHERTEXTBYTES]="";
    // Se adquiere el nombre del archivo a comprimir por medio de los argumentos en la ejecucion
    strcpy(nombre, argv[1]);

    // Se abre el archivo a comprimir con modo de lectura de bytes
    FILE *archivo = fopen(nombre, "rb");
    if (archivo == NULL)
    {
        printf("Error opening file :c\n");
        return 2;
    }
    // Se posiciona en la posicion 0 y busca el final
    fseek(archivo, 0, SEEK_END);
    unsigned int tamano_archivo = ftell(archivo);
    // Se posiciona de nuevo en la posicion 0
    fseek(archivo, 0, SEEK_SET);

    printf("Tamano de archivo original: %d bytes\n", tamano_archivo);

    // Se crea un arreglo del tamano del archivo para almacenar sus bytes
    unsigned char *vault = malloc(tamano_archivo);
// Y otro para el texto cifrado del aes 256
    unsigned char *ciphertext = malloc(tamano_archivo);
    
    // Se pone todo el arreglo en 0
    memset(vault, 0, tamano_archivo);
    memset(output, 0, pqcrystals_kyber1024_BYTES);
    // Se leen y almacenan los bytes del archivo en el arreglo de vault
    fread(vault, 1, tamano_archivo, archivo);
    // Se cierra el archivo a comprimir
    fclose(archivo);

    // file printing
    /* for (int i = 0; i < tamano_archivo; i++)
    {
        printf("%c",(int)vault[i]);
    } */

    //se obtiene el shake128 del vault
    shake128(output, pqcrystals_kyber1024_BYTES, vault, tamano_archivo);

    for (int i = 0; i < pqcrystals_kyber1024_BYTES; i++)
    {
        char byte[3];
        sprintf(byte, "%02x", (int)output[i]);
        strcat(res_shake128, byte);
    }
    printf("shake128: %s\n", res_shake128);

    //Kyber
    pqcrystals_kyber1024_ref_keypair(pk, sk); //KeyGen
    pqcrystals_kyber1024_ref_enc(ct, ss, pk,res_shake128); // Encapsulate

    /* for(int j=0;j<pqcrystals_kyber1024_ref_CIPHERTEXTBYTES;j++){
        char byte[3];
        sprintf(byte, "%02x", ct[j]);
        strcat(res_Kyber1024, byte);
    } 

   printf("Kyber1024: %s\n", res_Kyber1024);
   */
    printf("Kyber1024 ss: ");
    for(int j=0;j<pqcrystals_kyber1024_ref_BYTES;j++){
        printf("%02x",ss[j]);
    } 
    printf("\n");

    //AES 256
    encrypt(vault, strlen((unsigned char *)vault), ss, ss, ciphertext);
    printf("AES 256: ");
    for (int i = 0; i < tamano_archivo; i++)
    {
        printf("%02x",ciphertext[i]);
    }
    printf("\n");



    /* ciphertext[tamano_archivo] = '\0';
    int dlen=decrypt(ciphertext, tamano_archivo/8, ss, ss, vault);

    printf("\t%d\n",dlen);
    for (int i = 0; i < tamano_archivo; i++)
    {
        printf("%c",(int)vault[i]);
    } */
    return 0;
}
