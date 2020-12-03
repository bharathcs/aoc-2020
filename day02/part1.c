#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *inputfile;
    int MAX_LINE_LENGTH = 20; 
    char *line = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    inputfile = fopen("input", "r");
    
    while ((line = fgets(line, MAX_LINE_LENGTH, inputfile))){
        printf("%s", line);
    }
    printf("Test");
    free(line);
}
