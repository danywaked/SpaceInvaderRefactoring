#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include <vector>

struct Star
{
	Star(float x, float y) noexcept;
	Vector2 position = { 0, 0 };
	float size = 0;
	static constexpr Color color = SKYBLUE;
	void Render() const noexcept;
};

struct Background
{
	std::vector<Star> stars;
	Background(int starAmount);	
	void Render() const noexcept;

};