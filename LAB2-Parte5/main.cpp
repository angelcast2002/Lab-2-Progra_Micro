/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
*
* Curso:       CC3086 - Programación de microprocesadores     Ciclo II - 2022
* Descripción: Solicitar al usuario un numero entero velocidad, y por medio de 3 hilos hacer:
*              1. Crear un contador que inicie en 0 y termine en 50 con un incremento de 1, en cada ciclo hacer una pausa de 1 segundo.
*              2. Calcular la distancia en base a la velocidad proporcionada y al tiempo del ciclo 1.
*              3. Cada x distancia mostrar un mensaje con la distancia recorrida.
*
* Autor:       Angel Castellanos 21700 
------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
# include <unistd.h>

using namespace std;

//Declaro las variables globales que seran necesarias para los hilos
int velocidad;
int tiempo;
int distancia;
int contador = 50;




void *funTiempo(void *threadNumber){

    for (int i = 0; i < contador; i++)
    {
        tiempo = tiempo + 1;
        cout << "\nEl valor del hilo 1 es: " << tiempo << " segundos." << endl;
        sleep(1);
    }
    
    pthread_exit(NULL);

}

void *funDistancia(void *threadNumber){

    for (int i = 0; i < contador; i++)
    {
        distancia = velocidad * tiempo;
        cout << "\nEn " << tiempo << " segundos, la distancia recorrida es: " << distancia << " metros." << endl;
        sleep(1);
    }
    
    pthread_exit(NULL);

}

void *verificar_distancia(void *threadNumber){
    int primera_vez_diez = 0;
    int primera_vez_veinte = 0;
    int primera_vez_treinta = 0;
    for (int i = 0; i < contador; i++)
    {
        if (distancia >= 10 && distancia < 20 && primera_vez_diez == 0)
        {
            cout << "\nSe han recorrido 10 metros." << endl;
            primera_vez_diez = 1;
        }

        else if (distancia >= 20 && distancia < 30 && primera_vez_veinte == 0)
        {
            cout << "\nSe han recorrido 20 metros." << endl;
            primera_vez_veinte = 1;
        }
        
        else if (distancia >= 30 && primera_vez_treinta == 0)
        {
            cout << "\nSe han recorrido 30 metros." << endl;
            primera_vez_treinta = 1;
        }

        sleep(1);
    }
    
    pthread_exit(NULL);

}

void error_rc(pthread_t tid, int rc){
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    // Esperar a que cada thread termine en orden

}

int main()
{

    cout << "Ingrese la velocidad: " << endl;
    cin >> velocidad;

    int rc;
    long i;
    i = 0;

    // Declarar una variable tipo pthread_t
    pthread_t tid;

    // Recomendable: declarar tambien un atributo tipo
    // pthread_attr_t
    pthread_attr_t attr;

    // Al usar atributos, inicializar el objeto
    pthread_attr_init(&attr);

    // Modificar el atributo especifico
    // en este caso el atributo setdetachstate = JOINABLE
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Crear el hilo
    rc = pthread_create(&tid, &attr, funTiempo, (void *)i);
    error_rc(tid, rc);

    rc = pthread_create(&tid, &attr, funDistancia, (void *)i);
    error_rc(tid, rc);

    rc = pthread_create(&tid, &attr, verificar_distancia, (void *)i);
    error_rc(tid, rc);
    
    
    // Liberar espacios de memoria utilizados para atributo
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);


    return 0;
}
