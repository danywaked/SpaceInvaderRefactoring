#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include <string_view>

struct Window 
{
    Window(int width, int height, std::string_view title) noexcept{
        InitWindow(width, height, title.data());
        SetTargetFPS(60);
    }
   bool ShouldClose() const noexcept{
       return WindowShouldClose();
   }
   ~Window() noexcept{
       CloseWindow();
   }

   Window(const Window& other) = delete;
   Window& operator=(const Window& other) = delete;
   Window(Window&& other) = delete;
   Window & operator=(Window && other) = delete;
};