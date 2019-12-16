#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/*
 * This function uses first in, first out method to load the pages
 * into the frames.
 */
int fifo(FILE *ptr) {
    printf("First in, First out produced the following results: \n");
    //Read the first line from the file
    //Read the # of pages, frames and requests
    int number_of_pages = 0;
    int number_of_frames = 0;
    int number_of_requests = 0;

    //Read the first row containing the necessary info
    fscanf(ptr, "%d %d %d", &number_of_pages, &number_of_frames, &number_of_requests);

    //Create an array with the provided number of frames and initialize it to -1
    int frame[number_of_pages];
    int index = 0;
    while (index < number_of_pages) {
        frame[index] = -1;
        index += 1;
    }

    //At this point, the default value in the array is -1
    int next_empty_position = 0;

    int outerIndex = 0;
    int total_page_faults = 0;
    while (!feof(ptr)) {
        //Load the page into a variable form the file
        int page;
        fscanf(ptr, "%d", &page);
        int inMemory = 0; //0 means false; 1 means true
        //Check if the page is already in the array
        index = 0;
        while (index < number_of_frames) {

            if (frame[index] == page) {
                printf("Page %d is already in frame %d \n", page, index);
                inMemory = 1;
            }
            index++;
        }

        //At this point, if the page is still not in memory, it should be added into the memory.
        if (inMemory == 0) {//not in memory

            //Check if the element is not negative one
            if (frame[next_empty_position] != -1) {
                printf("Page %d unloaded from the frame %d,", frame[next_empty_position], next_empty_position);
            }

            frame[next_empty_position] = page;


            printf("Page %d was loaded in frame %d \n", page, next_empty_position);
            total_page_faults += 1;
            //Update the next empty pointer accordingly.
            if ((next_empty_position + 1) > (number_of_frames - 1)) {
                //Rest to zero
                next_empty_position = 0;
            } else {
                next_empty_position += 1;
            }

        }

    }

    printf("Total Page Faults: %d \n", total_page_faults);

    return 0;
}


struct Frame {
    int page;
    int time_stamp;
};

/*
 * This function uses least recently used method for paging
 */
int lru(FILE *ptr) {
    printf("Least Recently Used Policy produces the following output: \n");
    //Read the first line from the file
    //Read the # of pages, frames and requests
    int number_of_pages = 0;
    int number_of_frames = 0;
    int number_of_requests = 0;

    //Read the first row containing the necessary info
    fscanf(ptr, "%d %d %d", &number_of_pages, &number_of_frames, &number_of_requests);

    struct Frame frame[number_of_frames];

    //Initialize the values to be -1
    int index = 0;
    while (index < number_of_frames) {
        frame[index].page = -1;
        frame[index].time_stamp = 0;
        index += 1;
    }


    //Load the data into the array of frames
    index = 0;
    int total_page_faults = 0;
    int clock = 1;
    while (!feof(ptr)) {

        //Read the page
        int page;
        fscanf(ptr, "%d", &page);

        //Check if the page is already in the array of frames
        int search_index = 0;
        int inMemory = 0; //0 means false, one means true

        while (search_index < number_of_frames) {

            if (frame[search_index].page == page) {

                //Page is in the memory.
                printf("Page %d already in the frame %d \n", page, search_index);

                //Update the time stamp
                frame[search_index].time_stamp = clock;
                //printf("Updated Time Stamp for frame %d \n",search_index);
                inMemory = 1;

            }



            search_index += 1;
        }

        //If the page not in memory, load it to the frame
        if (inMemory == 0) { //Not in memory
            //Find oldest time index in the frame array
            search_index = 0;
            int lowest_index = 0;
            int lowest_value = frame[0].time_stamp;
            while (search_index < number_of_frames) {

                //Check if the current time stamp is the lowest.
                if (frame[search_index].time_stamp < lowest_value) {
                    lowest_value = frame[search_index].time_stamp;
                    lowest_index = search_index;
                }
                search_index += 1;
            }

            //Take the lowest index and replace with the new element.
            if(frame[lowest_index].page != -1) {
                printf("Page %d unloaded from frame %d, ", frame[lowest_index].page, lowest_index);
            }

            //Replace with the th new element
            frame[lowest_index].page = page;
            frame[lowest_index].time_stamp = clock;
            printf("Page %d load to frame %d \n", frame[lowest_index].page, lowest_index);
            //printf("Updated Time Stamp for frame %d \n",lowest_index);


            total_page_faults += 1;
        }

            search_index = 0;
//            while(search_index < number_of_frames){
//                printf("Index %d has %d with time stamp %d \n", search_index, frame[search_index].page, frame[search_index].time_stamp);
//                search_index++;
//            }

        //frame[index].time_stamp = (int) time(NULL);
        index += 1;
        clock += 2;
    }

    printf("Total Page Faults: %d \n", total_page_faults);
    fclose(ptr);

    return 0;
}

