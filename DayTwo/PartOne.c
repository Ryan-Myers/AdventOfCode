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

    while (fgets(buffer, MAX_LEN, fp)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
		charToInt = (int)buffer[strlen(buffer) - 1] - (int)48;

		switch (buffer[0]) {
			case 'f':
				//printf("Forward: %i\n", charToInt);
				horizontal += charToInt;
				break;
			case 'd':
				//printf("Down: %i\n", charToInt);
				depth += charToInt;
				break;
			case 'u':
				//printf("Up: %i\n", charToInt);
				depth -= charToInt;
				break;
			default:
				printf("WTF: %s\n", buffer);
		}

		//printf("Depth: %i\n", depth);
    }

	printf("Horizontal: %i\n", horizontal);
	printf("Depth: %i\n", depth);
	printf("Answer: %i\n", depth * horizontal);

    fclose(fp);
    return 0;
}