#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Assumption: The input is all well formed integers
 * Written by Shazim Ajaz
 * CSC 139
 * Assignment 5
 * Due Data Dec 4th
 * Fall 2019
 */

/*
 * this method returns the absolute value of the given number
 */
int abs(int number){
    if(number < 0){
        return number * (-1);
    }
    return number;
}

/*
 * This function takes an array as its parameter and performs FCFS simulation.
 */
int fcfs(int *queue, int size){
    //Print the array in the order given
    int index = 0;
    int total_distance = 0;
    int header_location = 50; //default header location.
    while(index < size){
        int current_sector_location = queue[index];
        //Calculate the distance traveled by the header
        int current_distance_traveled = current_sector_location - header_location;

        //Find the absolute value of the distance.
        if(current_distance_traveled < 0){
            current_distance_traveled = (-1)*current_distance_traveled;
        } //else the number is already positive

        //Update the total distance
        total_distance += current_distance_traveled;

        //Update the header location
        header_location = current_sector_location;

        //Print the results
        printf("Reading Track: %d\n", current_sector_location);
        index += 1;
    }
    printf("Total Distance: %d\n", total_distance);
    return 0;
}

/*
 * This function takes an array as its parameter and performs sstf simulation.
 */
int sstf(int *queue, int size){
    printf("sstf was called \n");

    int index = 0;
    int header_location = 50;
    int total_distance = 0;
    while(index < size) {
        //Find out which request is the shortest from its current location
        int shortest_seek_time_index = 0;
        int inner_index = 0;
        while(inner_index < size){
            //Take the value at the current index
            int value_at_current_index = queue[inner_index];
            int value_of_current_shortest = queue[shortest_seek_time_index];
            //compares its seek time with the seek time of the shortest_seek_time_index
            if(abs(value_at_current_index - header_location) < abs(value_of_current_shortest - header_location)){
                //update the index
                shortest_seek_time_index = inner_index;
            }
            inner_index += 1;
        }
        index += 1;

        //Calculate the distance between the current shortest and the head
        int current_shortest = queue[shortest_seek_time_index];
        int distance = current_shortest - header_location;
        queue[shortest_seek_time_index] = 1000; //means its already consumed
        distance = abs(distance);


        printf("Reading Track: %d\n", current_shortest);

        //Update current location of the header
        header_location = current_shortest;
        total_distance += distance;

    }
    printf("Total Distance: %d", total_distance);
    return 0;
}

/*
 * This function uses bubble sort to sort the given array
 */
int bubble_sort(int *array, int size){
    int outer_index = 0;
    for(outer_index = 0; outer_index < size; outer_index += 1){
        int inner_index = 0;
        while(inner_index < size){
            if(array[inner_index] > array[outer_index]){
                //Swap the values
                int temp = array[inner_index];
                array[inner_index] = array[outer_index];
                array[outer_index] = temp;
            }
            inner_index += 1;
        }
    }
}

/*
 * This function takes an array as its parameter and performs look simulation.
 */
int look(int *queue, int size){
    //Sort the in ascending order
    bubble_sort(queue, size);

    //Find the starting index
    int head_location = 50;
    int index = 0;
    int current_starting_index = 0;
    while(index < size){
        if(queue[index] < head_location){
            current_starting_index += 1;
        } else {
            break;
        }

        index += 1;
    }



    //Take the starting index and keep servicing request until the left most request in the queue has been reached.
    int current_servicing_index = current_starting_index - 1;
    while(current_servicing_index >= 0) {
        printf("Reading Track: %d \n", queue[current_servicing_index]);
        current_servicing_index -= 1;

    }
    //Calculate the distance in the first part of the movement.
    int distance_to_left = head_location - queue[0];

    //Now jump back to the next forwarding index
    current_servicing_index = current_starting_index;

    //Calculate the distance of the "giant" leap
    int distance_of_the_leap = queue[current_servicing_index] - queue[0];

    while (current_servicing_index < size){
        printf("Reading Track: %d \n", queue[current_servicing_index]);
        current_servicing_index += 1;
    }


    //Calculate the distance to the right
    int distance_to_right = queue[size - 1] - queue[current_starting_index];

    //Print the result
    printf("Total distance covered! %d\n", distance_of_the_leap + distance_to_left + distance_to_right);
    return 0;

}

/*
 * Main
 */
int main(int argc, char* argv[]) {

    //Use Array data structure for reading the values into
    int number_of_requests = argc - 2;
    int queue[argc];

    //Read which method was used
    char* method= argv[1];

    //Load the requests into the array
    int index = 0;
    printf("Number of requests read: %d \n", number_of_requests);
    printf("Performing Disk Scheduling using %s method\n", method);
    while(index < number_of_requests){
        queue[index] = atoi(argv[index + 2]);
        //printf("Request : %d\n", queue[index]);
        index += 1;
    }

    //call the appropriate function based on the specified method
    if(strcmp(method, "fcfs") == 0){
        fcfs(queue, number_of_requests);
    } else if(strcmp(method, "sstf")==0){
        sstf(queue, number_of_requests);
    } else if(strcmp(method, "look") == 0){
        look(queue, number_of_requests);
    } else {
        printf("Please provide a valid method of execution!\n");
        exit(0);
    }

    return 0;
}