#include "projectile.h"


Projectile::Projectile(Vector2 position, int p_speed) noexcept
{
	position.x = rect.x;
	position.y = rect.y;
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

	//// UPDATE LINE POSITION
	//lineStart.y = position.y - 15;
	//lineEnd.y = position.y + 15;
	//lineStart.x = position.x;
	//lineEnd.x = position.x;

	if (rect.y < 0 || rect.y > GetScreenHeight())
	{
		active = false;
	}
}

void Projectile::Render(const Resource& texture) const noexcept {
	DrawTextureV(texture.texture,{ rect.x, rect.y}, WHITE);
}