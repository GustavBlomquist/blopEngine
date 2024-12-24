#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char*argv[]){

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL intitialized \n";
    } else{
        std::cout << "SDL couldn't intitialze " << SDL_GetError() << "\n";
    }

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
    
    sol::load_result script = lua.load_file("../assets/scripts/test.lua");

    if(script.valid()){
       lua.script_file("../assets/scripts/test.lua"); 
        std::cout << "The current directory is: " << std::filesystem::current_path() << "\n"; 
    } else{
        sol::error err = script;
        std::cout << "Lua script error: " << err.what() << "\n";
    }

    
    glm::vec2 test = glm::vec2(6.5, 4.5);

    std::cout << "Here is a vector that im printing " << std::to_string(test.x) << " " << std::to_string(test.y) << " \n";
    return 0;
}