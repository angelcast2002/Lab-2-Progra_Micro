/*
*------------------------------------------
* Parte-2
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

* CC3086 - Programacion de Microprocesadores
*
*------------------------------------------
* Descripción: Lab 2 Parte
* Autor:       Angel Castellanos 21700 
* Se probo con: visual studio code y gcc
*------------------------------------------
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <stdlib>
using namespace std;
//Se crea la struct
struct infoUsuarios{
    string nombre;
    string apellido;
    int CUI;
    int ultimoNcui;
    string expiracion;
}infoUsuarios[4];

int main(){
    int NoUsuarios = 3;
    printf("Bienvenido al programa de ordenar cui's\n");

    for(int i=0; i<NoUsuarios; i++){
        //Para vaciar buffer y permitir digitar valores
        fflush(stdin);
        //Se piden los datos a almacenar
        printf("\n ---Ingresando el usuario %d ---", i);
        cout << "\nDigite Nombre: " << endl;
        cin >> infoUsuarios[i].nombre;
        cout << "Digite apellido: " << endl;
        cin >> infoUsuarios[i].apellido;
        cout << "Digite CUI: " << endl;
        cin >> infoUsuarios[i].CUI;
        cout << "Digite ultimo digito de CUI: " << endl;
        cin >> infoUsuarios[i].ultimoNcui;
        cout << "Digite fecha de expiracion: " << endl;
        cin >> infoUsuarios[i].expiracion;
        cout << "\n";
    }

    //Se ordena el array de manera ascendente en base al ultimo digito de CUI y se imprime
    for (int i = 1; i<10; i++) {
        for (int j = 0; j < NoUsuarios; ++j) {
            if (infoUsuarios[j].ultimoNcui == i){
                cout << "CUI:";
                cout << infoUsuarios[j].CUI << endl;
            }

        }

    }

    return 0;
}


