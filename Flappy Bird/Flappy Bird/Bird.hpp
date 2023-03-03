#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bird{

public:

	sf::Texture bird_t;
	sf::Sprite bird_s;

	bool allow = true;
	bool is_touching = false;
	bool is_flying = false;
	bool is_dead = false;

	float vertical_velocity;

	//default constructor
	Bird();

	//graphics
	void render(sf::RenderWindow& target_window);

	void fall(float g_factor);
	void fly(float g_factor, float up_time);

	//audio
	sf::SoundBuffer sb_jump, sb_score, sb_death;
	sf::Sound jump_sfx, score_sfx, death_sfx;

	void play_sound(std::string state);
};