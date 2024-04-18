#include "../alambix-v0.2.4/include/alambix.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>

#define SEM_NAME "/sem_order"

sem_t sem;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
//pthread_barrier_t barrier;

void * client_order_drinks(void * arg){
    pthread_mutex_lock(&mut);
    char * drink;
    while ((drink = alambix_choose_drink()) != NULL)
    {
        alambix_order_drink(drink);
    }
    pthread_mutex_unlock(&mut);
    sem_post(&sem);
    //pthread_barrier_wait(&barrier);
}

void * waiter_take_drinks(void * args){
    sem_wait(&sem);
    sem_wait(&sem);
    //pthread_barrier_wait(&barrier);
    alambix_take_order();
    //pthread_barrier_destroy(&barrier);
    sem_close(&sem);
    sem_destroy(&sem);
    //TODO
}
void alambix_init(){
}

void alambix_start(){
    sem_init(&sem, 0, 0);

    //pthread_barrier_init(&barrier, NULL, 3);
    //pthread_create(&alambix_help_thread, NULL, alambix_help, NULL);
    if( pthread_create(&alambix_client0_thread, NULL, client_order_drinks, NULL) != 0){
        fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_client0_thread);

    if( pthread_create(&alambix_client1_thread, NULL, client_order_drinks, NULL) != 0){
        fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_client1_thread);

    if( pthread_create(&alambix_waiter_thread, NULL, waiter_take_drinks, NULL) != 0){
        fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_waiter_thread);
    
}




void alambix_help(void){
    long int pid_fils=fork();
    if(pid_fils == 0){
        char *argv[3];
        argv[0] = "firefox";
        argv[1] = "/home/evan/Documents/PMU/Projet_Alambix/alambix-v0.2.4/ui/original/doc/index.html";
		argv[2] = (char *) NULL;

        execv("/usr/bin/firefox", argv);
    }

}

int main(int argc, char **argv){
    alambix_init();
    alambix_open();
}