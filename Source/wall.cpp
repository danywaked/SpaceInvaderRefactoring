#include "wall.h"


Wall::Wall(Vector2 position) noexcept{
	rect.x = position.x;
	rect.y = position.y;
}

void Wall::Render(const Resource& texture) const noexcept {
	DrawTextureV(texture.texture, { rect.x, rect.y }, WHITE);
	constexpr int textSize = 40;
	const int textPosX = static_cast<int> (rect.x + rect.width / 3);
	const int textPosY = static_cast<int>(rect.y + rect.height / 2);
	DrawText(TextFormat("%i", health), textPosX, textPosY, textSize, RED);
}