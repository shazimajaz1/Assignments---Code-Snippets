//Shazim Ajaz
//CSC 60
//Spring 2018



#include <stdio.h>

int main(){
  unsigned char data3[] = {11, 17, 19, 23, 31, 39, 41, 51, 61, 71, 91};
  int size1 = sizeof(data3)/sizeof(data3[0]);
  unsigned char primes[] = {  2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89 , 97 };
  int size2 = sizeof(primes)/sizeof(primes[0]);

  //Printing all the prime numbers in the data 3 table using primes array
  for(int i = 0; i < size1; i++){
    //Checking if the number exists in the primes array
    for(int j = 0; j < size2; j++){
      if(data3[i] == primes[j]) {
        printf("%d\n", data3[i]);
        break;
      }
    }
  }
}
