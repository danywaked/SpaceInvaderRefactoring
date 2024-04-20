#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "raylib.h"
#include "Resources.h"

class Alien
{
	int speed = 2;
	bool moveRight = true;

public:
	Vector2 position = { 0, 0 };
	Rectangle rect{};
	bool active = true;
	float radius = 30;

	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
};