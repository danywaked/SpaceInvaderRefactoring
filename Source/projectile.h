#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Resources.h"

class Projectile
{
	static constexpr float width = 9.0f;
	static constexpr float height = 47.0f;

public:
	Projectile(Vector2 position, int p_speed)noexcept;
	Rectangle rect{0.0f,0.0f,width,height};
	float GetWidth() const noexcept;
	float GetHeight() const noexcept;
	float GetX() const noexcept;
	float GetY() const noexcept;
	bool active = true;
	int speed = 15;
	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
	bool isActive() const noexcept { return active; }
};