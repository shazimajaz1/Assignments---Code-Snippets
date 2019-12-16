#include <stdio.h>
#include <stdlib.h>


/*
 * A part of this code is inspired from Geeks for Geeks queue implementation. It can be accessed at
 * https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 */
//This struct defines a basic queue
struct Queue {
    int start; //Beginning of the Queue
    int end; //Last element of the Queue
    int size; //size of the Queue at that instance. This is the filled size
    unsigned capacity; //Total capacity of the queue.
    int* array; //This is the array where the data will be stored.
};

//This function creates a Queue and initializes the values
struct Queue* createQueue(unsigned capacity){
    //Allocate the memory to the queue
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));

    //Initialize the Queue variables
    queue->capacity = capacity;
    queue->start = 0;
    queue->size = 0; //Both the size and the start of the queue at this point are 0
    queue->end = capacity - 1;

    //Allocate the memory to the array
    queue->array = (int *) malloc((capacity * sizeof(int)));

    return queue;
}

//This method returns true if the queue is full --> No more spaces
int isFull(struct Queue* queue){

    //return queue->size == queue->capacity;

    return queue->capacity == queue->size;
}

//This method returns true if the queue is empty --> No elements
int isEmpty(struct Queue* queue){
    return queue->size == 0;
}

//Enqueue: This function adds the element to the queue
void enqueue(struct Queue* queue, int value){

    //Check if the queue is full
    int result = isFull(queue);
    if(result){
        return; //No value can be added to a full queue
    } else {
        //At this point,we know that the queue is not full
        //Determine the new rear of the queue
        queue->end = (queue->end + 1) % queue->capacity;
        //Add the given element to that rear of the queue
        queue->array[queue->end] = value;
        //Increase the queue size
        queue ->size += 1;
    }
}

//Deque: This function removes the element from the quee
int dequeue(struct Queue* queue){
    //Check if there are any elements in the queue
    if(isEmpty(queue)){
        return -1;
    } else {
        //Queue is not empty
        //Remove the element from the start of the queue
        int item = queue->array[queue->start];

        //Update the front of the queue
        queue->start = (queue->start+1) % queue->capacity;

        //Reduce the size counter by 1
        queue->size -= 1;

        return item;

    }
}

