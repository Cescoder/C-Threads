/*
Data: 18/11/2022
Autore: Francesco Scuriatti

ESERCIZIO: Scrivere un programma in linguaggio c capace di utilizzare 2 thread per stampare 2 parole diverse.
        -> Utilizzo dei mutex
*/

//Librerie
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Istanza dei mutex
pthread_mutex_t m1;
pthread_mutex_t m2;

//FUNZIONI DEI THREAD

    //Stampa parola hello
    void *printHello(void *arg){
        //Lock del mutex 1
        pthread_mutex_lock(&m1);

        //Stampa della parola
        printf("Hello ");
        
        //Unlock del mutex 2
        pthread_mutex_unlock(&m2);

        pthread_exit(NULL);

    }

    //Stampa parola world
    void *printWorld(void *arg){
        //Lock del mutex 2
        pthread_mutex_lock(&m2);

        //Stampa della parola
        printf("world\n");

        //Unlock del mutex 1
        pthread_mutex_unlock(&m1);

        pthread_exit(NULL);

    }

//MAIN
int main(int argc, char *argv[]){
    //Instanze dei thread
    pthread_t pHello;
    pthread_t pWorld;

    //Inizializzazione dei mutex
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    pthread_mutex_lock(&m2);
    
    while(1){
        //Funzione del primo thread
        pthread_create(&pHello,NULL,printHello,NULL);

        //Funzione del secondo thread
        pthread_create(&pWorld,NULL,printWorld,NULL);

    }

}