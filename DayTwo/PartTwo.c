#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main(void) {
    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];

	int charToInt = 0;
    int horizontal = 0;
    int depth = 0;
	int aim = 0;

    while (fgets(buffer, MAX_LEN, fp)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
		charToInt = (int)buffer[strlen(buffer) - 1] - (int)48;

		switch (buffer[0]) {
			case 'f':
				horizontal += charToInt;
				if (aim != 0) depth += charToInt * aim;
				//printf("Forward: %i - Depth: %i\n", charToInt, depth);
				break;
			case 'd':
				aim += charToInt;
				//printf("Down: %i - Aim: %i\n", charToInt, aim);
				break;
			case 'u':
				aim -= charToInt;
				//printf("Up: %i - Aim: %i\n", charToInt, aim);
				break;
			default:
				printf("WTF: %s\n", buffer);
		}

		//printf("Depth: %i\n", depth);
    }

	printf("Horizontal: %i\n", horizontal);
	printf("Depth: %i\n", depth);
	printf("Aim: %i\n", aim);
	printf("Answer: %i\n", depth * horizontal);

    fclose(fp);
    return 0;
}