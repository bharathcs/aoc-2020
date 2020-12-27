#include <stdlib.h>
#include <stdio.h>

#define INPUTFILE "input"

int* readFileIntoStorage(int* arrayLength);
int readNum(FILE * fp);
int digitify(char c);
int* joltDelta(int* arr, int length);
void part1(int* storage, int length);

void show(int arr[], int l);
void quicksort(int* arr, int low, int high);
int partition(int* arr, int low, int high);
void swap(int* first, int* second);

int main(void){
    int length = 0; // length of storage array
    // int* storage = readFileIntoStorage(&length);
    int* storage = readFileIntoStorage(&length);

    quicksort(storage, 0, length - 1);
    show(storage, length - 1);
    // part1(storage, length);
    
    free(storage);
    return 0;
}

void part1(int* storage, int length){
    int* joltDiff = joltDelta(storage, length);
    quicksort(joltDiff, 0, length - 1);
    show(joltDiff, length - 1);
    free(joltDiff);
} 

int* readFileIntoStorage(int* arrayLength) {
    FILE * fp = fopen(INPUTFILE, "r");
    size_t size = 100;
    int* storage = malloc(size * sizeof(double));
    int* currentPtr;
    int currentNum;
    int ptrDiff = -1;

    if (storage == NULL) {
        printf("ERROR: MALLOC FAILED. ABORT");
        fclose(fp);
        return storage;
    }
    
    while ((currentNum = readNum(fp)) >= 0) {
        if (++ptrDiff > size ) {
            size = size + 100;
            storage = realloc(storage, size * sizeof(int));
            if (storage == NULL) {
                printf("ERROR: REALLOC FAILED. ABORT");
                fclose(fp);
                return storage;
            }
        }
        currentPtr = storage + ptrDiff;
        *currentPtr = currentNum;
    }
    *(++currentPtr) = -1;
    show(storage, ptrDiff);
    *arrayLength = ptrDiff + 1;
    fclose(fp);
    return storage;
}

int readNum(FILE * fp) {
    if (feof(fp)) {
        return -1;
    }
    int c = fgetc(fp);
    if (c < 0) {
        // no idea why this has to be done, but it appears to
        // work this way. feof(fp) doesn't register end-of-file
        // but c == -1 signals the end of file properly.
        return -1;
    }
    int result = 0;
    result = digitify(c);
    while ((c = getc(fp)) != '\n' && c >= 0) {
        result = result * 10 + digitify(c);
    }
    return result;
}

int digitify(char c) {
    if (c < '0' || c > '9') {
        printf("ERROR: Digitify recieved '%c (%i)' instead of digit.\n", c, c); 
    }
    return (c - '0');
}

void show(int* arr, int l) {
    printf("arr: ");
    for (int* i = arr; i - arr <= l; i++) {
        printf("%d ", *i);
    }
    printf("\n");
}

void quicksort(int* arr, int low, int high) {
    if (high <= low) {
        return;
    }
    int pivotPos = partition(arr, low, high);
    quicksort(arr, low, pivotPos - 1);
    quicksort(arr, pivotPos + 1, high);
}

int partition(int* arr, int low, int high) {
    int pivot = *(arr + high);
    int lastSmallerPos = (low - 1);

    for (int currPos = lastSmallerPos + 1; currPos <= high; currPos++){
        if (*(arr + currPos) < pivot) {
            lastSmallerPos++;
            swap(arr + lastSmallerPos, arr + currPos);
        }
    }
    swap(arr + lastSmallerPos + 1, arr + high);
    return lastSmallerPos + 1;
}

void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

int* joltDelta(int* arr, int length) {
    int* diffArr = malloc(length * sizeof(int));
    int* diffIndex = diffArr;
    int* i = arr;
    *(diffIndex++) = *i - 0;
    for (i++; i - arr < length; i++) {
        *(diffIndex++) = *i - *(i - 1);
    }
    return diffArr;
}
