/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 2 Arquitectura de Computadores
Version:0.1

EJERCICIO 10
Implementar un programa paralelo en C que calcule el producto de una matriz cuadrada,
M, por un vector, v1
v2 = M • v1; v2(i) = ∑ M(i, k) • v(k), i = 0, ...N - 1

Usa para la comunicación/sincronización la cláusula reduction.


Para compilar: gcc -O2 MatrizS3.c -o MatrizS3 -fopenmp
Para ejecutar use: MatrizS3 longitud

*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define PRINTF_ALL



int main(int argc,char **argv) {
    double resultado;
    unsigned int N=3,i,j;
    double cgt1,cgt2;
    double ncgt; //para tiempo de ejecución
    //Leer argumento de entrada (no de componentes del vector)
    if (argc<2) {
        printf("Faltan no componentes del vector\n");
        exit(-1);
    }
    N=atoi(argv[1]);
    double **matriz,*v1,*v2;
    v1=(double *) malloc(N*sizeof(double));
    v2=(double *) malloc(N*sizeof(double));
    matriz=(double **) malloc(N*sizeof(double *));
    for(i=0; i<N; i++) matriz[i]=(double *) malloc(N*sizeof(double));
    //reservamos memoria dinamica.

    #pragma omp parallel
    {
        #pragma omp for
        for(i=0; i<N; i++) v1[i]=i;

        #pragma omp for
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                matriz[i][j]=i+j;
            }
        }

    }
    //inicializamosla matriz y el vector

    cgt1=omp_get_wtime();
    for(i=0; i<N; i++) {
        resultado=0;
        #pragma omp parallel for reduction(+:resultado)
        for(j=0; j<N; j++) {
            resultado+=(matriz[i][j]*v1[j]);
        }
        v2[i]=resultado;

    }
    //hacemos el producto de la matriz por le vector y lo guardamos en le vector.

    cgt2=omp_get_wtime();
    ncgt=cgt2-cgt1;


    //Imprimir resultadoado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Vector resultadoado\n");
    for(i=0; i<N; i++) printf("%f ",v2[i]);

#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Primer componente del vector resultadoado [%f] y el ultimo componente del vector resultadoado [%f]\n",v2[0],v2[N-1]);
#endif

    free(v1);
    free(v2);
    for(i=0; i<N; i++) free(matriz[i]);
    free(matriz);
    //eliminamos la memoria dinamica.
}
