#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
#define SIZE 2
//const int SIZE=3; 

extern "C" void sgemm_(char* TRANSA,char* TRANSB, int* M,int* N,
int* K,float* ALPHA,float* A,int* LDA,float* B,int* LDB,
float* BETA,float* C, int* LDC);
extern "C" void sgemv_(char* TRANS, int* M, int* N, float* ALPHA, float* A, int* LDA, 
float* X, int* INCX, float* BETA, float* Y, int*
INCY);

extern "C" float scopy_(int* n, float* sx, int* incx, float* sy, int* incy);
extern "C" float snrm2_(int* n, float* vecx, int* incx);


void PrintVecAsMatrix(float* vec, int m, int n);

int main() {
  
char TRANSA = 'T';
char TRANSB = 'T';
//int M = 3; row
//int N = 3; col
int M = SIZE;
int N = SIZE;
// Número de columnas del vector b
int K = 2;
float ALPHA = 1.0;
int LDA = M;
int LDB = N;
float BETA = 1.0;
int LDC = M;
// Incremento para las funciones de blas
int INC = 1;  
int TAM = SIZE*SIZE;

/*
Ejemplo de Wikipedia:
2x + y = 11
5x + 7y = 13
*/

//Matriz A coeficientes del sistema
//float A[SIZE*SIZE]={3.0,-1.0,-1.0,-1.0,3.0,1.0,2.0,1.0,4.0};
float A[SIZE*SIZE]={2.0, 1.0, 5.0, 7.0};
float a_copy[SIZE*SIZE]={0.0};

//Vector b 
//float b[SIZE]={1.0,3.0,7.0};
float b[SIZE]={11.0,13.0};
float x[SIZE]={1.0, 1.0};

//Crear copia de matriz A
scopy_(&TAM,A,&INC,a_copy,&INC);

//Matriz D^-1
float D[SIZE*SIZE]={0.0};
// R = L + U
float R[SIZE*SIZE]={0.0};
// T = D^-1(L+U)
float T[SIZE*SIZE]={0.0};
// C = D^-1*b
float C[SIZE]={0.0};


/*Se calculan D^-1, L y U*/

for (int n = 0; n < N; n++)
{
  // Vector D^-1 (vector para manejar en BLAS)
  D[n*M + n]=1./A[n*M + n];
  A[n*M + n] = 0.0;

  //Diagonales superior e inferior U + L = R
  for (int m = 0; m < M; m++)
  {
    A[n*M + m] = -A[n*M + m];
    R[n*M + m] = A[n*M + m];
  }
}


// Obtener T = D^-1((-L)+(-U))  la función regresa a T traspuesta
sgemm_(&TRANSA,&TRANSB,&M,&N,&K,&ALPHA,D,&LDA,R,&LDB,&BETA,T,&LDC);
cout<<"T: "<<endl;
PrintVecAsMatrix(T, M, N);

//Obtener C = D^-1 * b
sgemv_(&TRANSA, &M, &N, &ALPHA, D, &LDA, b, &INC, &BETA, C, &INC);
cout<<"C: "<<endl;
PrintVecAsMatrix(C, M, 1);
cout<<endl;



/******************************************   Algoritmo de Jacobi  *************************************************/
bool flag=false;
int iteraciones = 0;
float tol = 1e-6;
char trans = 'N';
float c_aux[SIZE]={0.0};
float residuo;
float beta = -1.0;
float b_aux[SIZE]={0.0};

//Copia del vector C en c_aux
scopy_(&N,C,&INC,c_aux,&INC);



while(iteraciones < 1000 && !flag){

	/*Calcular X(n)=T*X(n-1)+C ; esta función recibe trans = 'N' por que el vector T ya se encuentra traspuesto.
  El valor de esta operación se guarda en C. */
  sgemv_(&trans, &M, &N, &ALPHA, T, &LDA, x, &INC, &BETA, C, &INC);

  //Copia de C quien tiene a x(1), en x
  scopy_(&N,C,&INC,x,&INC);
  //Copia del vector C original guardado en c_aux, en C
  scopy_(&N,c_aux,&INC,C,&INC);
  cout<<"x["<<iteraciones<<"]"<<endl;
  PrintVecAsMatrix(x, M, 1);

  //Copia del vector b en b_aux para realizar la operación de comprobación: A*x-b
  scopy_(&N,b,&INC,b_aux,&INC);


  /*Operacion: A*x-b
  Donde A es una matriz de M x N, x y b son vectores de N x 1, 
  el reultado se almacena en b, es por eso que se realiza una copia de este vector antes de realizar la operación. 

  En esta parte del algoritmo ya obtuvimos el vector x que resuelve el sistema de ecuaciones, y que con la operación de
  A*x-b se busca comprobar que tanto se aproxima la solución de los valores del vector x al vector b. */
  sgemv_(&TRANSA, &M, &N, &ALPHA, a_copy, &LDA, x, &INC, &beta, b, &INC);
  /*cout<<"Resultado A*x-b: "<<endl;
  PrintVecAsMatrix(b, M, 1);*/

  //Calcular residuo con la norma del vector b
  residuo = snrm2_(&N,b,&INC);
  //Regresamos el valor de b almecando en b_aux a b
  scopy_(&N,b_aux,&INC,b,&INC);
  cout<<"Residuo: "<<residuo<<endl;

	
	if (residuo < tol)
  {
    flag = true;
  }
		
		
  iteraciones++;
		
}

cout<<"Numero de iteraciones: "<<iteraciones<<endl;
cout<<"Vector x: "<<endl;
PrintVecAsMatrix(x, M, 1);

return 0;

}


//Función para imrpimir matrices 
/*
m => rows
n => cols 
*/
void PrintVecAsMatrix(float* vec, int m, int n){  
    for(int i=0; i<m; i++){
      for(int j=0; j<n; j++){
        cout<<vec[n*i+j]<<" ";
      }
      cout<<endl;
    }

}

