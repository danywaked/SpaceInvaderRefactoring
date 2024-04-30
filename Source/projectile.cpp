#include "projectile.h"


Projectile::Projectile(Vector2 position, int p_speed) noexcept
{
	rect.width = 9.0f;
	rect.height = 47.0f;
	rect.x = position.x ;
	rect.y = position.y;
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
	DrawTextureV(texture.texture,{ rect.x, rect.y}, WHITE);
}