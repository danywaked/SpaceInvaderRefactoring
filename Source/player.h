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
	static constexpr float timerMax = 0.4f;
	static constexpr float playerWidth = 100.0f;
	static constexpr float playerHeight = 100.0f;
	void Movement() noexcept;
	void Animation() noexcept;
public:
	Player(float posX) noexcept;
	float GetWidth() const noexcept;
	float GetHeight() const noexcept;
	float GetX() const noexcept;
	Rectangle rect{0.0f,0.0f,playerWidth,playerHeight};
	int activeTexture = 0;
	int lives = 3;
	void Render(const Resource& texture) const noexcept;
	void Update() noexcept;

};