#include <iostream>
#include "./Constants.h"
#include "./Game.h"
// #include "../lib/glm/glm.hpp" todo needed? if not, remove library

Board* Game::board;

Game::Game() {
  this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  this->graphics = new Graphics();
  graphics->Initialize(width, height);
  Start();
  isRunning = true;
  return;
}

void Game::Start(){
  this->board = new Board();
  // todo later, choose who starts (x always 1st)
  this->currentPlayer = HUMAN;
  this->currentMove = 'X';
  this->row = ROW;
  this->column = COLUMN;
}

void Game::ProcessInput(){
  if (!graphics->ProcessInput(currentPlayer, isRunning, row, column)){
    isRunning = false;
  }
}

void Game::ProcessAI(){
  // todo update AI
  if (currentPlayer == PC){
    board->GetEmptyCell(row, column);
  }
}

void Game::Update(){
  // make move
  if (board->Update(currentMove, row, column)){
    Game::TogglePlayer();
  }
}

void Game::Render(){
  graphics->Render(board);
  if (graphics->Quit()){
    this->isRunning = false;
    return;
  }
}

void Game::TogglePlayer(){
  if (currentPlayer == HUMAN){
    currentPlayer = PC;
    currentMove = 'O';
  } else {
    currentPlayer = HUMAN;
    currentMove = 'X';
  }
}

void Game::Destroy(){
  graphics->Destroy();
}
