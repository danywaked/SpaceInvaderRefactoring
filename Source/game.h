#pragma once
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib.h"
#pragma warning(pop)

#include "Window.h"
#include "Resources.h"
#include "background.h"
#include "wall.h"
#include "player.h"
#include "alien.h"
#include "projectile.h"
#include <vector>
#include <string>


static float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct PlayerData
{
	PlayerData(std::string p_name, int p_score) {
		name = p_name;
		score = p_score;
	}
	std::string name;
	int score = 0;
	void render(int pos) const noexcept {
		const int yoffset = pos * 40;
		DrawText(name.c_str(), 50, 140 + yoffset, 40, YELLOW);
		DrawText(TextFormat("%i", score), 350, 140 + yoffset, 40, YELLOW);
	}
};
static constexpr int screenWidth = 1920;
static constexpr int screenHeight = 1080;
struct Game
{
	Window game{ screenWidth,screenHeight,"Space Invaders 2.0" };
	State gameState = State::STARTSCREEN;

	static constexpr int wallCount = 5;
	static constexpr int starAmount = 600;
	static constexpr int formationWidth = 8;
	static constexpr int formationHeight = 5;
	static constexpr int alienSpacing = 80;
	static constexpr int formationX = 100;
	static constexpr int formationY = 50;
	static constexpr int maxLeaderboardSize = 5;
	static constexpr  int addedScore = 100;
	static constexpr float alienShootTimerMax = 59.0f;
	bool newHighScore = false;
	int score = 0;
	float alienShootTimer = 0.0f;

	void Run();

	void Start();
	void End()noexcept;
	void Continue()noexcept;
	void Update();
	void Render();

	void UpdateGameplay();
	void RenderEntities();
	void CheckGameOverState() noexcept;
	void EraseInactiveEntities()noexcept;

	bool CheckForWallCollisions(Projectile& projectile) noexcept;
	void CheckForPlayerCollisions() noexcept;
	void CheckForAlienCollisions() noexcept;
	void SpawnPlayerProjectile(); 
	void AlienShooting();
	void SpawnWalls();
	void SpawnAliens();
	bool CheckNewHighScore()noexcept;
	void InsertNewHighScore(std::string p_name);

	Background background = Background(starAmount);
	ResourceManager resources;
	Player player{ GetScreenWidthF() / 2.0f };

	std::vector<Projectile> EnemyProjectiles;
	std::vector<Projectile> PlayerProjectiles;
	std::vector<Wall> Walls;
	std::vector<Alien> Aliens;
	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
};