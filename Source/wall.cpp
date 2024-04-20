#include "wall.h"


void Wall::SetPosition(float x, float y) noexcept
{
	rect.x = x;
	rect.y = y;
}
float Wall::GetX() const noexcept
{
	return rect.x;
}

float Wall::GetY() const noexcept
{
	return rect.y;
}

float Wall::GetWidth() const noexcept
{
	return rect.width;
}

float Wall::GetHeight() const noexcept
{
	return rect.height;
}

void Wall::Render(const Resource& texture) const noexcept {
	DrawTexture(texture.texture, GetX() - 100.0f, GetY() - 100.0f, WHITE);
	DrawText(TextFormat("%i", health), static_cast<int> (position.x) - 21, static_cast<int>(position.y) + 10, 40, RED);
}

void Wall::Update() noexcept {
	if (health < 1)
	{
		active = false;
	}
}