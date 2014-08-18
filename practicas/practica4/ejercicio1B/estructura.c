/* (C) Programmed by:
   Antonio Jimenez Martínez


Practica 4 Arquitectura de Computadores
Version:0.1

EJERCICIO 1B

Para compilar: g++ -O2 estructura.c -lrt

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
//#define PRINTF_ALL
struct estructura {
    int a;
    int b;
};
estructura s[5000];
void multiplicar(int * R,estructura * s);
main()
{

    int  R[40000];
    double ncgt; //para tiempo de ejecución
    struct timespec cgt1,cgt2;
    int ii,i;
    int X1,X2;
    //inicializacion
    for(i=0; i<5000; i++) {
        s[i].a=2;
        s[i].b=3;
    }
    clock_gettime(CLOCK_REALTIME,&cgt1);
    multiplicar(R,s);
    clock_gettime(CLOCK_REALTIME,&cgt2);
    ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+
         (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    printf("Tiempo(seg.):%11.9f \n",ncgt);
#ifdef PRINTF_ALL
    for (ii=0; ii<=40000; ii++) {
        printf("%d ",R[ii]);
    }
    printf("\n");
#endif
}

void multiplicar(int * R,estructura * s) {
    int ii,i,X1,X2;
    for (ii=0; ii<=40000; ii++) {
        for(i=0; i<5000; i=i+5) {//unificacion de los dos bubles
								 //desenrrollado de buble
								 //acceso ordenado a la estrucctura, es decir promero la varibles a y despues la b
            X1+=2*s[i].a+ii;
            X2+=3*s[i].b-ii;
            X1+=2*s[i+1].a+ii;
            X2+=3*s[i+1].b-ii;
            X1+=2*s[i+2].a+ii;
            X2+=3*s[i+2].b-ii;
            X1+=2*s[i+3].a+ii;
            X2+=3*s[i+3].b-ii;
            X1+=2*s[i+4].a+ii;
            X2+=3*s[i+4].b-ii;
        }
        if (X1>X2) {
            R[ii]=X2;
        }
        else {
            R[ii]=X1;
        }
    }
}
