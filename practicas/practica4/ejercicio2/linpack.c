
/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 4 Arquitectura de Computadores
Version:0.1

EJERCICIO 2
Implementar un programa secuencial que multiplique un vector por una 
constante y le sume otro vector.

Para compilar: gcc -O2 linpack.c -o linpack -lrt
Para ejecutar use: linpack longitud
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
//#define PRINTF_ALL


void multiplicar(int* A,int* B,int* C,int N,int k);

int main(int argc,char **argv) {
    unsigned int N,i,j,k;
    k=999;//inicializamos contante

    struct timespec cgt1,cgt2;
    double ncgt; //para tiempo de ejecución
    //Leer argumento de entrada (no de componentes de la matriz)
    if (argc<2) {
        printf("Faltan no componentes del vector\n");
        exit(-1);
    }
    N=atoi(argv[1]);
    int *A,*B,*C;

    A=(int *) malloc(N*sizeof(int ));
    B=(int  *) malloc(N*sizeof(int ));
    C=(int  *) malloc(N*sizeof(int ));
    //reservamos memoria dinamica.


    for(i=0; i<N; i++) {
        B[i]=20;
        C[i]=30;

    }
    //inicializamosla matriz y el vector

    clock_gettime(CLOCK_REALTIME,&cgt1);
    multiplicar(A,B,C,N,k);
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
         (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

//Imprimir resultado de la suma y el tiempo de ejecución


#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Vector resultado\n");
    for(i=0; i<N; i++) {
        printf("%d ",A[i]);
    }
    printf("\n");
#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    printf("Primer componente del vector resultado [%d] y el ultimo componente del vector resultado [%d]\n",A[0],A[N-1]);
#endif

    free(B);
    free(C);
    free(A);
    //eliminamos la memoria dinamica.
}

void multiplicar(int* A,int* B,int* C,int N,int k) {
    int i;
    for (i=0; i<N; i++) A[i]= k*B[i] + C[i];
}
