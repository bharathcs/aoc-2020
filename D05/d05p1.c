#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char * readFile(FILE * fp);
int convert(char c);

int main(void){
    FILE * fp = fopen("input", "r");
    char c;
    int index = 0;
    int storage[851];

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            continue;
        }
        int ROW = index / 10;
        int COL = index % 10;
        index += 1;
        if (COL == 0) {
            storage[ROW] = convert(c) * pow(2, 9 - COL);
        } else {
            storage[ROW] = storage[ROW] + convert(c) * pow(2, 9 - COL);
        }
    }
    int max = 0;
    for (int i = 0; i < 851; i++) {
        printf("%d\n", storage[i]);
        if (max < storage[i]) {
            max = storage[i];
        }
    }
    printf("\n\nMax: %d", max);
    return 0;
}

int convert(char c) {
    switch (c) {
        case 'F':
        case 'L':
            return 0;
        case 'B':
        case 'R':
            return 1;
        default:
            printf("%c\t", c);
            printf("Invalid c!");
            return 0;
    }
}
