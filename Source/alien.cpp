#include "alien.h"

Alien::Alien(Vector2 position) noexcept
{
	rect.x = position.x;
	rect.y = position.y;
	rect.width = alienWidth;
	rect.height = alienHeight;
}

void Alien::Update() noexcept {
	const int window_width = GetScreenWidth();

	if (moveRight)
	{
		rect.x += speed;

		if (rect.x >= window_width)
		{
			moveRight = false;
			rect.y += 50;
		}
	}
	else
	{
		rect.x -= speed;

		if (rect.x <= 0)
		{
			moveRight = true;
			rect.y += 50;
		}
	}
}

void Alien::Render(const Resource& texture) const noexcept {
	DrawTextureV(texture.texture, { rect.x - offset, rect.y - offset }, WHITE);
}