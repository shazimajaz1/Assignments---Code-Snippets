//Shazim Ajaz(N)
//CSC 60
//Spring 2018


//This program checks if all the alphabets are present or not
#include <stdio.h>

int main() {
  //Test String
  char data[]={'a', 'b', 'c', 'D', 'E', 'f', 'g', 'h', 'I', 'J', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 
  int lowercase = 97; //upto 122
  int uppercase = 65; //upto 90
  int condition = 1;
  int i;
  while(lowercase <= 122) {
    //Take the character and try to find it in the enire array: if found then move on else set the condtion to false and break out of the loop.
    
    for(i = 0; i <= (sizeof(data)/sizeof(data[0])); i++){
      condition = 1;
      //if the character is found, break the loop
      if(data[i] == lowercase || data[i] == uppercase){
        break; //break the for loop
      }
      else { //if not found
        condition = 0;
      }
    }
    if(condition){
      //Means that the character is not found
      printf("%s", "Character(s) are/is missing!");
      break;
    } //else continue with the process
    lowercase++;
    uppercase++;
  }
}


