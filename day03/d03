#include <stdio.h>
#include <stdlib.h>

int find_row_len(void);
int find_no_rows(int);
int find_trees_hit(int right_step, int down_step);

int main(void){
    printf("%d * ", find_trees_hit(1, 1));
    printf("%d * ", find_trees_hit(3, 1));
    printf("%d * ", find_trees_hit(5, 1));
    printf("%d * ", find_trees_hit(7, 1));
    printf("%d   ", find_trees_hit(1, 2));
    return 0;
}

int find_trees_hit(int right_step, int down_step){
    FILE *f = fopen("input", "r");
    int MAX_ROW_LEN = find_row_len();
    int MAX_ROWS = find_no_rows(MAX_ROW_LEN);
    int slope[MAX_ROWS][MAX_ROW_LEN];
    int result = 0;
    int x = 0;
    int y = 0;
    char c;

    while (!feof(f)) {
        c = fgetc(f);
        if (c == '\n') {
            x = 0;
            y += 1;
        } else { 
            slope[y][x] = c == '#' ? 1 : 0;
            x += 1;
        }
    }
    for (int i = 0, j = 0; i < MAX_ROWS; i = i + down_step) {
        result = result + slope[i][j];
        j = (j + right_step) % MAX_ROW_LEN;
    }
    fclose(f);
    return result;
}

int find_row_len(void){
    FILE *f = fopen("input", "r");
    char c;
    int x = 0;

    while ((c = fgetc(f)) != '\n') {
        x += 1;
    }

    fclose(f);

    return x;
}

int find_no_rows(int row_len){
    FILE *f = fopen("input", "r");
    char c;
    int x = 0;

    while ((c = fgetc(f)) != EOF) {
        x = x + ((c == '\n') ? 1 : 0);
    }

    fclose(f);

    return x;
}
