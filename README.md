# MetodoJacobi
*Este repositorio es parte de la materia de Cómputo de Alto Desempeño...*

**Para compilarlo se requiere instalar la biblioteca BLAS que viene incluida en LAPACK en GNU Linux**

*Instalación:*
> 1. sudo apt-get update
> 2. sudo apt-get install build-essential
> 3. sudo apt-get install liblapack-dev
> 4. sudo apt-get install libblas-dev

*Compilación:*
Para compilar el código es necesario situarse en el directorio donde se encuentra el mismo y ejecutar lo siguiente en la terminal:
**g++ nombrearchivo.cpp -o nombrearchivo -lblas** 

o también: **g++ nombrearchivo.cpp -o nombrearchivo.out -lblas** 

y después de compilar, ejecutar de la siguiente forma:
**./nombrearchivo** o **./nombrearchivo.out**

*Documentación:*
Estos son los enlaces que corresponden a la implementación en la que el código esta basado, y la documentación de las funciones empleadas de BLAS.

[Implementación Wikipedia](https://es.wikipedia.org/wiki/M%C3%A9todo_de_Jacobi "Implementación Wikipedia")

[Documentación BLAS](https://www.netlib.org/blas/ "Documentación BLAS")



*Extra:*
Para instalar WSL (Windows Subsystem for Linux) en Windows 10 ;)

[WSL for Windows 10](https://docs.microsoft.com/en-us/windows/wsl/install-win10 "WSL for Windows 10")













