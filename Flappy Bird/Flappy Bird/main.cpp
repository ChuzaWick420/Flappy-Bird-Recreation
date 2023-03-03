#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "physics.hpp"
#include "Pipe.hpp"
#include "Bird.hpp"
#include "scoreboard.hpp"

#define pipe_count 8

float d_time;

int main() {

    int death_counter = 0;

    //initially game should be paused
    bool is_paused = true;

    //player
    Bird bird;

    sf::Clock gravity_clock;
    sf::Clock fly_timer;
    sf::Clock pipe_motion;

    //creates game window
    sf::RenderWindow game_window(sf::VideoMode(1300, 700), "Flappy Bird", sf::Style::Default);

    scoreboard scores(game_window);

    //creates window's icon
    sf::Image window_icon;
    window_icon.loadFromFile("assets/imgs/Bird.png");

    game_window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());

    game_window.setPosition(sf::Vector2i(200, 10));

    //sets seed for random numbers
    std::srand(time(0));

    //passes random values
    Pipe pipe[pipe_count];

    //spacing between each pipe
    float spacing = 200;        //set it to 170 cuz dev sucks at video games :(

    for (int j = 0; j < pipe_count; j++) {

        pipe[j].set(rand(), game_window.getSize().x + ((1 + j) * (32 * pipe[0].scale)) + (j * spacing), game_window);

    }

    game_window.setFramerateLimit(60);

    //game loop
    while (game_window.isOpen()) {

        d_time = gravity_clock.getElapsedTime().asSeconds();

        //checks for events
        sf::Event event;

        //checking events triggered on window
        while (game_window.pollEvent(event))
        {
            //Close event
            if (event.type == sf::Event::Closed) {

                //save the data
                save_data(scores);

                //closes window
                game_window.close();

            }
                
        }

        //controls
        //fly        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && bird.allow == true && bird.is_dead == false) {

            bird.play_sound("jump");

            bird.is_flying = true;
            bird.vertical_velocity = 70;

            //resets falling timer
            gravity_clock.restart();
            fly_timer.restart();

            //once bird flies, it cannot fly again
            bird.allow = false;
        }

        //allows bird to fly again when space bar is released
        if (event.type == sf::Event::KeyReleased)
            bird.allow = true;

        //physics
        if (bird.is_flying == true)
            bird.fly(9.8, fly_timer.getElapsedTime().asSeconds());

        if (bird.is_dead == false && pause(is_paused) == false)
            bird.fall(9.8);

        //death
        if (bird.is_dead == true)
            death_counter++;

        if (death_counter  == 1)
            bird.play_sound("death");

        //animations
        game_window.clear(sf::Color::Blue);

            bird.render(game_window);

            for (int i = 0; i < pipe_count; i++) {

                pipe[i].render(game_window);

                if(pause(is_paused) == false && bird.is_dead == false)
                    pipe[i].update(pipe_motion);
            
                //checks for collisions
                if (is_touching(bird.bird_s, game_window, pipe[i]))
                    bird.is_dead = true;

                //respawns the pipes
                if (pipe[i].pipe_edge_s[0].getPosition().x + (32 * pipe[i].scale) < 0)
                    pipe[i].set(rand(), pipe[(pipe_count + i - 1) % pipe_count].pipe_edge_s[0].getPosition().x + spacing, game_window);      //spawns next to final pipe

                //checks for scores
                scores.scored(1, bird, pipe[i]);

            }

            scores.render(game_window);

        game_window.display();

    }

    return 0;
}