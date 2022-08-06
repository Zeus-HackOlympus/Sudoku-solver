/**
 * @author      : HackOlympus (zeus@hackolympus)
 * @file        : sudoku
 * @created     : Wednesday Aug 03, 2022 21:39:59 IST
 */

#ifndef SUDOKU_H

#define SUDOKU_H

#include <stdio.h> 
#include <stdlib.h> 

void fill_table();
void print_table(); 

int checkall(int row, int col, int num); 
void place_valid_num(int r, int c); 

int finalcheck(); 
int empty_found(); 
int solve(); 


#endif /* end of include guard SUDOKU_H */

