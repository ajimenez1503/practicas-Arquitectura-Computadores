/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 3 Arquitectura de Computadores
Version:0.1

EJERCICIO 8
Implementar un programa secuencial en C que calcule la multiplicación de matrices
cuadradas, B y C:

A = B • C;

Para compilar: gcc -O2 MatrizS.c -o MatrizS
Para ejecutar use: MatrizS longitud
*/

#include <stdlib.h>
#include <stdio.h>
//#define PRINTF_ALL

int main(int argc,char **argv) {
    unsigned int N,i,j,k;
    //Leer argumento de entrada (no de componentes del vector)
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
            matrizC[i][j]=1;
        }
    }
    //inicializamosla matriz y el vector

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            matrizA[i][j]=0;
            for (k=0; k<N; k++) {
                matrizA[i][j]+=matrizB[i][k]*matrizC[k][j];
            }
        }
    }
    //hacemos el producto de la matriz por la matriz y la guardamos en la otra matriz



//Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tamaño Vectores:%u\n",N);
    printf("Vector resultado\n");
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%f ",matrizA[i][j]);
        }
        printf("\n");
    }
#else
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
