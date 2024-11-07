#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

/*
	Class that acts as the game engine
	Wrapper Class
*/

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game
{
private:

	// private variables 
	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Image icon;

	// Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Mouse Positions 
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources 
	sf::Font font;

	// Text
	sf::Text uiText;
	sf::Text levelText;
	sf::Text gameOverText;

	// Game Logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	float enemySpeed;
	float threshold;
	int level;

	// Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();

public:

	// Constructors and Destructors
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	// Functions
	void pollEvents();
	void update();
	void render();
	void updateMousePositions();
	void spawnEnemy();
	void renderEnemies(sf::RenderTarget& target);
	void updateEnemies();
	void renderText(sf::RenderTarget& target);
	void updateText();
	void renderGameOverText(sf::RenderTarget& target);
};
