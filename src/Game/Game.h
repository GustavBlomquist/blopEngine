#pragma once

#include <SDL2/SDL.h>

const int UPDATE_FPS = 60;
const int MS_PER_UPDATE = 1000 / UPDATE_FPS;

class Game{
    private:
        bool isRunning;
        double updateDeltaTime;
        int millisecsPreviousUpdate;
        double updateTimeAccumulator;
        double interpolationVal;
        SDL_Window* window;
        SDL_Renderer* renderer;
    
    public:
        Game();
        ~Game();

        void Init();
        void Run();
        void Start();
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        static int windowHeight;
        static int windowWidth;
};