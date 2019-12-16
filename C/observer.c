//Written By Shazim Ajaz
// Date: Sept 24th, 2019
// CSC 139
// Assignment 1

//This program uses /proc file system to display the information asked in
//assignment 1. 
//There are three versions of this program. 
//First version is default. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	printf("************************************************\n");
	if(argc == 1) {
		def(); //Part B
	}
	
	if(argc == 2) {
		def(); //Part B
		printf("************************************************\n");
		defPlus(); //Part C
	}
	if(argc == 3) {	
		printf("************************************************\n");
		def();
		defPlus();
		defExtended(); //Part D
	}
	return 0;
}

//This method when called, runs the default version of the program that prints
//the following information.
//CPU name, Kernel Version
//Amount of time since the system was last booted in dd:hh:mm:ss
//data (gettimeofdata) and machine hostname

def() {
	//Read the CPU info file and filter the info to display on
	//the screen. 
	printf("CPU Info: \n");
	system("cat /proc/cpuinfo | grep 'model name'");

	//Read the linux kernel version is output it after filtering
	printf("\n");
	printf("Kernel Version: \n");
	system("cat /proc/version");
	
	//Print the system last boot time
	printf("\n");
	printf("System Last Boot Time: \n");
	
	int uptime;
	//read the uptime from file. 
	FILE *ptr = fopen("/proc/uptime", "r");
	if(ptr != NULL) {
		fscanf(ptr, "%d", &uptime);
		format_time(uptime);
		fclose(ptr);	
	} else {
		printf("Error! File not found.");
	}
	
	//Get time of day and machine hostname
	//We can use rtc file in the driver to get the time
	printf("\n"); 
	system("cat /proc/driver/rtc | grep rtc_time");

	printf("\n");

	//The host name is stored inside the file hostname which is 
	//located at /proc/sys/kernel/hostname
	
	system("cat /proc/sys/kernel/hostname");
}

//This function takes time as an integer parameter
//The it converts it itno dd:hh:mm:ss
format_time(int time) {
	int second = time % 60; // Get the remaining seconds
	int minutes = time / 60; // Get the output in minutes
	int hours = minutes / 60; // Get the ouptut in hours
	minutes = minutes % 60; // Get the remaining minutes
	
	int days = hours / 24; // Get the hours in days.
	hours = hours % 24; // Get the remaining hours

	//Format the  string
	printf("%d:%d:%d:%d\n", days, hours, minutes, second );
	
}


//This implements the things asked in Part C
defPlus() {
	printf("********************Part C*******************\n");
	//The amount of time all CPUs have spent in user mode
	//Read the file
	FILE *ptr = fopen("/proc/stat", "r");
	if(ptr != NULL) {
		printf("Time spent by different CPUs: \n");
		//Read the file line by line
		char buff[1000];
		
		int i;
		for(i = 0; i < 5; i++) {		
			fscanf(ptr, "%s", buff);
			printf("%s \n", buff);
		
			fscanf(ptr, "%s", buff);
			printf("User Mode: %s \n", buff);
		
			fscanf(ptr, "%s", buff); //Skipping next number
			fscanf(ptr,"%s", buff); 	
			printf("Kernel Mode: %s \n", buff);
		
			fscanf(ptr, "%s", buff);
			printf("Idle: %s \n", buff);
		
			//Move the pointer to the next line.
			fgets(buff, 1000, (FILE*) ptr);
			printf("\n");

		}

		//Close the file as its not needed anymore
		fclose(ptr);
	} else {
		printf("Error! File not found.");
	}
	
	//The number of disk read/write requests completed on the system
	system(" cat /proc/diskstats | grep sd > temp.txt");
	char buff[1000];
	FILE *ptr2 = fopen("temp.txt", "r");
	printf("Read writes per device: \n");
	int i;
	for(i = 0; i <8; i++) {

		fscanf(ptr2, "%s", buff);
		fscanf(ptr2, "%s", buff);
		fscanf(ptr2, "%s", buff); //This is the only useful buffer
		printf("%s\n", buff);
		
		fscanf(ptr2, "%s", buff); //This is the number of reads
		printf("Reads: %s\n", buff);
		
		//skip 3 columns and get the 8th value which is writes
		fscanf(ptr2, "%s", buff);
		fscanf(ptr2, "%s", buff); 
		fscanf(ptr2, "%s", buff);
	 
		fscanf(ptr2, "%s", buff); //This is the number of writes
		printf("Writes: %s\n\n", buff);

		//Move to next line
		fgets(buff, 1000, (FILE*) ptr2);
				

	}
	//The number of context switches that the kernel has performed
	//The number of context switches performed by the kernel 
	//can be obtained by running the status command on root with id 1. 
	printf("Context Switches Performed By Kernel Root Process: \n");
	system("cat /proc/1/status | grep switches");	
	printf("\n");
	
	//The time when the system was last booted
	printf("System was last booted on the following time:\n");
	system("last reboot");		
	printf("\n");


	//The number of processes that have been created since the system
	//was last booted
	printf("Processes created since last boot: \n");
	system("cat /proc/stat | grep processes");

}
//*******************This needs Finishing**********************//
//This function implements part D of the assignment
defExtended() {
	//The amount of memory configured into this computer
	printf("********************************Part D**************** \n");
	printf("Total Memory configured into this computer: \n");
	system("cat /proc/meminfo | grep MemTotal");	
	//The amount of memory currenlty available
	printf("\n");
	printf("Memory Available: \n");
	system("cat /proc/meminfo | grep MemFree");
	//A list of load averages (each averaged over the last minute)
	


}



