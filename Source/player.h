#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)
#include "Resources.h"

class Player
{
	float speed = 7;
	float timer = 0;
	void Movement() noexcept;
public:
	Player(float posX) noexcept;
	float GetWidth() const noexcept;
	float GetHeight() const noexcept;
	float GetX() const noexcept;
	Rectangle rect{};
	int activeTexture = 0;
	float playerWidth = 100;
	float playerHeight = 100;
	int lives = 3;
	void Render(const Resource& texture) const noexcept;
	void Update() noexcept;

};