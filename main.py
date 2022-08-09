#!/usr/bin/env python3 
import os 
from extract import * 

def solve() : 
    os.system("./solve")

def main():
    if os.path.exists("question.jpeg") : 
        extract() 
        if os.path.exists("./solve") : 
            solve() 
        else : 
            os.system("make")
            solve()
    else : 
        print("make a question.jpeg file that contains image of sudoku to solve")


if __name__=='__main__' : 
    main()
