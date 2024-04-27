#include "background.h"


float GetRandomFloat(int begin, int end) noexcept{
	return static_cast<float>(GetRandomValue(begin, end));
}

Star::Star(Vector2 position)
{
}

void Star::Update(float starOffset)noexcept {
	position.x = initPosition.x + starOffset;
	position.y = initPosition.y;
}

void Star::Render()noexcept{
	DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), size, color);
}

void Background::Initialize(int starAmount) noexcept {
	for (int i = 0; i < starAmount; i++)
	{
		Star newStar{}; //TODO: dont two step init. use consgtructors
		newStar.initPosition.x = (GetRandomFloat(-150, GetScreenWidth() + 150.0f));
		newStar.initPosition.y = (GetRandomFloat(0, GetScreenHeight()));
		newStar.color = SKYBLUE;
		newStar.size = (GetRandomFloat(1, 4)) / 2.0f;

		Stars.push_back(newStar);
	}
}

void Background::Update(float offset) noexcept{
	for (auto& s : Stars) {
		s.Update(offset);
	}
}

void Background::Render() noexcept {
	for (auto& s : Stars) {
		s.Render();
	}
}