#include <iostream>
#include "./Constants.h"
#include "./Game.h"

SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
  board = new Board();
  this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
  return this->isRunning;
}

void Game::Initialize(int width, int height){
  // create all SDL inits / flow
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cerr<< "Error Initializing SDL" << std::endl;
    return;
  }
  window = SDL_CreateWindow(
    NULL
    , SDL_WINDOWPOS_CENTERED
    , SDL_WINDOWPOS_CENTERED
    , width
    , height
    , SDL_WINDOW_BORDERLESS
  );
  if (!window){
    std::cerr<<"Error Creating SDL Window" << std::endl;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1 , 0);
  if (!renderer){
    std::cerr<<"Error Creating SDL Renderer" << std::endl;
    return;
  }

  LoadLevel(0);

  isRunning = true;
  return;
}

void Game::LoadLevel(int levelNumber){
  // TODO Initialize board

}

void Game::ProcessInput(){
  SDL_PollEvent(&event);
  switch(event.type){
    case SDL_QUIT: { // clicking 'x button' on window
      isRunning = false;
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE){
        isRunning = false;
      }
    }
    default: {
      break;
    }
  }
}

void Game::Update(){
  // wait until FRAME_TARGET_TIME reached since last frame
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

  // delta time is difference in ticks from last frame converted to seconds
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  // clamp to max value - set max deltaTime, in case of debugging or delay
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  // sets the new ticks for the current frame to be used in the next pass
  ticksLastFrame = SDL_GetTicks();

  // use delta time to update my game objects
  board->Update(deltaTime);

}

void Game::Render(){
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);

  // clear back buffer
  SDL_RenderClear(renderer);

  if (board->GameOver()){
    return;
  }
  board->Render();

  // swap buffers and render
  SDL_RenderPresent(renderer);
}

void Game::Destroy(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}