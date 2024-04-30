#include "game.h"
#include <iostream>


int main(void){    
    try {
        Game game;
        game.Run();
    } 
    catch(const std::runtime_error& e){
        std::cerr << "Runtime error " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error occured. Exiting." << std::endl;
    }
    
    return 0;
}