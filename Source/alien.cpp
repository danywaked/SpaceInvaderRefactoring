#include "alien.h"

Alien::Alien(Vector2 position) noexcept{
	rect.x = position.x;
	rect.y = position.y;
}

float Alien::GetHeight() const noexcept {
	return rect.height;
}

Vector2 Alien::GetGunPosition() const noexcept{
	return Vector2({ rect.x + (rect.width / 2.0f), rect.y });
}

void Alien::Update() noexcept {
	const float window_width = static_cast<float>(GetScreenWidth());
	rect.x += speed;

	if (rect.x >= window_width - rect.width || rect.x <= 0.0f)
	{
		speed *= -1;
		rect.y += 50.0f;
	}
}

void Alien::Render(const Resource& texture) const noexcept {
	DrawTextureV(texture.texture, { rect.x , rect.y }, WHITE);
}