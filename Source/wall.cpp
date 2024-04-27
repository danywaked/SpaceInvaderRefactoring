#include "wall.h"


Wall::Wall(Vector2 position) noexcept
{
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 170;
	rect.height = 76;
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
	const auto offsetX = rect.width / 2;
	const auto offsetY = rect.height / 2;
	DrawTextureV(texture.texture, { GetX() - offsetX, GetY() - offsetY }, WHITE);
	DrawText(TextFormat("%i", health), static_cast<int> (rect.x) - 21, static_cast<int>(rect.y) + 10, 40, RED);
}