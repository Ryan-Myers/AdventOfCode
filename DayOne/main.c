#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 256

int main(void)
{
    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    char buffer[MAX_LEN];
    int previousValue = 0;
    int valuesHigher = 0;
    while (fgets(buffer, MAX_LEN, fp)) {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = 0;
        //printf("%s\n", buffer);
        if (atoi(buffer) > previousValue) {
            //printf("%s is > %i \n", buffer, previousValue);
            valuesHigher++;
        }
        previousValue = atoi(buffer);
    }

    //Just remove one from here because the first value is going to be higher than the start of 0 by default
    printf("Values Higher: %i\n", valuesHigher - 1);

    fclose(fp);
    return 0;
}