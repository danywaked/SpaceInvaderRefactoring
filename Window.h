#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

struct Window {
    Window(int screenWidth, int screenHeight, const char* title)
    {
        InitWindow(screenWidth, screenHeight, title);
        SetTargetFPS(60);
    }
   bool ShouldClose() const
   {
       return WindowShouldClose();
   }
   ~Window()
   {
       CloseWindow();
   }
};
