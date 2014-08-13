/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 3 Arquitectura de Computadores
Version:0.1

EJERCICIO 7
Implementar en paralelo la multiplicación de una matriz triangular por un vector
utilizando la directiva for de OpenMP.
Añadir lo necesario para que el usuario pueda fijar la planificación de tareas usando la variable
de entorno OMP_SCHEDULE.



Para compilar: gcc -O2 MatrizP.c -o MatrizP -fopenmp
Para ejecutar use: MatrizP longitud
*/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

//#define PRINTF_ALL

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
        #pragma omp for schedule(runtime)
        for(i=0; i<N; i++) v1[i]=3;

        #pragma omp for schedule(runtime)
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                if( i<=j) {
                    matriz[i][j]=2;
                }
                else {
                    matriz[i][j]=0;
                }
            }
        }

    }
    //inicializamosla matriz y el vector


    cgt1=omp_get_wtime();
    for(i=0; i<N; i++) {
        resultado=0;
        #pragma omp parallel for reduction(+:resultado) schedule(runtime)
        for(j=0; j<N; j++) {
            if( i<=j) {
                resultado+=(matriz[i][j]*v1[j]);
            }
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
