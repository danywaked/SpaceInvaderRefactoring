#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Resources.h"


class Wall
{
	static constexpr float width = 170.f;
	static constexpr float height = 76.0f;
public:
	Wall(Vector2 position) noexcept;
	Rectangle rect{0.0f,0.0f,width,height};
	int health = 50;

	bool isActive() const noexcept {
		return health > 0;
	}
	
	void Render(const Resource& texture) const noexcept;
};