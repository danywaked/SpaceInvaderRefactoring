#include "game.h"

// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B)noexcept //Uses pythagoras to calculate the length of a line
{
	const float length = sqrtf(pow(B.x - A.x, 2.0f) + pow(B.y - A.y, 2.0f));
	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) noexcept // Uses pythagoras to calculate if a point is within a circle or not
{
	const float distanceToCentre = lineLength(circlePos, point);
	if (distanceToCentre < radius)
	{
		return true;
	}
	return false;
}

void Game::Run()
{
	while (!game.ShouldClose())
	{
		Update();
		Render();
	}
}

void Game::Start()noexcept
{
	SpawnWalls();
	
	//creating player
	[[gsl::suppress(con.4)]]
	Player newPlayer;
	player = newPlayer;

	SpawnAliens();
	
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	score = 0;
	gameState = State::GAMEPLAY;
}

void Game::End() noexcept
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
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
			End();
		}
		player.Update();
		
		//Update Aliens and Check if they are past player
	for (auto& a : Aliens) {
		a.Update(); 
		if (a.position.y > GetScreenHeight() - player.player_base_height)
		{
			End();
		}
	}
		//End game if player dies
		if (player.lives < 1)
		{
			End();
		}
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		// Update background with offset
		playerPos = { player.x_pos, player.player_base_height };
		cornerPos = { 0.0f, player.player_base_height };
		offset = lineLength(playerPos, cornerPos) * -1;
		background.Update(offset / 15.0f);

		//UPDATE PROJECTILE
		for (auto& p : Projectiles) {
			p.Update();
		}
		//UPDATE WALLS
		for (auto& w : Walls) {
			w.Update();
		}
		CheckForCollisions();
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
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed on the queue
				int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						[[gsl::suppress(bounds.2)]] [[gsl::suppress(bounds.4)]] [[gsl::suppress(type.1)]]
						name[letterCount] = static_cast<char>(key);
						[[gsl::suppress(bounds.2)]] [[gsl::suppress(bounds.4)]]
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}

				//Remove chars 
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					{ [[gsl::suppress(bounds.2)]] [[gsl::suppress(bounds.4)]]
						name[letterCount] = '\0';
					}
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
			// name + score to scoreboard
			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				[[gsl::suppress(bounds.3)]] 
				std::string nameEntry(name);

				InsertNewHighScore(nameEntry);

				newHighScore = false;
			}
		}
		break;
	default:
		//SHOULD NOT HAPPEN
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
		//Code
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
		break;

	case State::GAMEPLAY:
		background.Render();
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);
		[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
		player.Render(resources.shipTextures[player.activeTexture]);
		for(auto& p : Projectiles){
				p.Render(resources.laserTexture);
		}
		for (auto& w : Walls) {
			w.Render(resources.barrierTexture);
		}
		for (auto& a : Aliens) {
			a.Render(resources.alienTexture);
		}
		break;

	case State::ENDSCREEN:
		if (newHighScore)
		{
			DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
			DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText)
			{
				// HOVER CONFIRMIATION
				DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);
			}
			else
			{
				DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), DARKGRAY);
			}

			//Draw the name being typed out
			[[gsl::suppress(bounds.3)]]
			DrawText(name, static_cast<int>(textBox.x) + 5, static_cast<int>(textBox.y) + 8, 40, MAROON);
			//Draw the text explaining how many characters are used
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						[[gsl::suppress(bounds.3)]]
						DrawText("_", static_cast<int>(textBox.x) + 8 + MeasureText(name, 40), static_cast<int>(textBox.y) + 12, 40, MAROON);
					}
				}
				else
				{
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}				
			}
			// Explain how to continue when name is input
			if (letterCount > 0 && letterCount < 9)
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}
		}
		else 
		{
			// If no highscore or name is entered, show scoreboard and call it a day
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			int row = 0;
			for(const auto& entry : Leaderboard){
				entry.render(row++);
			}
		}
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
	EndDrawing();
}

void Game::CheckForCollisions() noexcept
{
	for (auto& p : Projectiles) {
		if (!p.enemyBullet)
		{
			for (auto& a : Aliens) {
				//if (CheckCollision(a.position, a.radius, p.lineStart, p.lineEnd))
				if(CheckCollisionRecs(p.rect,a.rect))
				{
					// Set them as inactive, will be killed later
					p.active = false;
					a.active = false;
					score += 100;
				}
			}
		}
		else //ENEMY PROJECTILES HERE
		{
			//if (CheckCollision({ player.x_pos, GetScreenHeight() - player.player_base_height }, player.radius, p.lineStart, p.lineEnd))
			if(CheckCollisionRecs(player.rect,p.rect))
			{
				p.active = false;
				player.lives -= 1;
			}
		}
		for (auto& w : Walls) {
			//if (CheckCollision(w.position, w.radius, p.lineStart, p.lineEnd))
			if(CheckCollisionRecs(w.rect,p.rect))
			{
				// Set them as inactive, will be killed later
				p.active = false;
				w.health -= 1;
			}
		}
	}
}

void Game::SpawnPlayerProjectile()noexcept
{
	const float window_height = static_cast<float>(GetScreenHeight());
	Projectile newProjectile;
	newProjectile.position.x = player.x_pos;
	newProjectile.position.y = window_height - 130;
	newProjectile.enemyBullet = false;
	Projectiles.push_back(newProjectile);
}

void Game::AlienShooting()noexcept
{
	int randomAlienIndex = 0;
	if (Aliens.size() > 1)
	{
		randomAlienIndex = rand() % Aliens.size();
	}

	Projectile newProjectile;
	[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
	newProjectile.position = Aliens[randomAlienIndex].position;
	newProjectile.position.y += 40;
	newProjectile.speed = -15;
	newProjectile.enemyBullet = true;
	Projectiles.push_back(newProjectile);
	shootTimer = 0;
}

void Game::EraseInactiveEntities()noexcept
{
	std::erase_if(Aliens, [](const auto& alien) {return !alien.active; });
	std::erase_if(Walls, [](const auto& wall) {return !wall.active(); });
	std::erase_if(Projectiles, [](const auto& projectile) {return !projectile.active; });
}

void Game::SpawnWalls() noexcept
{
	const float window_width = static_cast<float>(GetScreenWidth());
	const float window_height = static_cast<float>(GetScreenHeight());
	const float wall_distance = static_cast<float>(window_width / (wallCount + 1));
	for (size_t i = 0; i < wallCount; i++)
	{
		Wall newWalls;
		newWalls.SetPosition(wall_distance * (i + 1), window_height - 250);
		Walls.push_back(newWalls);
	}
}

void Game::SpawnAliens()noexcept
{
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			Alien newAlien = Alien();
			newAlien.active = true;
			newAlien.position.x = static_cast<float>(formationX + 450.0f + (col * alienSpacing));
			newAlien.position.y = static_cast<float>(formationY + (row * alienSpacing));
			Aliens.push_back(newAlien);
		}
	}
}

bool Game::CheckNewHighScore()noexcept
{
	[[gsl::suppress(bounds.4, "suppressing prefer.at()")]]
	if (score > Leaderboard[4].score)
	{
		return true;
	}
	return false;
}

void Game::InsertNewHighScore(std::string p_name) noexcept
{
	PlayerData newData; //TODO dont twostep
	newData.name = p_name;
	newData.score = score;

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