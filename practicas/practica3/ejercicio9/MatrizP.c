/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 3 Arquitectura de Computadores
Version:0.1

EJERCICIO 9
Implementar en paralelo la multiplicación de matrices cuadradas con OpenMP.
Use las directivas, las cláusulas y las funciones de entorno que considere oportunas.
Se debe paralelizar también la inicialización de las matrices.

A = B • C;

Para compilar: gcc -O2 MatrizP.c -o MatrizP -fopenmp
Para ejecutar use: MatrizP longitud
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define PRINTF_ALL

int main(int argc,char **argv) {
    unsigned int N,i,j,k,resultado;
    double cgt1,cgt2;
    double ncgt; //para tiempo de ejecución
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


    #pragma omp parallel for
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            matrizB[i][j]=2;
            matrizC[i][j]=1;
        }
    }
    //inicializamosla matriz

    cgt1=omp_get_wtime();
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            resultado=0;
            #pragma omp parallel for reduction(+:resultado)
            for (k=0; k<N; k++) {
                resultado+=matrizB[i][k]*matrizC[k][j];
            }
            matrizA[i][j]=resultado;
        }
    }
    //hacemos el producto de la matriz por la matriz y lo guardamso en la matriz.
    cgt2=omp_get_wtime();
    ncgt=cgt2-cgt1;



    //Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Matriz:%u\n",ncgt,N);
    printf("MAtriz resultado\n");
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            printf("%f ",matrizA[i][j]);
        }
        printf("\n");
    }
#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño MAtri:%u\n",ncgt,N);
    printf("Primer componente de la matriz resultado [%f] y el ultimo componente de la matriz resultado [%f]\n",matrizA[0][0],matrizA[N-1][N-1]);
#endif


    for(i=0; i<N; i++) free(matrizB[i]);
    free(matrizB);
    for(i=0; i<N; i++) free(matrizC[i]);
    free(matrizC);
    for(i=0; i<N; i++) free(matrizA[i]);
    free(matrizA);
    //eliminamos la memoria dinamica.
}
