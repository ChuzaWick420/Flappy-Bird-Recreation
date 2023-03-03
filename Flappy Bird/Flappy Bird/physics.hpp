#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Pipe.hpp"
#include "scoreboard.hpp"

bool is_touching(sf::Sprite& player, sf::RenderWindow& t_window, Pipe& t_pipe) {

	bool check = false;

	//vertical size of object
	float player_height = player.getTexture()->getSize().y * player.getScale().y;
	float player_width = player.getTexture()->getSize().x * player.getScale().x;

	//ground
	if (t_window.getSize().y <= player.getPosition().y + player_height) 
		check = true;

	//pipe
	//horizontally, player is inside the pipe
	if (player.getPosition().x + player_width >= t_pipe.pipe_edge_s[t_pipe.down].getPosition().x 
	&& (player.getPosition().x				  <= t_pipe.pipe_edge_s[t_pipe.down].getPosition().x + (32 * t_pipe.pipe_edge_s[t_pipe.down].getScale().x))) {

		//but vertically, player is NOT inside the pipe
		if (!((player.getPosition().y			  >= (t_pipe.pipe_edge_s[t_pipe.up].getPosition().y)) 
		&& (player.getPosition().y + player_width <= t_pipe.pipe_edge_s[t_pipe.down].getPosition().y))) {

			check = true;

		}
	}


	return check;
}

bool pause(bool& trigger) {

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		trigger = true;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		trigger = false;

	return trigger;
}

void save_data(scoreboard& score) {

	if (std::stoi(score.t_scores) > std::stoi(score.t_highscores)) {

		score.score_file.open("assets/scores.txt", std::ios::out);
		score.score_file << score.t_scores;
		score.score_file.close();

	}

}