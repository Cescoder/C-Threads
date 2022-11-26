/*
Date: 25/11/2022
Authot: Francesco Scuriatti

Manage a bank account by using 3 terminals that work on it
Use mutex to protect the critical situation

Ubuntu terminal commands:
  - Compile: gcc mutexBankAccount.c -o exeName -lpthread
  - To run program: ./exeName
*/

//Libraries
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//mutex variable
pthread_mutex_t m1;

//Money accout counter
int cc;

//Thread Function

void *operation(void *arg){

    pthread_mutex_lock(&m1);

    printf("\nTerminal %d", (int)arg);
    printf("\n\t1- getMoney");
    printf("\n\t2- putMoney");

    int choice;
    printf("\nChoice: ");
    scanf("%d", &choice);

    int money;

    if(choice == 1){
        printf("\nMoney to get: ");
        scanf("%d", &money);
        cc -= money;
    }

    else if(choice == 2){
        printf("\nMoney to put: ");
        scanf("%d", &money);
        cc += money;
    }
    else{
        printf("\nOperation not avaiable...");
    }

    pthread_mutex_unlock(&m1);

    pthread_exit(NULL);

}


//MAIN
int main(int argc, char *argv[]){
    //Thread variable
    pthread_t terminals[3];

    //Mutex initialization
    pthread_mutex_init(&m1, NULL);

    //Threads creation
    for(int i=0; i<3; i++)
        if(pthread_create(&terminals[i],NULL,operation,(void*)i+1) != 0) printf("Error on thread %d", i+1);
    
    //Threads join
    for(int i=0; i< 3;i++)
        pthread_join(terminals[i], NULL);
    
    //Print final cc
    printf("\nMoney on account: %d\n", cc);

}
