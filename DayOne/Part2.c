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

    int previousValue = 0;
    int valuesHigher = 0;

    int a = 0;
    int b = 0;
    int c = 0;

    while (fgets(buffer, MAX_LEN, fp)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;

		c = b;
		b = a;
		a = atoi(buffer);

		//Just a dumb check to see if we're at the third iteration yet.
        if (c != 0) {
			if ((a + b + c) > previousValue) {
				valuesHigher++;
			}
            previousValue = a + b + c;
        }
    }

    //Just remove one from here because the first value is going to be higher than the start of 0 by default
    printf("Values Higher: %i\n", valuesHigher - 1);

    fclose(fp);
    return 0;
}