#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Resources.h"

class Projectile
{
public:
	Projectile(Vector2 position, int p_speed)noexcept;
	Rectangle rect{};
	float GetWidth() const noexcept;
	float GetHeight() const noexcept;
	float GetX() const noexcept;
	float GetY() const noexcept;
	bool active = true;
	int speed = 15;
	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
};