//CPU Algorithms Simulator
//Create by Shazim Ajaz
//Date Created: 10/14/19

//This program simulates the running algorithms that are related to CPU process scheduling.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This structure provides a coherent way to deal with the
//attributes related to a process
struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int time_spent;
    int time_left;
    int done; //0 means no, one means yes.
};


/*
	This method takes in an array of type processes and sort it with respect othe the arrival time
*/
int bubble_sort(struct process processes[20], int number_of_processes){

    int outerIndex = 0;
    while(outerIndex <= number_of_processes){
        int innerIndex = outerIndex;

        while(innerIndex <= number_of_processes) {
            if(processes[outerIndex].arrival_time > processes[innerIndex].arrival_time){
                //Swap the two processes
                struct process temp;
                memcpy(&temp, &processes[outerIndex], sizeof(temp));
                memcpy(&processes[outerIndex], &processes[innerIndex], sizeof(processes[outerIndex]));
                memcpy(&processes[innerIndex], &temp, sizeof(processes[innerIndex]));
            }
            innerIndex +=1;
        }
        outerIndex +=1;
    }
    return 0;
}


// This function runs the round robbin on the given file and prints the output
int rr(FILE *filePtr, int time_quantum) {
    //Print a dialog showing that round robin method was run
    printf("Round robin is running with time quantum: %d \n", time_quantum);

    //Read the data from the file
    struct process processes[20];
    int index = 0;
    int number_of_processes = 0;

    while (!feof(filePtr)) {

        fscanf(filePtr, "%d %d %d", &(processes[index].pid), &(processes[index].arrival_time), &(processes[index].burst_time));
        processes[index].time_spent = 0;
        processes[index].time_left = processes[index].burst_time;
        processes[index].done = 0; //not done yet
        index += 1;\
		number_of_processes += 1;
        //printf("Total Burst Time: %d \n", processes[index].burst_time);
    }


    //Number of process 0 -- 7
    number_of_processes -= 2;

    //Here we need to sort the file with respoect to the arrival time
    //The assumption is that the arrival times might not be ordered.
    bubble_sort(processes, number_of_processes);
    //The above line ensures that the processes are ordered before we try to simulate Round Robin scheduling

    int total_burst_time = 0;
    //Calculate the total burst time
    for(index = 0; index < number_of_processes; index++){
        total_burst_time = total_burst_time + processes[index].burst_time;
    }
    /*
     * Simulation Begins here
     */
    int total_run_time = 0;
    int time_wasted = 0;
    int current_process = 0;
    //Repeat it while all of the process are done executing
    while(total_run_time < total_burst_time) {
    //Run this for the amount of time left
        for(index = 0; index < time_quantum; index +=1) {

            /* These are the condition that each process must meet for it to run */
            //Check if the process has arrived and it is not done
            if (total_run_time >= processes[current_process].arrival_time & processes[current_process].done == 0) {

                //If the process is here the first time. Calculate it's wait time here

                //Execute the process
                printf("Process %d is running!..... \n", processes[current_process].pid);
                total_run_time += 1;

                //Reduce the remaining time of the process
                processes[current_process].time_left -= 1;
                processes[current_process].time_spent += 1;

                //Check if the process is done after the above step.
                //If that is the case, then mark the process as done.
                if (processes[current_process].time_left == 0) {
                    //Mark it as done
                    processes[current_process].done = 1; //1 means that the process is done
                    break; //Break the loop

                }

            } else if(total_run_time < processes[current_process].arrival_time){
                printf("\n CPU is idle \n");
                time_wasted += 1;
            }

            /* ****************************************************************** */
        }
        printf("Process %d's current run time is: %d \n", processes[current_process].pid, processes[current_process].time_spent);
        printf("Procees %d's burst time left is: %d \n\n", processes[current_process].pid, processes[current_process].time_left);
        current_process += 1;

        //If the end of the processes has reached, reset the pointer
        if(current_process == number_of_processes){
            current_process = 0;
        }

    }

    printf("Time Spent by the CPU Idle: %d \n", time_wasted);
    printf("CPU Utilization: %d Percent \n", (100 - (time_wasted/total_run_time)));

}

//This function runs he FCFS scheduling algorithm on the given file and prints the output
int fcfs(FILE *filePtr) {

    //Average waiting time
    int total_waiting_time = 0;
    int total_waiting_time_accumulator = 0;

    //Avergae response time
    int total_response_time = 0;
    int total_response_time_accumulator = 0;

    //Average Turn Around Time
    int total_turnaround_time = 0;
    int total_turnaround_time_accumulator = 0;

    //Average CPU Useage
    int total_cpu_usage = 0;


    printf("***************************************************************************\n");
    //Print heading that First come first server algorithm is being used
    printf("First Come First server algorithm is running\n");

    //Read the data from the file
//    int pids[20];
//    int arrival_times[20];
//    int burst_times[20];

    struct process processes[20];

    int number_of_processes = 0;
    //Read the values from the file into an array
    int index = 0;
    while(!feof(filePtr)) {
        //Read the values from the file and load them into the variables
        fscanf(filePtr, "%d %d %d \n", &(processes[index].pid), &(processes[index].arrival_time), &(processes[index].burst_time));

        //Increment the counter
        index = index+1;
        number_of_processes += 1;
    }
    bubble_sort(processes, number_of_processes - 1);
    printf("Number of processes: %d \n", number_of_processes );



    //Use the first come first serve method to run the algorithm
    index = 0;
    while(index < number_of_processes) {
        int innerIndex = 0;

        while(innerIndex != processes[index].burst_time) {
            printf("System Time:	%d	 process %d is running \n", innerIndex, processes[index].pid);
            innerIndex = innerIndex + 1;
            total_cpu_usage += 1;
        }
        printf("Process %d has finished execution... \n \n", processes[index].pid);

        //Update the waiting time
        if(innerIndex != processes[number_of_processes-1].pid) {
            total_waiting_time = total_waiting_time + innerIndex - processes[index].arrival_time;
            total_waiting_time_accumulator += total_waiting_time;

        }
        //Update the turn around time
        total_turnaround_time = total_turnaround_time + innerIndex;
        total_turnaround_time_accumulator += total_turnaround_time;

        //Account for context switch
        total_cpu_usage += 1;
        index = index+1;


    }
    printf("*******************Results of the Simulation************************************\n");
    printf("Average Waiting Time: %d \n", total_waiting_time_accumulator/number_of_processes);
    printf("Average Response Time: %d \n", total_waiting_time_accumulator/number_of_processes);
    printf("Average Turnaround Time: %d \n", total_turnaround_time_accumulator/number_of_processes);
    printf("Overall CPU Usage: %d (Each context switches counted as 1) \n", total_cpu_usage);
    printf("********************************************************************************\n");

    return 0;

}

