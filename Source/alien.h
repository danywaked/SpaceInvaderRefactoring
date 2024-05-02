#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Resources.h"

class Alien
{
	int speed = 2;
	static constexpr float heightChange = 50.0f;
	static constexpr float alienWidth = 100.0f;
	static constexpr float alienHeight = 100.0f;
public:
	Alien(Vector2 position) noexcept;	
	Rectangle rect{0.0f, 0.0f, alienWidth, alienHeight};
	bool active = true;
	float GetY() const noexcept;
	float GetHeight() const noexcept;
	Vector2 GetGunPosition() const noexcept;
	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
	bool isActive() const noexcept { return active; }
};