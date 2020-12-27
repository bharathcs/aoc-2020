#include <stdio.h>
#include <stdlib.h>

#define LEN_PREAMBLE 25

int part1(void);
int part2(int invalidNum);
double* readFileIntoStorage(void);
double readNum(FILE * fp);
int digitify(char c);
void show(double arr[], int l);
int checkNum(int number, double arr[]);

int main(void) {
    int invalidNum = part1();
    printf("%d\n", part2(invalidNum));
    return 0;
}

int part1(void) {
    FILE * fp = fopen("input", "r");
    double window[LEN_PREAMBLE];
    int oldestIndex = 0;
    double newNum;

    for (int i = 0; i < LEN_PREAMBLE; i++) {
        window[i] = readNum(fp);
    }

    while ((newNum = readNum(fp)) >= 0) {
        if (checkNum(newNum, window) != 1) {
            printf("%.0f was not found in window.\n", newNum);
            return newNum;
        }
        window[oldestIndex++] = newNum;
        if (oldestIndex == LEN_PREAMBLE) {
            oldestIndex = 0;
        }
    }
    return -1;
}

int part2(int invalidNum) {
    double* storage = readFileIntoStorage();
    double* startWindow = storage;
    double* stopWindow = startWindow + 1;
    double sum;
    double largest;
    double smallest;

    for (startWindow = storage; *startWindow >= 0; startWindow++) {
        sum = *startWindow;
        largest = *startWindow;
        smallest = *startWindow;
        for (stopWindow = startWindow + 1; *stopWindow >= 0; stopWindow++) {
            sum = sum + *stopWindow;
            if (largest < *stopWindow) {
                largest = *stopWindow;
            }
            else if (smallest > *stopWindow) {
                smallest = *stopWindow;
            }
            if (sum == invalidNum) {
                printf("Sequence: ");
                for (double* x = startWindow; x <= stopWindow; x++) {
                    printf("%.0f ", *x);
                }
                printf("adds up to the target invalid num. \nLargest, smallest: %.0f, %.0f sum: %.0f\n", largest, smallest, largest+smallest);
                return (largest + smallest);
            }
        }
    }
    return -1;
}

double* readFileIntoStorage(void) {
    FILE * fp = fopen("input", "r");
    size_t size = 100;
    double* storage = malloc(size * sizeof(double));
    double* currentPtr;
    double currentNum;
    int ptrDiff = -1;

    if (storage == NULL) {
        printf("ERROR: MALLOC FAILED. ABORT");
        return storage;
    }
    
    while ((currentNum = readNum(fp)) >= 0) {
        if (++ptrDiff > size ) {
            size = size + 100;
            storage = realloc(storage, size * sizeof(double));
            if (storage == NULL) {
                printf("ERROR: REALLOC FAILED. ABORT");
                return storage;
            }
        }
        currentPtr = storage + ptrDiff;
        *currentPtr = currentNum;
    }
    *(++currentPtr) = -1;
    // show(storage, ptrDiff + 1);
    return storage;
}

double readNum(FILE * fp) {
    if (feof(fp)) {
        return (double) -1;
    }
    int c = fgetc(fp);
    double result = 0;
    result = digitify(c);
    while ((c = getc(fp)) != '\n' && c >= 0) {
        result = result * 10 + digitify(c);
    }
    return result;
}

int digitify(char c) {
    if (c < '0' || c > '9') {
        printf("ERROR: Digitify recieved '%i' instead of digit.\n", c);
    }
    return (c - '0');
}

int checkNum(int number, double arr[]){
    for (double* x = arr; x < arr + LEN_PREAMBLE - 1; x++) {
        for (double* y = x + 1; y < arr + LEN_PREAMBLE; y++) {
            if ((*x + *y) == number) {
                return 1;
            }
        }
    }
    return 0;
}

void show(double* arr, int l) {
    printf("arr: ");
    for (double* i = arr; i - arr <= l; i++) {
        printf("%.0f ", *i);
    }
    printf("\n");
}
