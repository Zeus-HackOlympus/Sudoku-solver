/**
 * @author      : HackOlympus (zeus@hackolympus)
 * @file        : sudoku
 * @created     : Wednesday Aug 03, 2022 21:38:55 IST
 */


#include "sudoku.h" 

cell* table[9][9]; 

void init_table()
{
    for (int r=0; r < 9; r++) {
        for (int c=0; c < 9; c++) {
            table[r][c] = (cell*) malloc(sizeof(cell)); 
        }
    }
}

void fill_table()
{
    init_table(); 
    FILE *f = fopen("./input", "r"); 
    int r=0, c=0;
    while (r < 9) {
        while (c < 9) {
            char ch = fgetc(f); 
            if (ch == '.') {
                table[c][r]->num = -1; 
                table[c][r]->state = 0;
                c++; 
            } else if (ch == '\n') {
                ; 
            } else {
                table[c][r]->num = (int)ch - '0'; 
                table[c][r]->state = 1; 
                c++; 
            }
        }
        r++; 
        c=0; 
    }
    fclose(f); 
}

void print_table()
{
    printf("Input table:\n"); 
    for (int r=0; r < 9; r++) {
        for (int c=0; c < 9; c++) {
            if (table[c][r]->state) {
                printf("%d",table[c][r]->num); 
            } else {
                printf("."); 
            }
        }
        printf("\n"); 
    }
}

int main()
{
    fill_table(); 
    print_table(); 
    return 0; 
}
