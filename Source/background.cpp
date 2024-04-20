#include "background.h"


float GetRandomFloat(int begin, int end) {
	return static_cast<float>(GetRandomValue(begin, end));
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
		Star newStar; //TODO: dont two step init. use consgtructors
		newStar.initPosition.x = static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150));
		newStar.initPosition.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
		newStar.color = SKYBLUE;
		newStar.size = static_cast<float>(GetRandomValue(1, 4)) / static_cast<float>(2);

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