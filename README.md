# Biometric-system
## Requisitos
Actualmente la compilación y ejecución solo puede realizarse en sistemas operativos linux, preferentemente Ubuntu o cualquier distro basada en este.

Primero debes verificar si tienes instalado Openssh en tu sistema operativo, con el comando:

```shell
openssl version
```

Esto debe arrojar algo como:

```shell
OpenSSL 1.1.1f  31 Mar 2020
```

También es recomendable instalar el siguiente paquete:

```shell
sudo apt-get install libssl-dev
```

También debes verificar si tienes instalado make en el sistema operativo, con el comando:

```shell
make -version
```

Esto debe arrojar algo como:

```shell
GNU Make 4.2.1
Este programa fue construido para x86_64-pc-linux-gnu
Copyright (C) 1988-2016 Free Software Foundation, Inc.
Licencia GPLv3+: GNU GPL versión 3 o posterior <http://gnu.org/licenses/gpl.html>
Este es software libre: cualquiera es libre para redistribuirlo y modificarlo.
No existe GARANTÍA ALGUNA, hasta los límites permitidos por las leyes aplicables.
```

En caso de no estar instalado, escribir los siguientes comandos en la terminal:

```shell
sudo apt-get update
sudo apt-get install make
```
## Instrucciones de compilación y ejecución
Dirigir a la carpeta test

```sh
cd test
```
Correr el script en la linea de comandos para ejecutar la implementación
```sh
./script.sh
```
Correr el siguiente script para generar la tabla con las estadisticas de tiempos de ejecución
```sh
./conTiempo.sh
```
La tabla generada en Results.txt tendrá lo siguiente:

| FILE | Size | Encrypted | Decrypted | Tiempo Real | CPU | Pulsos de Reloj | Matlab |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Nombre del archivo | Tamaño del archivo original en bytes | Tamaño del archivo cifrado en bytes | Tamaño del archivo descifrado en bytes | Tiempo real en segundos | Tiempo de la CPU en segundos | Número de pulsos de reloj | Tiempo real del programa en Matlab |
