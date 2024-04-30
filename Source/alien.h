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
	bool moveRight = true;

public:
	Alien(Vector2 position) noexcept;	
	static constexpr float alienWidth = 100.0f;
	static constexpr float alienHeight = 100.0f;
	Rectangle rect{0.0f, 0.0f, alienWidth, alienHeight};
	bool active = true;
	void Update() noexcept;
	void Render(const Resource& texture) const noexcept;
	bool isActive() const noexcept { return active; }
};