/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 4 Arquitectura de Computadores
Version:0.1

EJERCICIO 1A
Implementar un programa secuencial en C que calcule la multiplicación de matrices
cuadradas, B y C.

A = B • C;

Relizar las modificaciones necearias para reducir el tiempo de ejecución.

Para compilar: gcc -O2 MatrizS.c -o MatrizS -lrt
Para ejecutar use: MatrizS longitud
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
//#define PRINTF_ALL


void multiplicar(double ** A,double **B,double **C,int n);

int main(int argc,char **argv) {
    unsigned int N,i,j,k;
    struct timespec cgt1,cgt2;
    double ncgt; //para tiempo de ejecución
    //Leer argumento de entrada (no de componentes de la matriz)
    if (argc<2) {
        printf("Faltan no componentes del vector\n");
        exit(-1);
    }
    N=atoi(argv[1]);
    double **matrizA,**matrizC,**matrizB;
    matrizB=(double **) malloc(N*sizeof(double *));
    for(i=0; i<N; i++) matrizB[i]=(double *) malloc(N*sizeof(double));

    matrizC=(double **) malloc(N*sizeof(double *));
    for(i=0; i<N; i++) matrizC[i]=(double *) malloc(N*sizeof(double));

    matrizA=(double **) malloc(N*sizeof(double *));
    for(i=0; i<N; i++) matrizA[i]=(double *) malloc(N*sizeof(double));
    //reservamos memoria dinamica.



    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            matrizB[i][j]=2;
            matrizC[j][i]=1;//modificamos la inicializacion por filas.
        }
    }
    //inicializamosla matriz y el vector

    clock_gettime(CLOCK_REALTIME,&cgt1);

    multiplicar(matrizA,matrizB,matrizC,N);

    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
         (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    //hacemos el producto de las matries





//Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Tamaño Vectores:%u\n",N);
    printf("Vector resultado\n");
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%f ",matrizA[i][j]);
        }
        printf("\n");
    }
#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Tamaño Vectores:%u\n",N);
    printf("Primer componente del vector resultado [%f] y el ultimo componente del vector resultado [%f]\n",matrizA[0][0],matrizA[N-1][N-1]);
#endif


    for(i=0; i<N; i++) free(matrizB[i]);
    free(matrizB);
    for(i=0; i<N; i++) free(matrizC[i]);
    free(matrizC);
    for(i=0; i<N; i++) free(matrizA[i]);
    free(matrizA);
    //eliminamos la memoria dinamica.
}


void multiplicar(double ** A,double ** B,double ** C,int N) {
    int i,j,k;
    double aux1,aux2,aux3,aux4;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {//modificamos el acceso a la matriz para que se realice por columnas y no por filas
							//mejorando asi el acceso a memoria secuencial.		
            A[i][j]=0;
            aux1=0.0,aux2=0.0,aux3=0.0,aux4=0.0;
            for (k=0; k<N; k+=4) {
                aux1+=B[i][k]*C[j][k];//desenrollado de bucle
                aux2+=B[i][k+1]*C[j][k+1];
                aux3+=B[i][k+2]*C[j][k+2];
                aux4+=B[i][k+3]*C[j][k+3];
            }
            A[i][j]=aux1+aux2+aux3+aux4;
        }
    }
}
