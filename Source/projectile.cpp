#include "projectile.h"


Projectile::Projectile(Vector2 position, int p_speed) noexcept{
	rect.x = position.x ;
	rect.y = position.y;
	speed = p_speed;
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