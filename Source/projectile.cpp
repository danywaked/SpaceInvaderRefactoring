#include "projectile.h"


Projectile::Projectile(Vector2 position, int p_speed) noexcept
{
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 9.0f;
	rect.height = 47.0f;
	speed = p_speed;
}

float Projectile::GetWidth() const noexcept
{
	return rect.width;
}

float Projectile::GetHeight() const noexcept
{
	return rect.height;
}

float Projectile::GetX() const noexcept
{
	return rect.x;
}

float Projectile::GetY() const noexcept
{
	return rect.y;
}

void Projectile::Update() noexcept{
	rect.y -= speed;

	if (rect.y < 0 || rect.y > GetScreenHeight())
	{
		active = false;
	}
}

void Projectile::Render(const Resource& texture) const noexcept {
	const auto offsetX = rect.width / 2;
	const auto offsetY = rect.height / 2;
	DrawTextureV(texture.texture,{ rect.x - offsetX, rect.y - offsetY }, WHITE);
}