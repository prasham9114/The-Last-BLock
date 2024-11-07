#include "Game.h"

using namespace sf;
using namespace std;

// Private functions 
void Game::initVariables()
{
	this->window = nullptr;

	//Game Logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 10;
	this->endGame = false;
	this->enemySpeed = 1.f;
	this->threshold = 500;
	this->level = 1;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "The Last Block", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);

	// Load and set window icon
	if (this->icon.loadFromFile("C:/Users/Prasham Desai/Desktop/Coding/C++ Games/The-Last-Block/x64/Debug/images/logo.jpg"))
	{
		// Set the window icon
		this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
	else
	{
		cout << "Failed to load icon\n";
	}
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setOutlineThickness(1.f);
	this->enemy.setOutlineColor(Color::Red);
}

void Game::initFonts()
{
	if (!font.loadFromFile("C:/Users/Prasham Desai/Desktop/Coding/C++ Games/The-Last-Block/x64/Debug/fonts/KnightWarrior-w16n8.otf"))
	{
		cout << "Failed to load font\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setFillColor(Color::Green);
	this->uiText.setString("NONE");
	this->uiText.setPosition(5.f, 5.f);

	this->levelText.setFont(this->font);
	this->levelText.setCharacterSize(30);
	this->levelText.setFillColor(Color::Yellow);
	this->levelText.setString("NONE");
	this->levelText.setPosition(695.f, 0);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("NONE");
	this->gameOverText.setPosition(270.f, 250.f);
}

// Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::pollEvents()
{
	// Event Polling
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type)
		{

		case Event::Closed:
			this->window->close();
			break;

		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;

		default:
			break;
		}
	}
}

// Functions 
void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	if (this->endGame == false)
	{

		this->updateText();

		this->updateEnemies();

		// End Game Condition
		if (this->health <= 0)
			this->endGame = true;
	}
}

void Game::render()
{
	/*
		@return void

		- clear old frames
		- render obejcts
		- display frame in window

		Renders Game Object
	*/
	this->window->clear();

	if (this->endGame == true)
	{
		this->renderGameOverText(*this->window);
	}
	else
	{
		// Draw Game Object
		this->renderEnemies(*this->window);

		this->renderText(*this->window);
	}

	this->window->display();
}

void Game::updateMousePositions()
{
	/**
		@ return void
		Updates the mouse positions:
		- Updates mouse position relative to the window(vector 2i)
	**/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::spawnEnemy()
{
	/**
		@return void

		Spawns enemies and sets their types , colors and positions randomly.
		- Sets a random type
		- Sets a random position
		- Sets a random color
		- Adds enemy to the vector

	**/

	// Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setFillColor(Color::Magenta);
		this->enemy.setSize(Vector2f(20.f, 20.f));
		break;
	case 1:
		this->enemy.setFillColor(Color::Yellow);
		this->enemy.setSize(Vector2f(35.f, 35.f));
		break;
	case 2:
		this->enemy.setFillColor(Color::Blue);
		this->enemy.setSize(Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(Color::Cyan);
		this->enemy.setSize(Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy.setFillColor(Color(255, 165, 0));
		this->enemy.setSize(Vector2f(100.f, 100.f));
		break;
	default:
		this->enemy.setFillColor(Color::Yellow);
		this->enemy.setSize(Vector2f(100.f, 100.f));
		break;
	}
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0);

	// Spawn Enemy
	this->enemies.push_back(this->enemy);
}

void Game::renderEnemies(RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::updateEnemies()
{
	/**
		@ return void

		Updates the enemy spawn timer and spawns enemies
		when total amount of enemie is less than max resets
		the timer when reached max.
		- Moves the enemy down
		- Removes Enemy at the edge of the screen //TODO

	**/

	//Updating the timer  for spawn enemy
	if (this->enemies.size() < this->maxEnemies)
	{
		// Resetting the time whem max timer reached 
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1;
	}


	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		// Move the enemies
		this->enemies[i].move(0.f, enemySpeed);

		if (this->points >= this->threshold)
		{
			this->threshold += 500;
			this->enemySpeed += 0.5f;
			this->level += 1;
		}

		// Delete the enemies when below the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			cout << "Health: " << this->health << "\n";
		}
	}

	// Delete the enemies on click
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			bool deleted = false;

			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{

				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{

					// Gain Points 
					if (this->enemies[i].getFillColor() == Color::Magenta)
						this->points += 10;

					else if (this->enemies[i].getFillColor() == Color::Yellow)
						this->points += 7;

					else if (this->enemies[i].getFillColor() == Color::Blue)
						this->points += 5;

					else if (this->enemies[i].getFillColor() == Color::Cyan)
						this->points += 3;

					else if (this->enemies[i].getFillColor() == Color::Green)
						this->points += 1;

					else
						this->points += 0;

					cout << "Points: " << this->points << "\n";

					//Delete the enemy when clicked
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}

	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderText(RenderTarget& target)
{
	if (this->endGame == false)
	{
		target.draw(this->uiText);
		target.draw(this->levelText);
	}
}

void Game::updateText()
{
	stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health;
	this->uiText.setString(ss.str());

	stringstream ss1;
	ss1 << "Level: " << this->level;
	this->levelText.setString(ss1.str());

	stringstream ss2;
	ss2 << "GAME OVER";
	this->gameOverText.setString(ss2.str());
}

void Game::renderGameOverText(RenderTarget& target)
{
	target.draw(this->gameOverText);
}
