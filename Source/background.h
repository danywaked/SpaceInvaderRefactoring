#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "raylib.h"
#include <vector>

struct Star
{
	Star(Vector2 position);
	Vector2 initPosition = { 0, 0 };
	Vector2 position = { 0, 0 };
	Color color = GRAY;
	float size = 0;
	void Update(float starOffset)noexcept;
	void Render()noexcept;
};

struct Background
{
	std::vector<Star> Stars;

	void Initialize(int starAmount) noexcept;
	void Update(float offset)noexcept;
	void Render()noexcept;

};