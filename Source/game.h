#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "player.h"
#include "projectile.h"
#include "wall.h"
#include "alien.h"
#include "background.h"
#include <vector>
#include "Resources.h"
#include <string>

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct PlayerData
{
	std::string name;
	int score = 0;
	void render(int pos) const noexcept {
		int yoffset = pos * 40;
		DrawText(name.c_str(), 50, 140 + yoffset, 40, YELLOW);
		DrawText(TextFormat("%i", score), 350, 140 + yoffset, 40, YELLOW);
	}
};

struct Game
{
	State gameState = {};
	int score;
	int wallCount = 5;

	//for Aliens shooting
	float shootTimer = 0;

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	int formationX = 100;
	int formationY = 50;

	bool newHighScore = false;

	void Start()noexcept;
	void End()noexcept;
	void Continue()noexcept;
	void Update();
	void Render()noexcept;

	void CheckForCollisions() noexcept;
	void SpawnPlayerProjectile()noexcept;
	void AlienShooting()noexcept;
	void EraseInactiveEntities()noexcept;
	void SpawnWalls()noexcept;
	void SpawnAliens()noexcept;
	bool CheckNewHighScore()noexcept;
	void InsertNewHighScore(std::string p_name)noexcept;

	Background background;
	ResourceManager resources;
	Player player;

	std::vector<Projectile> Projectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };

	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;
	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;
	int framesCounter = 0;
};