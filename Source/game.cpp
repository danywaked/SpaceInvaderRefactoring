#include "game.h"
#include <cassert>
#include <algorithm> 

void Game::Run(){
	while (!game.ShouldClose())
	{
		Update();
		Render();
	}
}

void Game::Start(){
	SpawnWalls();
	SpawnAliens();
	score = 0;
	player.lives = 3;
	gameState = State::GAMEPLAY;
}

void Game::End() noexcept{
	PlayerProjectiles.clear();
	EnemyProjectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue() noexcept{
	gameState = State::STARTSCREEN;
}

void Game::Update(){
	switch (gameState)
	{
	case State::STARTSCREEN:
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}

		break;
	case State::GAMEPLAY:

		CheckGameOverState();

		if (Aliens.empty()) {
			SpawnAliens();
		}
		UpdateGameplay();
		EraseInactiveEntities();

		break;
	case State::ENDSCREEN:
	
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}
		if (newHighScore)
		{
			InsertNewHighScore("New");
			newHighScore = false;
		}
		break;
	default:
		assert("Invalid Game state detected");
		break;
	}
}

void Game::Render(){
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
		RenderEntities();
		
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

void Game::UpdateGameplay(){
	for (auto& a : Aliens) {
		a.Update();
	}
	player.Update();

	for (auto& enemyProjectiles : EnemyProjectiles) {
		enemyProjectiles.Update();
	}
	for (auto& playerProjectiles : PlayerProjectiles) {
		playerProjectiles.Update();
	}
	if (IsKeyPressed(KEY_SPACE)) {
		SpawnPlayerProjectile();
	}
	AlienShooting();
	CheckForPlayerCollisions();
	CheckForAlienCollisions();
}

void Game::RenderEntities(){
	player.Render(resources.GetShipTexture(player.activeTexture));
	for (auto& enemyProjectiles : EnemyProjectiles) {
		enemyProjectiles.Render(resources.laserTexture);
	}
	for (auto& playerProjectiles : PlayerProjectiles) {
		playerProjectiles.Render(resources.laserTexture);
	}
	for (auto& w : Walls) {
		w.Render(resources.barrierTexture);
	}
	for (auto& a : Aliens) {
		a.Render(resources.alienTexture);
	}
}

void Game::CheckGameOverState() noexcept{
	for (auto& a : Aliens) {
		if (IsKeyReleased(KEY_Q) || player.lives < 1 || a.GetHeight() > GetScreenHeight() - player.GetHeight())
		{
			return End();
		}
	}
}

void Game::CheckForPlayerCollisions() noexcept{
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

bool Game::CheckForWallCollisions(Projectile& projectile) noexcept{
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

void Game::CheckForAlienCollisions() noexcept{
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

void Game::SpawnPlayerProjectile(){
	const float window_height = static_cast<float>(GetScreenHeight());
	Vector2 pos{ player.GetX() + (player.GetWidth()/2.0f),  window_height - player.GetHeight()};	
	constexpr int speed = 15;
	PlayerProjectiles.emplace_back(pos,speed);
}

const auto& GetRandomEntity(const auto& collection) noexcept{
	assert(!collection.empty());
	[[gsl::suppress(type.1, "suppressing prefer gsl::narrow_cast")]]
    const auto index = GetRandomValue(0, static_cast<int>(std::size(collection)) - 1);	
    assert(index >= 0 && index < std::size(collection));
	[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
	return collection[index];
}

void Game::AlienShooting(){
	shootTimer += 1;
	if (shootTimer > 59)
	{
		const auto alien = GetRandomEntity(Aliens);
		const auto barrel = alien.GetGunPosition();
		constexpr int speed = -15;
		EnemyProjectiles.push_back(Projectile(barrel, speed));
		shootTimer = 0;
	}
}

constexpr auto isDead = [](const auto& entity)  noexcept -> bool  {return !entity.isActive(); };

void Game::EraseInactiveEntities() noexcept{
	std::erase_if(Aliens, isDead);
	std::erase_if(Walls, isDead);
	std::erase_if(EnemyProjectiles, isDead);
	std::erase_if(PlayerProjectiles, isDead);
}

void Game::SpawnWalls(){
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

void Game::SpawnAliens(){
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

bool Game::CheckNewHighScore() noexcept{	
	return (score > Leaderboard.back().score);
}

void Game::InsertNewHighScore(std::string p_name){
	Leaderboard.push_back(PlayerData(p_name,score));
	std::sort(Leaderboard.begin(), Leaderboard.end(), [](const PlayerData& a, const PlayerData& b) {return a.score > b.score; });
	
	if (Leaderboard.size() > maxLeaderboardSize)
	{
		Leaderboard.pop_back();
	}
}