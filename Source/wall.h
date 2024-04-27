#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "raylib.h"
#include "Resources.h"


class Wall
{
public:
	Wall(Vector2 position) noexcept;
	Rectangle rect{};
	float GetX() const noexcept;
	float GetY() const noexcept;
	float GetWidth() const noexcept;
	float GetHeight() const noexcept;
	int health = 50;

	bool active() const noexcept {
		return health > 0;
	}
	
	void Render(const Resource& texture) const noexcept;
};