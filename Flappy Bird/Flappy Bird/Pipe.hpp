#pragma once
#include <SFML/Graphics.hpp>

class Pipe{

public:

	enum Location{

		up = 0, down

	};

	sf::Texture pipe_edge_t;
	sf::Texture pipe_mid_t;
	sf::Texture pipe_end_t;

	//2 because 1 pipe is up and 1 is down
	sf::Sprite pipe_edge_s[2];
	sf::Sprite pipe_mid_s[2];
	sf::Sprite pipe_end_s[2];

	float scale = 3;
	int difficulty = 3;

	//default constructor
	Pipe(){};

	//overloaded constructor
	void set(int type, float offset, sf::RenderWindow& t_window);
	void update(sf::Clock timer);
	void render(sf::RenderWindow& t_window);

};