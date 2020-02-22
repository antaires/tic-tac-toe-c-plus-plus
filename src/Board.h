#ifndef BOARD_H
#define BOARD_H

#include "./Constants.h"
#include <iostream>

class Board {
private:
  char board[ROW][COLUMN];
  unsigned int gameState;
  unsigned int moveCount;
  void SetGameState();
  char winner;
  void Print();
public:
  Board();
  ~Board();
  bool GameOver();
  bool XWin();
  bool OWin();
  bool Update(char piece, unsigned int row, unsigned int column);
  char GetCell(unsigned int row, unsigned int column);
  void GetEmptyCell(unsigned int& row, unsigned int& column);
  void Destroy();
};

#endif
