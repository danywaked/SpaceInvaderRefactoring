#include "player.h"


Player::Player(float posX) noexcept{
	rect.x = posX;
	rect.y = GetScreenHeight() - rect.height;
}

float Player::GetWidth() const noexcept{
	return rect.width;
}

float Player::GetHeight() const noexcept{
	return rect.height;
}

float Player::GetX() const noexcept{
	return rect.x;
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
	const float window_width = static_cast<float>(GetScreenWidth());
	if (rect.x <= 0.0f )
	{
		rect.x = 0.0f;
	}
	else if (rect.x > window_width - rect.width)
	{
		rect.x = window_width - rect.width;
	}
}


void Player::Render(const Resource& texture) const noexcept{
	DrawTextureV(texture.texture, { rect.x ,rect.y }, WHITE);
}