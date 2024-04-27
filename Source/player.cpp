#include "player.h"


Player::Player(float posX) noexcept
{
	rect.width = playerWidth;
	rect.height = playerHeight;
	rect.x = posX;
	rect.y = GetScreenHeight() - rect.height;
}

void Player::Update() noexcept{
	Movement();

	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}
}

void Player::Movement() noexcept{
	if (IsKeyDown(KEY_LEFT))
	{
		rect.x -= speed;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		rect.x += speed;
	}
	if (rect.x < 0 + rect.width)
	{
		rect.x = rect.width;
	}
	else if (rect.x > GetScreenWidth() - rect.width)
	{
		rect.x = GetScreenWidth() - rect.width;
	}
}


void Player::Render(const Resource& texture) const noexcept{
	const auto offsetX = rect.width / 2;
	const auto offsetY = rect.height / 2;
	DrawTextureV(texture.texture, { rect.x - offsetX,rect.y - offsetY }, WHITE);
}