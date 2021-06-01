/*Yicheng Kang
 *COEN 11
 *Lab 1
 *Wednesday 5:15pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXTIMES 10

int main(void) {
	int amount;
	int dividend;
	int divisor;
	int quotient;
	int correcttimes = 0;
	srand((int) time (NULL));
	for(amount = 0; amount < MAXTIMES; amount++) {
		divisor = rand()%12+1;
		quotient = rand()%13;
		dividend = quotient*divisor;
		correcttimes += 1*divtest(dividend, divisor, quotient);
	}
	printf("You got %d / 10 correct!\n", correcttimes);
}

int divtest(int dividend, int divisor, int quotient) {
	int result;
	printf("What is %d divided by %d?\n", dividend, divisor);
	scanf("%d", &result);
	if(result == quotient) {
		printf("Correct!\n");
	}
	else  {
		printf("Wrong! The correct answer is %d.\n", quotient);
	}
	
	if (result == quotient) {
		return 1;
	}
	return 0;
}
