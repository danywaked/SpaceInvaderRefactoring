#include "alien.h"

Alien::Alien(Vector2 position) noexcept{
	rect.x = position.x;
	rect.y = position.y;
}

void Alien::Update() noexcept {
	const float window_width = static_cast<float>(GetScreenWidth());

	//TODO: 
	//add speed
	//isAtWall()
		//speed *= -1;
		//position.y += 50;


	if (moveRight)
	{
		rect.x += speed;

		if (rect.x >= window_width - rect.width)
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
	DrawTextureV(texture.texture, { rect.x , rect.y }, WHITE);
}