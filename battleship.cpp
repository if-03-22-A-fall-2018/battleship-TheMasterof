/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent my_field[FIELDSIZE][FIELDSIZE];
CellContent op_field[FIELDSIZE][FIELDSIZE];
CellContent guess[FIELDSIZE][FIELDSIZE];
void load_game()
{
  FILE* fd_my = fopen("battleship.my", "r");
  FILE* fd_op = fopen("battleship.op", "r");

  for (int i = 0; i < FIELDSIZE; i++) {
    for (int j = 0; j < FIELDSIZE; j++) {
      fread(&my_field[i][j], sizeof(CellContent), 1, fd_my);
      fread(&op_field[i][j], sizeof(CellContent), 1, fd_op);
      guess[i][j]=Unknown;
    }
  }
  fclose(fd_my);
  fclose(fd_op);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col){
  if (row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE) {
    return OutOfRange;
  }

  return my_field[row][col];
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col){
  if (row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE) {
    return false;
  }
  guess[row][col] = op_field[row][col];
  if(guess[row][col] == Boat)
  {
    for (int i = row - 1; i < row + 2; i++)
    {
      for (int j = col - 1; j < col + 2; j++)
      {
        if(guess[i][j] != Boat)
        {
            guess[i][j] = Water;
        }
      }
    }
  }
  return true;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col){
  if (row < 0 || col < 0 || row >= FIELDSIZE || col >= FIELDSIZE) {
    return OutOfRange;
  }

  return guess[row][col];
}
