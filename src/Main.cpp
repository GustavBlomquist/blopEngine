#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include <iostream>
#include <string>

int main(int argc, char*argv[]){
    if(SDL_INIT_EVERYTHING){
        std::cout << "SDL intitialized \n";
    }

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
    
    glm::vec2 test = glm::vec2(6.5, 4.5);

    std::cout << "Here is a vector that im printing " << std::to_string(test.x) << " " << std::to_string(test.y) << " \n";
    return 0;
}