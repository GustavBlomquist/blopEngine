#pragma once

#include <SDL2/SDL.h>

class Game{
    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
    
    public:
        Game();
        ~Game();

        void Init();
        void Run();
        void Start();
        void Update();
        void ProcessInput();
        void Render();
        void Destroy();

        static int windowHeight;
        static int windowWidth;
};