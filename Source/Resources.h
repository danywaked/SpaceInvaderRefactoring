#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include <vector>
#include <stdexcept>
#include <string_view>
#include <format>
#include <unordered_map>

using namespace std::literals::string_view_literals;
struct Resource 
{
	Texture2D texture;
	explicit Resource(std::string_view path) {
		texture = LoadTexture(path.data());
		if (texture.id <= 0) {
			throw std::runtime_error(std::format("Unable to load texture: {}"sv, path));
		}
	}
	~Resource() {
		UnloadTexture(texture);	
	}
	Resource(const Resource & other) noexcept = delete;
	Resource& operator=(const Resource & other) noexcept = delete;
	Resource(Resource && other) noexcept{
		std::swap(other.texture, texture);
	}
	Resource& operator=(Resource&& other) noexcept{
		std::swap(other.texture, texture);
		return *this;
	}
};

struct ResourceManager
{
	std::unordered_map<std::string_view, Resource*> texturesList;

	std::vector<Resource> shipTextures;
	Resource alienTexture{ "./Assets/Alien.png"sv };
	Resource barrierTexture{ "./Assets/Barrier.png"sv };
	Resource laserTexture{ "./Assets/Laser.png"sv };

	[[gsl::suppress(f.6, "suppressing prefers noexcept")]]
	ResourceManager() {
		shipTextures.emplace_back("./Assets/Ship1.png"sv);
		shipTextures.emplace_back("./Assets/Ship2.png"sv);
		shipTextures.emplace_back("./Assets/Ship3.png"sv);
	}

	const Resource& GetShipTexture(int index) const {
		if (index >= shipTextures.size())
		{
			throw std::runtime_error(std::format("The texture index: {} for Ship Texture is out of range"sv, index));
		}
		[[gsl::suppress(bounds.4, "prefers gsl::at()")]]
		return shipTextures[index];
	}
};