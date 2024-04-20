#include "projectile.h"


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
	position.y -= speed;

	// UPDATE LINE POSITION
	lineStart.y = position.y - 15;
	lineEnd.y = position.y + 15;
	lineStart.x = position.x;
	lineEnd.x = position.x;

	if (position.y < 0 || position.y > GetScreenWidth())
	{
		active = false;
	}
}

void Projectile::Render(const Resource& texture) const noexcept{
	DrawTexture(texture.texture, position.x, position.y, WHITE);
}