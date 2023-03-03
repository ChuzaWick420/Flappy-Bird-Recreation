#include <iostream>
#include "Pipe.hpp"

void Pipe::set(int type, float offset, sf::RenderWindow& t_window) {

	//loads 3 pieces of pipe
	this->pipe_edge_t.loadFromFile("assets/imgs/Pipe_top.png");
	this->pipe_mid_t.loadFromFile("assets/imgs/Pipe_mid.png");
	this->pipe_end_t.loadFromFile("assets/imgs/Pipe_bottom.png");

	//only texture which flexes is the mid part of pipe
	this->pipe_mid_t.setRepeated(true);

	//scale
	this->pipe_edge_s[down].setScale(sf::Vector2f(scale, scale));
	this->pipe_edge_s[up].setScale(sf::Vector2f(scale, scale));
	this->pipe_mid_s[down].setScale(sf::Vector2f(scale, scale));
	this->pipe_mid_s[up].setScale(sf::Vector2f(scale, scale));
	this->pipe_end_s[down].setScale(sf::Vector2f(scale, scale));
	this->pipe_end_s[up].setScale(sf::Vector2f(scale, scale));

	//sets up lower pipe limit
	this->pipe_edge_s[down].setTexture(pipe_edge_t);
	this->pipe_end_s[down].setTexture(pipe_end_t);
	this->pipe_mid_s[down].setTexture(pipe_mid_t);

	this->pipe_mid_s[down].setTextureRect(
		//texture box starting from 0, 0 location
		sf::IntRect(0, 0,
			//width same as object size in pixels
			pipe_mid_t.getSize().x,
			//height depending on the type index
			((type % (difficulty)) * pipe_mid_t.getSize().y)
			));
	this->pipe_mid_s[down].setPosition(sf::Vector2f(offset, this->pipe_edge_s[down].getScale().y * pipe_edge_t.getSize().y));

	this->pipe_end_s[down].setPosition(sf::Vector2f(offset, (this->pipe_mid_s[down].getPosition().y + ((type % (difficulty)) * pipe_mid_t.getSize().y) * scale)));

	//moves the whole pillar till it touches floor

	float edge_height[2], mid_height[2], end_height[2];

	//getting height
	edge_height[down] = scale * this->pipe_edge_t.getSize().y;
	mid_height[down] = (type % (difficulty)) * pipe_mid_t.getSize().y * scale;
	end_height[down] = scale * this->pipe_end_t.getSize().y;

	//setting position
	this->pipe_end_s[down].setPosition(sf::Vector2f(offset, t_window.getSize().y - edge_height[down]));
	this->pipe_mid_s[down].setPosition(sf::Vector2f(offset, pipe_end_s[down].getPosition().y - mid_height[down]));
	this->pipe_edge_s[down].setPosition(sf::Vector2f(offset, pipe_mid_s[down].getPosition().y - edge_height[down]));

	//upper pillar
	//setting up sprites
	this->pipe_end_s[up] = this->pipe_end_s[down];
	this->pipe_edge_s[up] = this->pipe_edge_s[down];
	this->pipe_mid_s[up].setTexture(pipe_mid_t);

	this->pipe_mid_s[up].setTextureRect(sf::IntRect(0, 0, 
		//width same as object size in pixels
		pipe_mid_t.getSize().x,
		//height depending on the type index
		(difficulty - (type % (difficulty))) * pipe_mid_t.getSize().y)
	);

	//now rotate 180 degrees
	this->pipe_end_s[up].setRotation(180);
	this->pipe_edge_s[up].setRotation(180);
	this->pipe_mid_s[up].setRotation(180);

	//getting size
	end_height[up] = scale * pipe_end_t.getSize().y;
	mid_height[up] = (difficulty - (type % (difficulty))) * scale * pipe_mid_t.getSize().y;
	edge_height[up] = scale * pipe_edge_t.getSize().y;

	//setting position
	this->pipe_end_s[up].setPosition(sf::Vector2f((pipe_end_t.getSize().x * scale) + offset, end_height[up]));
	this->pipe_mid_s[up].setPosition(sf::Vector2f(this->pipe_end_s[up].getPosition().x, mid_height[up] + end_height[up]));
	this->pipe_edge_s[up].setPosition(sf::Vector2f(this->pipe_end_s[up].getPosition().x, edge_height[up] + mid_height[up]));

}

void Pipe::render(sf::RenderWindow& t_window) {

	//upper pillar
	t_window.draw(this->pipe_end_s[up]);
	t_window.draw(this->pipe_mid_s[up]);
	t_window.draw(this->pipe_edge_s[up]);

	//lower pillar
	t_window.draw(this->pipe_edge_s[down]);
	t_window.draw(this->pipe_mid_s[down]);
	t_window.draw(this->pipe_end_s[down]);

}

void Pipe::update(sf::Clock timer) {

	//updates at 1 pixel per 50 milliseconds
	if (timer.getElapsedTime().asMilliseconds() >= 200) {

		this->pipe_edge_s[down].move(-4, 0);
		this->pipe_edge_s[up].move(-4, 0);

		this->pipe_mid_s[down].move(-4, 0);
		this->pipe_mid_s[up].move(-4, 0);

		this->pipe_end_s[down].move(-4, 0);
		this->pipe_end_s[up].move(-4, 0);

		//once updated, reset the timer
		timer.restart();

	}

}