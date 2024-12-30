#include "./Game.h"

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#include <iostream>

int Game::windowWidth;
int Game::windowHeight;

Game::Game(){
    isRunning = false;
    
    spdlog::info("Game constructor called");
}

Game::~Game(){
    spdlog::info("Game destructor called");
}

void Game::Init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        spdlog::critical("SDL failed to initialize");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 1280;
    windowHeight = 720;
    window = SDL_CreateWindow(
        "Blop Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if(!window){
        spdlog::critical("Window falied to intitialize");
        return;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        0
    );
    if(!renderer){
        spdlog::critical("Renderer failed to initialize");
        return;
    }

    updateDeltaTime = MS_PER_UPDATE / 1000.0;
    updateTimeAccumulator = 0.0;
    millisecsPreviousUpdate = SDL_GetTicks64();

    isRunning = true;
}

void Game::Start(){

}

void Game::ProcessInput(){
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)){

        switch(sdlEvent.type){
            case SDL_QUIT:
                isRunning = false;
                break;
            
            case SDL_KEYDOWN:
                if(sdlEvent.key.keysym.sym == SDLK_F1){
                    isRunning = false;
                }

                break;
            
            default:
                break;
        }
    }
}

void Game::Update(){
    double updateTime = (SDL_GetTicks64() - millisecsPreviousUpdate) / 1000.0;
    // Ensure that we don't get an infinite loop if computer cannot catch up
    if(updateTime > 0.25)
        updateTime = 0.25;

    // Store updatetime to compare next update.
    millisecsPreviousUpdate = SDL_GetTicks64();

    updateTimeAccumulator += updateTime;

    // All updates are done within this loop.
    while(updateTimeAccumulator >= updateDeltaTime){
        // TODO: Update systems



        updateTimeAccumulator -= updateDeltaTime;
    }
    interpolationVal = updateTimeAccumulator / updateDeltaTime;
}

void Game::Render(){
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Run(){
    Start();
    while(isRunning){
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}