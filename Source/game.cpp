#include "game.h"
#include <cassert>


void Game::Run()
{
	while (!game.ShouldClose())
	{
		Update();
		Render();
	}
}

void Game::Start()
{
	SpawnWalls();
	SpawnAliens();
	//background = Background(600);
	score = 0;
	player.lives = 3;
	gameState = State::GAMEPLAY;
}

void Game::End() noexcept
{
	PlayerProjectiles.clear();
	EnemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	gameState = State::ENDSCREEN;
}

void Game::Continue()noexcept
{
	gameState = State::STARTSCREEN;
}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}

		break;
	case State::GAMEPLAY:
		if (IsKeyReleased(KEY_Q))
		{
			return End();
		}
		player.Update();
		
		//Update Aliens and Check if they are past player
		for (auto& a : Aliens) {
			a.Update(); 
			if (a.rect.y > GetScreenHeight() - player.playerHeight)
			{
				return End();
			}
		}
		//End game if player dies
		if (player.lives < 1)
		{
			return End();
		}
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		//UPDATE PROJECTILE
		for (auto& enemyProjectiles : EnemyProjectiles) {
			enemyProjectiles.Update();
		}
		for (auto& playerProjectiles : PlayerProjectiles) {
			playerProjectiles.Update();
		}
		CheckForAlienCollisions();
		CheckForPlayerCollisions();
		if (IsKeyPressed(KEY_SPACE))
		{
			SpawnPlayerProjectile();
		}

		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > 59) //once per second
		{
			AlienShooting();
		}
		EraseInactiveEntities();

		break;
	case State::ENDSCREEN:
	
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		
		break;
	default:
		assert("Invalid Game state detected");
		break;
	}
}

void Game::Render() noexcept
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameState)
	{
	case State::STARTSCREEN:
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
		break;

	case State::GAMEPLAY:
		background.Render();
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);
		
		player.Render(resources.shipTextures[player.activeTexture]); //TODO. give resources the interface you need instead of suppresing the warning
		for(auto& enemyProjectiles : EnemyProjectiles){
			enemyProjectiles.Render(resources.laserTexture);
		}
		for(auto& playerProjectiles : PlayerProjectiles){
			playerProjectiles.Render(resources.laserTexture);
		}
		for (auto& w : Walls) {
			w.Render(resources.barrierTexture);
		}
		for (auto& a : Aliens) {
			a.Render(resources.alienTexture);
		}
		break;

	case State::ENDSCREEN:
		
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
			{
				int row = 0;
				for(const auto& entry : Leaderboard){
					entry.render(row++);
				}
			}		
		break;
	default:
		assert("Invalid Game state detected");
		break;
	}
	EndDrawing();
}

void Game::CheckForPlayerCollisions() noexcept
{
	for (auto& playerProjectile : PlayerProjectiles) {
		if (CheckForWallCollisions(playerProjectile)) {
			continue;
		}
		for (auto& alien : Aliens) {
			if (CheckCollisionRecs(playerProjectile.rect, alien.rect))
			{
				playerProjectile.active = false;
				alien.active = false;
				score += 100;
			}
		}
	}
}

bool Game::CheckForWallCollisions(Projectile& projectile) noexcept
{
	for (auto& w : Walls) {
		if (CheckCollisionRecs(w.rect, projectile.rect))
		{
			projectile.active = false;
			w.health -= 1;
			return true;
		}
	}
	return false;
}

void Game::CheckForAlienCollisions() noexcept
{
	for (auto& enemyProjectile : EnemyProjectiles) {
		if (CheckForWallCollisions(enemyProjectile)) {
			continue;
		}
		if (CheckCollisionRecs(player.rect, enemyProjectile.rect))
		{
			enemyProjectile.active = false;
			player.lives -= 1;			
		}
	}
}

void Game::SpawnPlayerProjectile()
{
	const float window_height = static_cast<float>(GetScreenHeight());
	Vector2 pos{ player.GetX() + (player.GetWidth()/2.0f),  window_height - player.GetHeight()};	
	constexpr int speed = 15;
	PlayerProjectiles.emplace_back(pos,speed);
}

const auto& getRandomEntity(const auto& collection) noexcept {
	assert(!collection.empty());
	[[gsl::suppress(type.1, "suppressing prefer gsl::narrow_cast")]]
    const auto index = GetRandomValue(0, static_cast<int>(std::size(collection)) - 1);	
    assert(index >= 0 && index < std::size(collection));
	[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
	return collection[index];
}

void Game::AlienShooting()
{
	const auto alien  = getRandomEntity(Aliens);
	//TODO
	//const auto barrel = alien.getGunPosition();

	Vector2 pos{ alien.rect.x, alien.rect.y};
	pos.y += 40;
	constexpr int speed = -15;
	EnemyProjectiles.push_back(Projectile(pos, speed));
	shootTimer = 0;
}

constexpr auto isDead = [](const auto& entity)  noexcept -> bool  {return !entity.isActive(); };

void Game::EraseInactiveEntities()noexcept{
	std::erase_if(Aliens, isDead);
	std::erase_if(Walls, isDead);
	std::erase_if(EnemyProjectiles, isDead);
	std::erase_if(PlayerProjectiles, isDead);
}

void Game::SpawnWalls() 
{
	const float window_width = GetScreenWidthF();
	const float window_height = static_cast<float>(GetScreenHeight());
	const float wall_distance = static_cast<float>(window_width / (wallCount + 1));
	constexpr float yOffset = 250.0f;
	Walls.reserve(wallCount);
	for (size_t i = 0; i < wallCount; i++){
		Vector2 pos{ wall_distance * (i + 1), window_height - yOffset };
		Walls.emplace_back(pos);
	}
}

void Game::SpawnAliens()
{
	Aliens.reserve(formationHeight * formationWidth);
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			const float x = static_cast<float>(formationX + 450.0f + (col * alienSpacing));
			const float y = static_cast<float>(formationY + (row * alienSpacing));
			const Vector2 pos = { x,y };
			Aliens.emplace_back(pos);
		}
	}
}

bool Game::CheckNewHighScore()noexcept
{	
	return (score > Leaderboard.back().score);
}

void Game::InsertNewHighScore(std::string p_name) noexcept
{
	PlayerData newData; //TODO dont twostep. add constructor
	newData.name = p_name;
	newData.score = score;

	//push new on to leaderboard
	//sort by score
	//pop_back()

	for (size_t i = 0; i < Leaderboard.size(); i++)
	{
		[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
		if (newData.score > Leaderboard[i].score)
		{
			Leaderboard.insert(Leaderboard.begin() + i, newData);
			Leaderboard.pop_back();
			i = Leaderboard.size();
		}
	}
}