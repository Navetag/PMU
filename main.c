#include "../alambix-v0.2.4/include/alambix.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * client_order_drinks(void * arg){
    pthread_mutex_lock(&mut);
    char * drink;
    while ((drink = alambix_choose_drink()) != NULL)
    {
        alambix_order_drink(drink);
    }
    pthread_mutex_unlock(&mut);
}

void alambix_init(){
    //RIEN
}

void alambix_start(){
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