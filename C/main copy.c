//
// Created by Shazim Ajaz on 11/5/19.
//
#include <stdio.h>
#include "queue.h"
#include "buffer.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <zconf.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>

/*                                      */
//***********Synchronization************//
/*                                     */

pthread_mutex_t mutex;
sem_t sem_mutex_full;
sem_t sem_mutex_empty;

//define the buffer
struct Queue* buffer;


//This is a producer function
void *producer(void *param){
    printf("\n");
    int buffer_item;

    while(1) {
        //Sleep for a random period of time
        int sleep_time = rand() % (1000+1-10) % 10;
        sleep(sleep_time);

        //Generate a random number
        buffer_item = sleep_time;

        //Acquire the lock
        sem_wait(&sem_mutex_empty);
        pthread_mutex_lock(&mutex);
        //Critical Section
        enqueue(buffer, buffer_item);
        printf("Producer produced: %d \n", buffer_item);
        //Release the lock
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_mutex_full); //Increment the full mutex because a new element was just added
  //      printf("sem_mutex_empty %d /n", sem_mutex_empty);

    }

}

/*
 * This is the consumer method. This method consumes data from the queue
 */
void *consumer(void *param){
    int item;
    while(1) {



        //Sleep for a random period of time
        int sleep_time = rand() % (1000 + 1 - 10) % 10;
        sleep(sleep_time);

        //Synchronization
//        printf("semaphore : %d \n", sem_mutex_full);
        sem_wait(&sem_mutex_full); //The consumer should wait here //Increment the full mutex
        pthread_mutex_lock(&mutex);

        //Critical section
        item = dequeue(buffer);

        printf("Consumer consumed: %d \n",  item);

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_mutex_empty); //

    }
}


int main(int argc, char* argv[]) {
    srand(time(NULL));

    buffer = createQueue(BUFFER_SIZE);


    /* Uncomment this code to show tests for insert_function
    //Step 1: Fill the buffer with null valus
    int index;
    for(index = 0; index < BUFFER_SIZE; index += 1){
        buffer[index] = -100;
    }

    //Step 2: Test if the method works
    test_insert_item();

     */
//    buffer_item item = 20;
//    buffer[0] = item;
//    print_buffer();
//
//    remove_item(item);
//
//    print_buffer();

    if(argc < 4){
        printf("The format is: a.out <sleep time before terminating> <# of prod threads> <#number of cons threads>");
        exit(0);
    }
    //Retrieve three arguments
    int time_to_sleep= atoi(argv[1]);
    int number_of_producer_threads = atoi(argv[2]);
    int number_of_consumer_threads = atoi(argv[3]);

    printf("Sleep time: %d producers: %d consumers: %d \n", time_to_sleep, number_of_producer_threads, number_of_consumer_threads );

    //Create the mutex lock and the semaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem_mutex_full, 0, 0);
    sem_init(&sem_mutex_empty, 0, BUFFER_SIZE);


    int index;
    //Create producer threads
    for(index = 0; index < number_of_producer_threads; index +=1) {
        pthread_t producer_tid;
        pthread_attr_t producer_attr;
        pthread_attr_init(&producer_attr);
        pthread_create(&producer_tid, &producer_attr, producer, NULL);
        printf("Producer thread number %d was created \n", index);
    }

    //Create consumer threads
    for(index = 0; index < number_of_consumer_threads; index +=1) {
        pthread_t consumer_tid;
        pthread_attr_t consumer_attr;
        pthread_attr_init(&consumer_attr);
        pthread_create(&consumer_tid, &consumer_attr, consumer, NULL);
        printf("Consumer thread number %d was created \n", index);
    }

    //Sleep
    sleep(time_to_sleep);
    printf("Time expired! Going to sleep... \n");
    exit(0);
}
