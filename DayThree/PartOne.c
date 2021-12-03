#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
**  Bit set, clear, and test operations
**
**  public domain snippet by Bob Stout
*/

typedef enum {ERROR = -1, FALSE, TRUE} LOGICAL;

#define BOOL(x) (!(!(x)))

#define BitSet(arg,posn) ((arg) | (1L << (posn)))
#define BitClr(arg,posn) ((arg) & ~(1L << (posn)))
#define BitTst(arg,posn) BOOL((arg) & (1L << (posn)))
#define BitFlp(arg,posn) ((arg) ^ (1L << (posn)))


#define BITSPERLINE 12

int main(void) {
    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

	char bits[BITSPERLINE];
	int bitCounterPositive[BITSPERLINE];	
	int bitCounterNegative[BITSPERLINE];

	//Default array values to zero, but allow the array to grow with BITSPERLINE being redefined.
	memset(bitCounterPositive, 0, sizeof bitCounterPositive);
	memset(bitCounterNegative, 0, sizeof bitCounterNegative);

	while(fscanf(fp, "%s", bits) != EOF) {
		for (int i = 0; i < BITSPERLINE; i++) {
			if (bits[i] == '0') {
				bitCounterNegative[i]++;
			}
			else {
				bitCounterPositive[i]++;
			}
		}
	}

	int gammaRate = 0;
	int epsilonRate = 0;

	for (int i = 0 ; i < BITSPERLINE; i++) {
		if (bitCounterPositive[i] > bitCounterNegative[i]) {
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