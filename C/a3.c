//Shazim Ajaz
//CSC 60
//Spring 2018


//This program shuffles the data for the array randomly
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function Declaration
void switchElements(unsigned char *e1, unsigned char *e2);

int main() {
	//Get the array:
  unsigned char data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int random;
  unsigned char temp;
  srand(time(NULL));
	for(int i = 0; i < 10; i++) {
    random = 1 + rand() % (10 - 1);
    switchElements(&data[i], &data[random]);
  }
  

	//Printing the new array on the screen
	for(int j = 0; j < 10; j++) {
		
    printf("%d\n", data[j]);
	}
}

void switchElements(unsigned char *e1,unsigned char *e2){
  unsigned char temp = *e1;
  *e1 = *e2;
  *e2 = temp;
}


