#include "background.h"


float GetRandomFloat(int begin, int end) noexcept{
	return static_cast<float>(GetRandomValue(begin, end));
}

Star::Star(float x, float y) noexcept : position({ x, y }) {
	size = GetRandomFloat(1, 4)/2.0f;
}

void Star::Render() const noexcept{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

Background::Background(int starAmount) {
	stars.reserve(starAmount);
	for (int i = 0; i < starAmount; i++)
	{
		float x = (GetRandomFloat(-150, GetScreenWidth() + 150));
		float y = (GetRandomFloat(0, GetScreenHeight()));
		stars.emplace_back(x, y);
	}
}

void Background::Render() const noexcept {
	for (auto& s : stars) {
		s.Render();
	}
}