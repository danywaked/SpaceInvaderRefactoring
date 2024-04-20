#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "game.h"
#include <iostream>


int main(void)
{    
    try {
        Game game(resolution, title);
        game.run();
        //put this stuff in .run()
        //Game game = { State::STARTSCREEN };
        //while (!WindowShouldClose())    // Detect window close button or ESC key
        //{
        //    game.Update();

        //    BeginDrawing();
        //    ClearBackground(BLACK);
        //    game.Render();
        //    EndDrawing();
        //}
        //CloseWindow();
    } 
    catch(const std::runtime_error& e){
        std::cerr << "Runtime error " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown error occured. Exiting." << std::endl;
    }
    
    return 0;
}