/**
 * @author      : HackOlympus (zeus@hackolympus)
 * @file        : sudoku
 * @created     : Wednesday Aug 03, 2022 21:38:55 IST
 */


#include "sudoku.h" 

int table[9][9];  

void fill_table()
{
    FILE *f = fopen("./input", "r"); 
    int r=0, c=0;
    while (r < 9) {
        while (c < 9) {
            char ch = fgetc(f); 
            if (ch == '.') {
                table[r][c] = -1; 
                c++; 
            } else if (ch == '\n') {
                ; 
            } else {
                table[r][c] = (int)ch - '0'; 
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
    for (int r=0; r < 9; r++) {
        for (int c=0; c < 9; c++) {
            if (table[r][c] != -1) {
                printf("%d ",table[r][c]); 
            } else {
                printf(". "); 
            }
        }
        printf("\n"); 
    }
}



int checkall(int row, int col, int num)
{

    // Pretty cool way to regulate the input in multiples of 3 
    int brow = row - (row % 3); 
    int bcol = col - (col % 3);
    
    // check for row    
    for (int r=0; r < 9; r++) {
        if (table[r][col] == num) {
                return 0; 
            } 
        }
    
    for (int c=0; c < 9; c++) {
        if (table[row][c] == num) { 
            return 0;  
        }
    }

    // check for number in box 
    for (int r=0; r < 3; r++) {
        for (int c=0; c < 3; c++) {
            if (r != row && c != col) {    // not count itself 
                if (table[brow+r][bcol+c] == num) {
                    return 0; 
                }
            }
        }
    }

    return 1; 
}


int empty_found()
{
    for (int r=0; r < 9; r++) {
        for (int c=0; c < 9; c++) {
            if (table[r][c] == -1) {
                return 1; 
            }
        }
    }
    return 0; 
}

int solve()
{
    for (int r=0; r < 9; r++) {
        for (int c=0; c < 9; c++) {
            if (table[r][c] == -1) {
                for (int num = 1; num <= 9; num++) {
                    if (checkall(r,c,num)) {
                        table[r][c] = num;   
                        if (solve()) {
                            //print_table(); 
                            return 1; 

                        } else {
                            table[r][c] = -1; 
                        }
                    }
                }
                return 0; 
            }
        }
    }
    return 1; 
}

int main()
{
    fill_table(); 
    puts("Input table:"); 
    print_table(); 
    if (solve()) {
        puts("Output table:"); 
    } else {
        printf("Error occured\n"); 
    }
    print_table(); 
    return 0; 
}
