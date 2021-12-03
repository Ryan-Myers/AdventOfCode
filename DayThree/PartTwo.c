#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BITSPERLINE 5

int main(void) {
    FILE* fp;
    fp = fopen("inputTest.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

	char bits[BITSPERLINE];
	int bitCounterOne[BITSPERLINE];	
	int bitCounterZero[BITSPERLINE];
	int linesInFile = 0;

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
		linesInFile++;
	}

	//Reset the file pointer to the start of the file so we can read it again
	rewind(fp);

	int gammaRate = 0;
	int epsilonRate = 0;
	int oxygenRateBitsToCheck = 0;

	for (int i = 0 ; i < BITSPERLINE; i++) {
		if (bitCounterOne[i] >= bitCounterZero[i]) {
			//We're setting the bits most significant first 
			gammaRate |= 1UL << BITSPERLINE - 1 - i;
			oxygenRateBitsToCheck |= 1UL << BITSPERLINE - 1 - i;
		}
		else {
			epsilonRate |= 1UL << BITSPERLINE - 1 - i;
		}
		printf("Same: %i - %i - %i\n", i, bitCounterOne[i], bitCounterZero[i]);

		if (bitCounterOne[i] == bitCounterZero[i]) {
			printf("Same: %i\n", i);
		 	oxygenRateBitsToCheck &= 0UL << BITSPERLINE - 1 - i;
		}
	}

	//fileContents = ROWS:COLUMNS - LAST COLUMN will be an active flag
	char fileContentsOxygen[linesInFile][BITSPERLINE + 2];
	memset(fileContentsOxygen, 0, sizeof fileContentsOxygen);

	int oxygenRowsLeft = linesInFile;

	for (int row = 0; row < linesInFile; row++) {
		fscanf(fp, "%s", fileContentsOxygen[row]);
		//default each row as active
		fileContentsOxygen[row][BITSPERLINE] = 'A';
	}

	for (int column = 0; column < BITSPERLINE; column++) {
		for (int row = 0; row < linesInFile; row++) {
			if (oxygenRowsLeft > 1 && fileContentsOxygen[row][BITSPERLINE] == 'A') {
				if (((oxygenRateBitsToCheck & (1UL << BITSPERLINE - 1 - column)) && fileContentsOxygen[row][column] != '1') ||
			       (!(oxygenRateBitsToCheck & (1UL << BITSPERLINE - 1 - column)) && fileContentsOxygen[row][column] != '0')) {

					printf("Inactivating Row %i for column %i: %s\n", row, column, fileContentsOxygen[row]);
					fileContentsOxygen[row][BITSPERLINE] = 'I';
					oxygenRowsLeft--;
				}
			}
		}
	}

	for (int i; i < linesInFile; i++) {
		printf("Row %i: %s\n", i, fileContentsOxygen[i]);
	}

	printf("oxygenRateBitsToCheck: %i\n", oxygenRateBitsToCheck);

	printf("gammaRate: %i\nepsilonRate: %i\nPower Consumption: %i\n", gammaRate, epsilonRate, gammaRate * epsilonRate);

    fclose(fp);
    return 0;
}