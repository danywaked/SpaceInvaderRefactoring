#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

struct Window {
    Window(int width, int height, const char* title) noexcept
    {
        InitWindow(width, height, title);
        SetTargetFPS(60);
    }
   bool ShouldClose() const noexcept
   {
       return WindowShouldClose();
   }
   ~Window() noexcept
   {
       CloseWindow();
   }

   Window(const Window& other) = delete;
   Window& operator=(const Window& other) = delete;
   Window(Window&& other) = delete;
   Window & operator=(Window && other) = delete;

};
