/**
 * @author      : HackOlympus (zeus@hackolympus)
 * @file        : sudoku
 * @created     : Wednesday Aug 03, 2022 21:39:59 IST
 */

#ifndef SUDOKU_H

#define SUDOKU_H

#include <stdio.h> 
#include <stdlib.h> 

typedef struct cell {
    int num; 
    int state; // filled or not
} cell;  

void init_table(); 
void fill_table();
void print_table(); 

#endif /* end of include guard SUDOKU_H */

