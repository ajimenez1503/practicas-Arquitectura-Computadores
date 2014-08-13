/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 2 Arquitectura de Computadores
Version:0.1

EJERCICIO 8
Implementar un programa secuencial en C que calcule el producto de una matriz cuadrada,
M, por un vector, v1
v2 = M • v1; v2(i) = ∑ M(i, k) • v(k), i = 0, ...N - 1

Para compilar: gcc -O2 MatrizS.c -o MatrizS -lrt
Para ejecutar use: MatrizS longitud

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>
//#define PRINTF_ALL


int main(int argc,char **argv) {
    unsigned int N=3,i,j;

    struct timespec cgt1,cgt2;
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


    for(i=0; i<N; i++) v1[i]=2;
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            matriz[i][j]=2;
        }
    }
    //inicializamosla matriz y el vector


    clock_gettime(CLOCK_REALTIME,&cgt1);
    for(i=0; i<N; i++) {
        double result=0;
        for(j=0; j<N; j++) {
            result=result+(matriz[i][j]*v1[j]);
        }
        v2[i]=result;
    }
    //hacemos el producto de la matriz por le vector y lo guardamos en le vector.


    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+(double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));


    //Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Vector resultado\n");
    for(i=0; i<N; i++) printf("%f ",v2[i]);
#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Primer componente del vector resultado [%f] y el ultimo componente del vector resultado [%f]\n",v2[0],v2[N-1]);
#endif

    free(v1);
    free(v2);
    for(i=0; i<N; i++) free(matriz[i]);
    free(matriz);
    //eliminamos la memoria dinamica.
}
