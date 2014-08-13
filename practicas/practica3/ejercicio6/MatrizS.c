/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 3 Arquitectura de Computadores
Version:0.1

EJERCICIO 6
Implementar un programa secuencial en C que multiplique una matriz triangular por un
vector.

//utilizamos matriz triangular superior
Para compilar: gcc -O2 MatrizS.c -o MatrizS
Para ejecutar use: MatrizS longitud

*/
#include <stdlib.h>
#include <stdio.h>

#define PRINTF_ALL



int main(int argc,char **argv) {
    unsigned int N,i,j;
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


    for(i=0; i<N; i++) {
        v1[i]=3;
    }

    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
            if( i<=j) {//matriz triangular superior igualada a 2
                matriz[i][j]=2;
            }
            else {//matriz triangular inferior igualada a 0
                matriz[i][j]=0;
            }
        }
    }
    //inicializamosla matriz y el vector


    for(i=0; i<N; i++) {
        double result=0;
        for(j=0; j<N; j++) {
            if( i<=j) {//solo multiplicamos por la matriz triangular superior
                result=result+(matriz[i][j]*v1[j]);
            }
        }
        v2[i]=result;
    }
    //hacemos el producto de la matriz por el vector y lo guardamos en le vector.




//Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tamaño Vectores:%u\n",N);
    printf("Vector resultado\n");
    for(i=0; i<N; i++) printf("%f ",v2[i]);
#else
    printf("Tamaño Vectores:%u\n",N);
    printf("Primer componente del vector resultado [%f] y el ultimo componente del vector resultado [%f]\n",v2[0],v2[N-1]);
#endif

    free(v1);
    free(v2);
    for(i=0; i<N; i++) free(matriz[i]);
    free(matriz);
    //eliminamos la memoria dinamica.
}
