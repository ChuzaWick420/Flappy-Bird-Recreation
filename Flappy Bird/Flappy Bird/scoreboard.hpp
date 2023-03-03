#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "Pipe.hpp"
#include "Bird.hpp"

class scoreboard {

public:

	std::string t_scores = "0", t_highscores;
	sf::Text score, highscore;
	sf::Font game_font;

	//file where scores are stored
	std::fstream score_file;

	//default constructor
	scoreboard(sf::RenderWindow& t_window);

	void render(sf::RenderWindow& t_window);
	void scored(int value, Bird& player, Pipe& t_pipe);

};

scoreboard::scoreboard(sf::RenderWindow& t_window) {

	game_font.loadFromFile("assets/font/RobotoMono-Bold.ttf");

	//open file in read/input mode
	this->score_file.open("assets/scores.txt", std::ios::in);

	//reads and store into variable t_highscores
	this->score_file >> t_highscores;
	this->score_file.close();

	this->highscore.setString("Highscores: " + this->t_highscores);
	this->highscore.setFillColor(sf::Color::Red);
	this->highscore.setFont(this->game_font);

	this->score.setString("Scores: 0");
	this->score.setFillColor(sf::Color::Green);
	this->score.setFont(this->game_font);
	this->score.setPosition((t_window.getSize().x / 2) - 50, 0);
}

void scoreboard::render(sf::RenderWindow& t_window) {

	t_window.draw(this->score);
	t_window.draw(this->highscore);

}

void scoreboard::scored(int value, Bird& player, Pipe& t_pipe) {

	if (player.is_dead == false)
	if (player.bird_s.getPosition().x >= t_pipe.pipe_edge_s[t_pipe.down].getPosition().x + (32 * t_pipe.scale) - 1
	 && player.bird_s.getPosition().x <= t_pipe.pipe_edge_s[t_pipe.down].getPosition().x + (32 * t_pipe.scale) + 3) {

		//string to int conversion
		int total = std::stoi(this->t_scores);

		//add the argument value to the (string -> int) value, convert back to string and overwrite the Text
		this->t_scores = std::to_string(total + value);

		//and set the highscore sprite
		this->score.setString("Scores: " + this->t_scores);

		player.play_sound("score");

	}

}