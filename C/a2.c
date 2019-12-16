//Shazim Ajaz
//CSC 60
//Spring 2018


//This program checks to see if the array only contains letters and digits
#include <stdio.h>

int main() {
	char data[]  = {'h','e','l','l','o','1','2','+'};
	int cond = 1;
	//Using Ascii values of charcters to make comparisons
	for(int i = 0; i <sizeof(data); i++) {
		if(data[i] < 48 || (data[i] > 57 && data[i] < 65) || (data[i] > 90 && data[i] < 97 ) || data[i] > 122) {
			printf("%s\n", "It does not contain all letters or digits");
			cond = 0;
			break;
		}
	}
	//At this point if the condition is true then there are all letters
	if(cond) {
		printf("%s\n", "It contains only letters and digits");
	}

}