struct optFrame {
    int page;
    int next_use_time;
    int index_in_pages_array;
};
/*
 * This function uses optimal method for paging
 */
int opt(FILE *ptr) {
    /*
     * We maintain an array of pages once it is loaded.
     * It has the value
     * It has its next access time.
     */

    //Load the page into in array from the file.
    printf("Least Recently Used Policy produces the following output: \n");
    //Read the first line from the file
    //Read the # of pages, frames and requests
    int number_of_pages = 0;
    int number_of_frames = 0;
    int number_of_requests = 0;

    //Read the first row containing the necessary info
    fscanf(ptr, "%d %d %d", &number_of_pages, &number_of_frames, &number_of_requests);

    //Load the data into the memory
    int index = 0;
    int requests[number_of_requests];
    while (index < number_of_requests) {
        fscanf(ptr, "%d", &requests[index]);
        index += 1;
    }


    //We maintain array of frame with the given number of frames
    struct optFrame frames_array[number_of_frames];

    //Initialize the frames array
    index = 0;
    while(index < number_of_frames){
        frames_array[index].page= -1;
        frames_array[index].next_use_time= 1000; //Since we do not have infinity. 1000 is our upper limit
        frames_array[index].index_in_pages_array=-1;

        index += 1;
    }

    /*
     * These are the possible scenarios. All of these must be accounted for.
     * ### Anytime a request comes in, we calculate the value of each numbers distance from
     * ### its next use time
     * 1. A request comes in, the page is not in memory but we have an empty slot.
     *      a. Place the page in the next empty slot
     * 2. A request comes in, the page is in memory. We don't care if we have an empty slot or not at this time
     * 3. A request comes in, the page is not in memory, and we do not have an empty slot:
     *      a. This is where page replacement should be done.
     *      b. Assume that the values of each pages next_use_time are up to date.
     *      c. Choose the page with largest next use time and remove it from the memory
     *      d. Fill the empty frame with the requested page.
     */

    //This loop goes request by request and places the pages in the appropriate frames
    //and completes the requests
    int request_number = 0;

//    printf("Data successfully loaded into the array! \n");
//    index = 0;
//    while (index < number_of_requests) {
//        printf("Page %d \n", requests[index]);
//        index += 1;
//    }
	int total_number_of_page_faults = 0;
    while(request_number < number_of_requests){
       // printf("A request for %d came in \n", requests[request_number]);
        //Update the distance of each page in the frames array from its next use time.
        int frame_iteration_index;
        for(frame_iteration_index=0; frame_iteration_index < number_of_frames; frame_iteration_index += 1){
            //Take the frame at the given index and calculate its distance from the next_use_time
            struct optFrame current_frame = frames_array[frame_iteration_index];
            //Check if it is empty
            if(current_frame.page != -1){//means not empty
                //Search the index of the next use of the page in the array.
                int page_search_index = current_frame.index_in_pages_array +1;
                int next_use_found = 0; //0 means false, 1 means true

                while(page_search_index < number_of_requests){
                    if(requests[page_search_index] == requests[current_frame.index_in_pages_array]){
                        next_use_found = 1;
                        break; //break the loop
                    }

                    page_search_index += 1;
                }
                //calculate the distance of that frame
                if(next_use_found == 1){
                    int time = page_search_index - current_frame.index_in_pages_array;

                    current_frame.next_use_time = time - (request_number - current_frame.index_in_pages_array) + 1;
                    //printf("Page %d has updated use time of %d! \n", current_frame.page, current_frame.next_use_time);

                } else { //there is no further use for the page
                    current_frame.next_use_time = 1000; //set it to infinity if no next use has been found
                }
            }
            frames_array[frame_iteration_index] = current_frame;

        }

        //Print the next use_time of each frame
        frame_iteration_index = 0;
        while(frame_iteration_index < number_of_frames){
            //printf("Page %d in frame %d has next use time of %d \n", frames_array[frame_iteration_index].page, frame_iteration_index, frames_array[frame_iteration_index].next_use_time);
            frame_iteration_index+=1;
        }
        //Since we update the next use time of each update, at this point, we can assume that the next we will
        //get an updated next use time for each page in the frame.
        //We can make decision based on the next_used_time to remove the page that we desire.

        //A request comes in
        int current_request = requests[request_number];

        //Case 1: Request is already in the frame
        //Search if the request if it is already in the frames array
        frame_iteration_index = 0;
        int found_in_frames_array = 0; // 0 means false, 1 means true
        while(frame_iteration_index < number_of_frames){
            if(current_request == frames_array[frame_iteration_index].page){
                //if true, update the boolean variable
                found_in_frames_array = 1;

                //Break the loop
                break;
            }
            frame_iteration_index += 1;
        }
        //Request is already in the frame
        if(found_in_frames_array == 1){
            //update the index
           frames_array[current_request].index_in_pages_array = request_number;
            printf("Page %d is found in frame %d \n", current_request, frame_iteration_index);
        } else { //Request is not in the frame
		total_number_of_page_faults += 1;
            //Check if the frame has an empty space.
            frame_iteration_index = 0;
            int empty_frame_found = 0;
            while(frame_iteration_index < number_of_frames){
                if(frames_array[frame_iteration_index].page == -1) {//means empty
                    //Update the boolean variable.
                    empty_frame_found = 1;

                    //Break the loop since next empty space is found
                    break;

                }
                frame_iteration_index += 1;
            }
            //If empty, then place in that empty space
            if(empty_frame_found == 1){
                //Update the empty frame with the current request
                frames_array[frame_iteration_index].page = current_request;
                frames_array[frame_iteration_index].index_in_pages_array = request_number;

                //Identify the update
                printf("Page %d loaded to frame %d \n", current_request, frame_iteration_index);
            } else { //No empty frame is found | perform optimal scheduling
                //Find the index of the frame with the highest use time value
                frame_iteration_index = 0;
                int largest_index = 0;
                while(frame_iteration_index < number_of_frames){
                    if(frames_array[frame_iteration_index].next_use_time > frames_array[largest_index].next_use_time){
                        largest_index = frame_iteration_index;
                    }
                    frame_iteration_index += 1;
                }
                //Replace the frame at that index with the new request
                printf("Page %d unloaded from frame %d, ", frames_array[largest_index].page, largest_index);
                frames_array[largest_index].page = current_request;
                frames_array[largest_index].index_in_pages_array = request_number;
                printf("Page %d loaded to frame %d \n", current_request, largest_index);

            }

        }

        request_number += 1;
    }
	printf("Total Number of Page Faults: %d \n", total_number_of_page_faults);
    return 0;
}


int main(int argc, char *argv[]) {
    //Check if enough arguments are provided
    if (argc < 3) {
        printf("Missing Arguments: The syntax is 'a.out [input_file] [FIFO|LRU|OPT]' \n");
        exit(0);
    }

    //Read the arguments provided
    char *file_name = argv[1];
    char *method = argv[2];

    //Create a file pointer with the file name
    FILE *filePtr;
    filePtr = fopen(file_name, "r");

    if (filePtr == NULL) {
        printf("Error with file ptr! \n");
        exit(0);
    }


    //Call the function with appropriate method
    if (strcmp(method, "FIFO") == 0) {
        fifo(filePtr);
    } else if (strcmp(method, "LRU") == 0) {
        lru(filePtr);
    } else if (strcmp(method, "OPT") == 0) {
        opt(filePtr);
    } else {
        //show error message
        printf("Please specify correct method name you want to use: \n  choices are: [FIFO|LRU|OPT] \n");
    }

    fclose(filePtr);
    return 0;
}

