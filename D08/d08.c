#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_COL 10

int countLines(FILE * fp);
void readLines(FILE * fp, char[][MAX_COL]);
int run(char instructions[][MAX_COL], int hasRun[]);
int specialRun(char instructions[][MAX_COL], int hasRun[], int flippedLine, int maxLines);
int readNum(char instruction[MAX_COL]);

int main(void) {
    FILE * fp = fopen("input", "r");
    int lineCount = countLines(fp);
    char instructions[lineCount][MAX_COL];
    int hasRun[lineCount];

    memset( hasRun, 0, lineCount * sizeof(int) );
    rewind(fp);
    readLines(fp, instructions);
    printf("\nAnswer: %d\n", run(instructions, hasRun));
    printf("\nAnswer: %d\n", specialRun(instructions, hasRun, 0, lineCount));
    return 0;
}

int countLines(FILE * fp) {
    char c;
    int lineCount = 0;

    while ((c  = fgetc(fp)) != EOF) {
        if (c == '\n') {
            lineCount++;
        }
    }
    printf("%d", lineCount);
    return lineCount;
}

void readLines(FILE * fp, char arr[][MAX_COL]) {
    char c;
    int row = 0;
    int col = 0;
    while ((c = getc(fp)) != EOF) {
        if (c == '\n') {
            arr[row++][col] = '\0';
            // arr[row++][col] = c;
            col = 0;
        } else {
            arr[row][col++] = c;
        }
    }
}

int specialRun(char instructions[][MAX_COL], int hasRun[], int flippedLine, int maxLines) {
    memset( hasRun, 0, maxLines * sizeof(int) );
    int lineNum = 0;
    int acc = 0;

    while(hasRun[lineNum] == 0) {
        // printf("Running line %d with accumulator at %d\n", lineNum, acc);
        // printf("\t> %s (%d)\n", instructions[lineNum], readNum(instructions[lineNum]));
        hasRun[lineNum] = 1;
        char firstLetter = instructions[lineNum][0];
        firstLetter = lineNum != flippedLine 
            ? firstLetter 
            : firstLetter == 'n'
                ? 'j'
                : firstLetter == 'j'
                    ? 'n'
                    : firstLetter;
        switch(firstLetter) {
            case 'n':
                lineNum++;
                // printf("Line %d\t Acc %d\n", lineNum, acc);
                break;
            case 'j':
                lineNum = lineNum + readNum(instructions[lineNum]);
                // printf("Line %d\t Acc %d\n", lineNum, acc);
                break;
            case 'a':
                acc = acc + readNum(instructions[lineNum]);
                lineNum++;
                // printf("Line %d\t Acc %d\n", lineNum, acc);
                break;
            default:
                printf("'%c' encountered in instruction \n.", instructions[lineNum][0]);
        }
    }
    
    if (lineNum == maxLines) {
        printf("Flipped line %d, reached line %d, with acc %d\n", flippedLine, lineNum, acc);
        return acc;
    } else if (flippedLine >= maxLines){
        printf("Flipped every line...\n");
        return 9999999;
    } else {
        printf("Flipped line %d, reached line %d, with acc %d\n", flippedLine, lineNum, acc);
        return specialRun(instructions, hasRun, flippedLine + 1, maxLines);
    }
}

int run(char instructions[][MAX_COL], int hasRun[]) {
    int lineNum = 0;
    int acc = 0;

    while(hasRun[lineNum] == 0) {
        printf("Running line %d with accumulator at %d\n", lineNum, acc);
        printf("\t> %s (%d)\n", instructions[lineNum], readNum(instructions[lineNum]));
        hasRun[lineNum] = 1;
        switch(instructions[lineNum][0]) {
            case 'n':
                printf("Line %d\t Acc %d\n", ++lineNum, acc);
                break;
            case 'j':
                lineNum = lineNum + readNum(instructions[lineNum]);
                printf("Line %d\t Acc %d\n", lineNum, acc);
                break;
            case 'a':
                acc = acc + readNum(instructions[lineNum]);
                printf("Line %d\t Acc %d\n", ++lineNum, acc);
                break;
            default:
                printf("'%c' encountered in instruction \n.", instructions[lineNum][0]);
        }
    }
    return acc;
}

int readNum(char instruction[MAX_COL]) {
    int result = 0;
    int sign = 1;
    
    switch (instruction[4]) {
        case '-':
            sign = -1;
            break;
        case '+':
            sign = 1;
            break;
        default:
            printf("'%c' encountered instead of '+' or '-'.\n", instruction[4]);
    }
    for(int i = 5; instruction[i] != '\n'; i++) {
        char c = instruction[i];
        if (c < '0' || c > '9') {
            break;
        }
        result = result * 10 + (c - '0');
    }
    return (result * sign);
}
