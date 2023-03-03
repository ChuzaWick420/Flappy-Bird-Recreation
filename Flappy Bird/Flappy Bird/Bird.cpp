#include "Bird.hpp"
#include <iostream>

extern float d_time;

//default constructor
Bird::Bird() {

	//loads texture
	this->bird_t.loadFromFile("assets/imgs/Bird.png");
	//sets texture
	this->bird_s.setTexture(this->bird_t);

	//lowers to scale from 409x289 to 32x32
	this->bird_s.setScale(sf::Vector2f((float)32/409, (float)32/289));

	//default position
	this->bird_s.setPosition(50, 300);

	//associates sound files
	sb_jump.loadFromFile("assets/sounds/fly.wav");

	jump_sfx.setBuffer(sb_jump);

	sb_score.loadFromFile("assets/sounds/score.wav");

	score_sfx.setBuffer(sb_score);

	sb_death.loadFromFile("assets/sounds/death.wav");

	death_sfx.setBuffer(sb_death);
}

void Bird::render(sf::RenderWindow& target_window) {
	
	target_window.draw(this->bird_s);
}

void Bird::fall(float g_factor) {

	//applies gravity
	this->bird_s.move(0, (10 * d_time) + (g_factor * 0.5 * d_time * d_time));
	
}

void Bird::fly(float g_factor, float up_time) {

	if (this->vertical_velocity > 0) {

		this->vertical_velocity = this->vertical_velocity + (-g_factor * 3 * up_time);

		this->bird_s.move(0, -vertical_velocity * up_time);

		//debug
		//std::cout << "Height: " << 700 - this->bird_s.getPosition().y << std::endl;
		//std::cout << "Velocity: " << this->vertical_velocity << std::endl;

	}

	else
		this->is_flying = false;

}

void Bird::play_sound(std::string state) {

	if (state == "jump") {

		jump_sfx.play();

	}

	if (state == "score") {

		score_sfx.play();

	}

	if (state == "death") {

		death_sfx.play();

	}
}