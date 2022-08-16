/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
*
* Curso:       CC3086 - Programación de microprocesadores     Ciclo II - 2022
* Descripción: Generar n cantidad de numeros aleatorios y sumar la primera mitad con 1 hilo, la segunda mitad la debe sumar otro hilo
* Autor:       Angel Castellanos 21700 
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>

#define NTHREADS 2
using namespace std;
//Declaro las variables globales que seran necesarias para los hilos
int tamanoArray;
int *numerosAleatoreos = new int[tamanoArray];
int medioArray;



void *sumar_Array(void *threadNumber){
    long tID;
    // Casting del parametro tipo void a la variable local tipo long
    tID = (long long)threadNumber;

    int suma = 0;

    //Si el tID es 0 significa que es el hilo 1 por lo que suma la 1ra mitad del array
    if(tID == 0){
        for (int i = 0; i < medioArray; ++i) {
            suma += numerosAleatoreos[i];
        }
    }

    //Si el tID es 1 significa que es el hilo 2 por lo que suma la 2da mitad del array
    else{
        for (int i = medioArray; i < tamanoArray; ++i) {
            suma += numerosAleatoreos[i];
        }
    }

    cout << "Suma de la mitad del hilo: "<< tID << " es de: " << suma << endl;

    pthread_exit(NULL);

}

int main()
{
    cout << "Ingrese la cantidad de numeros a generar: " << endl;
    tamanoArray;
    cin >> tamanoArray;

    //random numbers
    cout << "Los numeros aleatoreos son:" << endl;
    for (int i = 0; i < tamanoArray; i++)
    {
        numerosAleatoreos[i] = rand() % 100;
        cout << i << " - " << numerosAleatoreos[i] << endl;

    }

    int rc;
    long i;
    // Declarar una variable tipo pthread_t
    pthread_t tid;

    // Recomendable: declarar tambien un atributo tipo
    // pthread_attr_t
    pthread_attr_t attr;

    // Al usar atributos, inicializar el objeto
    pthread_attr_init(&attr);
    // Modificar el atributo especifico
    // en este caso el atributo setdetachstate = JOINABLE
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    medioArray = tamanoArray/2;


    for (i=0; i<NTHREADS; i++) {

        rc = pthread_create(&tid, &attr, sumar_Array, (void *)i);

        // La variable rc recibe errores en formato entero
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        // Esperar a que cada thread termine en orden
        rc = pthread_join(tid, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    // Liberar espacios de memoria utilizados para atributo
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);


    return 0;
}