//This function runs the SRTF scheduling algorithm on the given data and prints the output
int srtf(FILE *filePtr){
    printf("Shortest Time Remaining algorithm is currently running \n");
    //Read the data from the file
    struct process processes[20];

    int number_of_processes = 0;
    int total_burst_time = 0;
    //Read the values from the file into an array
    int index = 0;
    while(!feof(filePtr)) {
        //Read the values from the file and load them into the variables
        fscanf(filePtr, "%d %d %d \n", &(processes[index].pid), &(processes[index].arrival_time), &(processes[index].burst_time));
        total_burst_time += processes[index].burst_time; //Accumulate the total burst time.
        processes[index].time_left = processes[index].burst_time;
        processes[index].time_spent = 0;
        processes[index].done = 0;
        //Increment the counter
        index = index+1;
        number_of_processes += 1;

    }
    bubble_sort(processes, number_of_processes - 1);
    printf("Total Burst Time is %d \n", total_burst_time);

    //At this point, we have the jobs in order.
    //At each step, we execute the process, if any of the arrives processes has burst time shorter than
    //the time required for the current one, we switch the process
    int current_total_run_time = 0;
    //Run the loop for the amount of the burst time
    index = 0;
    while(current_total_run_time < total_burst_time) {

        //Check which process has arrived at this time (compare run time to the arrival time)
        int innerIndex = 0;
        int current_smallest_index = 0;
        //In this loop, find the process which have the lowest time_left value
        for (innerIndex = 0; innerIndex < number_of_processes; innerIndex += 1) {
            if (processes[innerIndex].arrival_time <= current_total_run_time & processes[innerIndex].done != 1) { //Make sure the process has arrived
                //It means that the process has arrived
                //Compare their burst time to the burst time of the process at current_smallest
                // index if the process is not done yet
                if (processes[innerIndex].time_left < processes[current_smallest_index].time_left) {
                    //Then update the current_smallest_index to the innerIndex
                    current_smallest_index = innerIndex;
                }

            } else {
                continue;
            }
        }

        if (processes[current_smallest_index].done != 1) {
            //At this point, we have index of the process with the smallest burst time at current_total_run_time
            printf("Process %d is currently running....! \n", processes[current_smallest_index].pid);

            //updater its burst time
            processes[current_smallest_index].time_left -= 1;
            processes[current_smallest_index].time_spent += 1;
            printf("Process has run for %d/%d times \n \n", processes[current_smallest_index].time_spent,
                   processes[current_smallest_index].burst_time);

            //If the current process has finished executing, then print that the current process has finished
            //Exit condition
            current_total_run_time += 1;
        } else {
            continue;
        }
        //Mark if the process is done
        if (processes[current_smallest_index].time_left <= 0) {
            processes[current_smallest_index].done = 1; //1 means process is done
        }


    }

    return 0;
}

int main(int argc, char **argv){

    //Check if the filename was provided
    char * filename;
    if(argv[1] != NULL) {
        filename = argv[1];
    } else {
        printf("A File Name must be provided for this program to work \n");
        exit(0);

    }
    //Above if statement will ensure that there is a file name.
    //Open the file with the given file name
    FILE *fileptr;
    fileptr = fopen(filename, "r"); //r argument means read only
    if(fileptr == NULL) {
        printf("File not found!\n");
        exit(0);
    }

    char * method;
    //Read the next argument and find out which sceduling algorithm to use
    if(argv[2] != NULL) {
        method = argv[2];
        printf("Method Selected: %s\n", method);
    } else {
        printf("Type of scheduling algorithm must be provided. \n");
        exit(0);
    }

    //At this point, we know which scheduling method to use.
    //We will call the appropriate method to deal with each scheduling algorithm simulation

    if(strcmp(method, "FCFS")==0){ //Simulate using first come first serve
        fcfs(fileptr);

    } else if(strcmp(method, "RR")==0){
        //check if the time quantum was provided
        if(argv[3] != NULL) {
            int time_quantum = atoi(argv[3]);
            if(time_quantum <= 0) {
                printf("A time quantum of 1 or more is required!");
                exit(0);
            }
            rr(fileptr, time_quantum);

        } else {
            printf("A time quantum must be provided if Round Robin algoritm is used. \n");
            exit(0);
        }
    } else if(strcmp(method, "SRTF")==0) {
        srtf(fileptr);

    }

    fclose(fileptr);

    return 1;

}