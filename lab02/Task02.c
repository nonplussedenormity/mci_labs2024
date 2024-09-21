#include <stdio.h>

// function to check if a number is an Armstrong Number
int isArmstrong(int num) {
    int originalNum = num;
    int sum = 0;
    int digit;
		//every time we check the next number we take it's cube and add to the sum.
    while (num != 0) {
        digit = num % 10;
        sum += digit * digit * digit; //hardcoded power of the digit as all are going to be 3 digit number
        num /= 10;
    }
		//our return statement checks if the sum is same as the number and returns true (1 in our case) if the number is a Armstrong number 
    return (sum == originalNum);
}

int main() {
    int count = 0;

    printf("Armstrong numbers between 100 and 999:\n");

    for (int i = 100; i <= 999; i++) {
        if (isArmstrong(i)) {
            printf("%d ", i); // printing the Armstrong number
            count++;
            if (count >= 2) {
                break; // stop after finding at least 2 Armstrong numbers
            }
					printf("and ");
        }
    }

    printf("\n");

    return 0;
}
