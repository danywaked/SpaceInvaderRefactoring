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
	Alien(Vector2 position) noexcept;
	Rectangle rect{};
	float offset = 50;
	float alienWidth = 100;
	float alienHeight = 100;
	bool active = true;
	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
};