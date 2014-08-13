/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 1 Arquitectura de Computadores
Version:0.1

EJERCICIO 8
Implementar un programa en C con OpenMP, que calcule
en paralelo la suma de dos vectores usando las parallel
y sections/section, esdecir, hay que repartir el trabajo
(tareas) entre varios threads usando sections/section.
Se debe paralelizar también las tareas asociadas a la inicialización de los vectores.
Para obtener este tiempo usar la función omp_get_wtime().

Para compilar: gcc -O2 -fopenmp SumaVectores.c -o SumaVectores -lrt
Para ejecutar use: SumaVectoresC longitud

*/
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#include <omp.h>//biblioteca omp
#define PRINTF_ALL // comentar para quitar el printf ...
#define MAX 33554432 //=2^25

double v1[MAX], v2[MAX], v3[MAX];
int main(int argc, char** argv) {
    int i;
    double ncgt; //para tiempo de ejecución
    //Leer argumento de entrada (no de componentes del vector)
    if (argc<2) {
        printf("Faltan no componentes del vector\n");
        exit(-1);
    }
    unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
#ifdef VECTOR_GLOBAL
    if (N>MAX) N=MAX;
#endif

    //Inicializar vectores
    #pragma omp parallel sections
    {
        #pragma omp section
        for(i=0; i<N; i+=3) {
            v1[i] = N*0.1+i*0.1;
            v2[i] = N*0.1-i*0.1; //los valores dependen de N
        }
        #pragma omp section
        for(i=1; i<N; i+=3) {
            v1[i] = N*0.1+i*0.1;
            v2[i] = N*0.1-i*0.1; //los valores dependen de N
        }
        #pragma omp section
        for(i=2; i<N; i+=3) {
            v1[i] = N*0.1+i*0.1;
            v2[i] = N*0.1-i*0.1; //los valores dependen de N
        }
    }
    double start,end;

    start=omp_get_wtime();
    //Calcular suma de vectores
    #pragma omp parallel sections
    {
        #pragma omp section
        for(i=0; i<N; i+=3)
            v3[i] = v1[i] + v2[i];

        #pragma omp section
        for(i=1; i<N; i+=3)
            v3[i] = v1[i] + v2[i];

        #pragma omp section
        for(i=2; i<N; i+=3)
            v3[i] = v1[i] + v2[i];
    }
    end=omp_get_wtime();

    ncgt=end-start;
    //Imprimir resultado de la suma y el tiempo de ejecución
#ifdef PRINTF_ALL
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\n",ncgt,N);
    for(i=0; i<N; i++)
        printf("/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",i,i,i,v1[i],v2[i],v3[i]);
#else
    printf("Tiempo(seg.):%11.9f\t / Tamaño Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / /V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n",ncgt,N,v1[0],v2[0],v3[0],N-1,N-1,N-1,v1[N-1],v2[N-1],v3[N-1]);
#endif

    return 0;
}
