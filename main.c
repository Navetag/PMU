#include "alambix-v0.2.4/include/alambix.h"
#include "protocol.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <string.h>

#include <fcntl.h>           /* pour les constantes O_* */
#include <sys/stat.h>        /* pour les modes d'ouverture */
#include <mqueue.h>

#define MQ_MSG_MAX (10)

#define MQ_MSG_SIZE (48)

#define SEM_NAME "/sem_order"

sem_t sem;
mqd_t mq;


struct mq_attr attr;

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
    fprintf(stdout, "got order");
    char * ordered_drink;
 
    while ((ordered_drink = alambix_get_ordered_drink()) != NULL)
    {
        if (mq_send(mq, ordered_drink, strlen(ordered_drink) + 1, 0) == -1) { 
			perror("mq_send()");
			
			exit(EXIT_FAILURE);
		}
    }
    //pthread_barrier_destroy(&barrier);

    sem_close(&sem);
    sem_destroy(&sem);
    //TODO
}

void * bartender_thrd(void * args){

    // receive the order from the waiter
    char buffer[MQ_MSG_SIZE];
    do
    {
        if (mq_receive(mq, buffer, MQ_MSG_SIZE, NULL) == -1) {
			perror("mq_receive()");
			mq_close(mq);
			mq_unlink(ALAMBIX_BARTENDER_MQ);
			exit(EXIT_FAILURE);
		}

    }
    while (alambix_has_ordered_drink());

}

void alambix_init(){
    fprintf(stdout, "Entered init");
    attr.mq_maxmsg = MQ_MSG_MAX;
	attr.mq_msgsize = MQ_MSG_SIZE;

    if ((mq = mq_open(ALAMBIX_BARTENDER_MQ, O_RDWR | O_CREAT, 0644, &attr)) == -1) {
		perror("mq_open()");
		exit(EXIT_FAILURE);
	}


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

    if( pthread_create(&alambix_bartender_thread, NULL, bartender_thrd, NULL) != 0){
        fprintf(stderr, "erreur pthread_create\n");
		exit(EXIT_FAILURE);
    }
    pthread_detach(alambix_bartender_thread);
    
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
    alambix_open();
    mq_close(mq);
    mq_unlink(ALAMBIX_BARTENDER_MQ);
}