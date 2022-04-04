#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../kyber/ref/api.h"
#include "../kyber/ref/fips202.h"
int main(int argc, char const *argv[])
{
    char nombre[1000];
    unsigned int outputByteLen=atoi(argv[2]);
    // Se adquiere el nombre del archivo a comprimir por medio de los argumentos en la ejecucion
    strcpy(nombre, argv[1]);

    // Se abre el archivo a comprimir con modo de lectura de bytes
    FILE *archivo = fopen(nombre, "rb");
    if(archivo==NULL){
        printf("Error opening file :c\n");
        return 2;
    }
    // Se posiciona en la posicion 0 y busca el final
    fseek(archivo, 0, SEEK_END);
    printf("holi\n");
    unsigned int tamano_archivo = ftell(archivo);
    // Se posiciona de nuevo en la posicion 0
    fseek(archivo, 0, SEEK_SET);

    printf("Tamano de archivo original: %d bytes\n", tamano_archivo);

    // Se crea un arreglo del tamano del archivo para almacenar sus bytes
    unsigned char *datos = malloc(tamano_archivo);
    unsigned char *output = malloc(tamano_archivo);
    // Se pone todo el arreglo en 0
    memset(datos, 0, tamano_archivo);
    memset(output, 0, tamano_archivo);
    // Se leen y almacenan los bytes del archivo en el arreglo de datos
    fread(datos, 1, tamano_archivo, archivo);
    // Se cierra el archivo a comprimir
    fclose(archivo);
    
    for (int i = 0; i < tamano_archivo; i++)
    {
        printf("%c",(int)datos[i]);
    }
    shake128(output, outputByteLen/8,datos, tamano_archivo);

    for (int i = 0; i < outputByteLen; i++)
    {
        printf("%02x",(int)output[i]);
    }
    return 0;
}
