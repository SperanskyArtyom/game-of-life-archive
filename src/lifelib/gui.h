#pragma once

#include <lifelib/GameOfLife.h>

#include <SFML/Graphics.hpp>

class GUI {
public:
    GUI(unsigned, unsigned);
    GUI();
    ~GUI();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text button_text;
    sf::RectangleShape pause_button, clear_button, inc_speed_button,
            dec_speed_button, field_bound, **cells;
    const unsigned win_size_x, win_size_y;
    double delay = 0.3;
    GameOfLife* game_field;
    bool game_is_running = false;

    void check_events();

    void draw_field();
    void draw_buttons();
    void draw_button(
            sf::RectangleShape button,
            float text_coord_x,
            float text_coord_y,
            std::string button_str);

    void set_buttons();
    void set_button(sf::RectangleShape& button, float x, float y);
    void set_game_field(unsigned size_x = 20, unsigned size_y = 20);

    void update_settings();
    void update_cells();
    void update_delay();
    void update_game_status();
    void delete_game_field();

    bool rectangle_is_pressed(sf::RectangleShape rectangle);

    int get_speed();
};
