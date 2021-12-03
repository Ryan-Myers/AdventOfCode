#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BITSPERLINE 12

int main(void) {
    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

	char bits[BITSPERLINE];
	int bitCounterOne[BITSPERLINE];	
	int bitCounterZero[BITSPERLINE];

	//Default array values to zero, but allow the array to grow with BITSPERLINE being redefined.
	memset(bitCounterOne, 0, sizeof bitCounterOne);
	memset(bitCounterZero, 0, sizeof bitCounterZero);

	while(fscanf(fp, "%s", bits) != EOF) {
		for (int i = 0; i < BITSPERLINE; i++) {
			if (bits[i] == '0') {
				bitCounterZero[i]++;
			}
			else {
				bitCounterOne[i]++;
			}
		}
	}

	int gammaRate = 0;
	int epsilonRate = 0;

	for (int i = 0 ; i < BITSPERLINE; i++) {
		if (bitCounterOne[i] > bitCounterZero[i]) {
			//We're setting the bits most significant first 
			gammaRate |= 1UL << BITSPERLINE - 1 - i;
		}
		else {
			epsilonRate |= 1UL << BITSPERLINE - 1 - i;
		}
	}

	printf("gammaRate: %i\nepsilonRate: %i\nPower Consumption: %i\n", gammaRate, epsilonRate, gammaRate * epsilonRate);

    fclose(fp);
    return 0;
}