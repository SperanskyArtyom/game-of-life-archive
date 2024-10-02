#include <lifelib/gui.h>

#include <ctime>

using namespace sf;

#define MAX_DELAY 1.0
#define MIN_DELAY 0.1
#define D_DELAY 0.1

GUI::GUI(unsigned x, unsigned y) : win_size_x{x}, win_size_y{y}
{
    window.create(VideoMode(win_size_x, win_size_y), "Game of Life");
    set_game_field();
    set_buttons();
}

GUI::GUI() : GUI(1000, 700)
{
}
GUI::~GUI()
{
    delete_game_field();
}

void GUI::run()
{
    Clock clock;
    float timer = 0;

    while (window.isOpen()) {
        check_events();

        if (game_is_running) {
            timer += clock.getElapsedTime().asSeconds();
            clock.restart();
            if (timer >= delay) {
                game_field->move_to_next_generation();
                timer = 0;
            }
        }

        window.clear(Color::White);
        draw_field();
        draw_buttons();
        window.display();
    }
}

void GUI::check_events()
{
    Event event;
    while (window.pollEvent(event)) {
        static bool lock_click;
        if ((event.type == Event::Closed)
            || ((Keyboard::isKeyPressed(Keyboard::LControl))
                && (Keyboard::isKeyPressed(Keyboard::Q))))
            window.close();
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.mouseButton.button == sf::Mouse::Left && !lock_click) {
                lock_click = true;
                update_settings();
            }
        if (event.type == sf::Event::MouseButtonReleased)
            if (event.mouseButton.button == sf::Mouse::Left)
                lock_click = false;
    }
}

void GUI::set_game_field(unsigned x, unsigned y)
{
    game_field = new GameOfLife(x, y);
    const float field_margin = 40, cell_width = 30;
    field_bound = RectangleShape(
            {(float)(cell_width * x), (float)(cell_width * y)});
    field_bound.setPosition(field_margin, field_margin);
    field_bound.setOutlineThickness(2);
    field_bound.setOutlineColor(Color::Black);

    cells = new RectangleShape*[y];
    for (unsigned i = 0; i < y; i++) {
        cells[i] = new RectangleShape[x];
        for (unsigned j = 0; j < x; j++) {
            cells[i][j] = RectangleShape({cell_width, cell_width});
            cells[i][j].setOutlineColor(Color::Black);
            cells[i][j].setOutlineThickness(1);
            cells[i][j].setPosition(
                    field_margin + cell_width * j,
                    field_margin + cell_width * i);
        }
    }
}

void GUI::set_buttons()
{
    font.loadFromFile("src/fonts/futurabookc.ttf");
    button_text.setFont(font);
    button_text.setCharacterSize(36);
    button_text.setFillColor(Color::Black);
    const float button_width = 200, button_height = 50, button_margin = 100,
                dy = 70;

    clear_button = pause_button = RectangleShape({button_width, button_height});
    inc_speed_button = dec_speed_button
            = RectangleShape({button_width / 4, button_height});

    set_button(
            pause_button,
            win_size_x - (button_margin + button_width),
            button_margin);
    set_button(
            clear_button,
            win_size_x - (button_margin + button_width),
            button_margin + dy);
    set_button(
            dec_speed_button,
            win_size_x - (button_margin + button_width * 3 / 4 + 10),
            button_margin + 2 * dy);
    set_button(
            inc_speed_button,
            win_size_x - (button_margin + button_width / 2 - 10),
            button_margin + 2 * dy);
}

void GUI::set_button(RectangleShape& button, float x, float y)
{
    button.setPosition(x, y);
    button.setOutlineThickness(2);
    button.setOutlineColor(Color::Black);
}

void GUI::draw_field()
{
    unsigned field_size_x = game_field->get_size_x();
    unsigned field_size_y = game_field->get_size_y();
    window.draw(field_bound);

    for (unsigned y = 0; y < field_size_y; y++) {
        for (unsigned x = 0; x < field_size_x; x++) {
            if (game_field->get_cell_status(x, y))
                cells[y][x].setFillColor(Color::Green);
            else
                cells[y][x].setFillColor(Color::White);
            window.draw(cells[y][x]);
        }
    }
}

void GUI::draw_buttons()
{
    if (game_is_running) {
        draw_button(pause_button, win_size_x - 240, 100, "Pause");
    } else {
        draw_button(pause_button, win_size_x - 235, 100, "Start");
    }

    draw_button(clear_button, win_size_x - 240, 170, "Clear");
    draw_button(dec_speed_button, win_size_x - 239, 237, "-");
    draw_button(inc_speed_button, win_size_x - 173, 241, "+");

    button_text.setPosition(win_size_x - 275, 290);
    button_text.setString("Speed: " + std::to_string(get_speed()) + "%");
    window.draw(button_text);
}

void GUI::draw_button(
        RectangleShape button,
        float text_coord_x,
        float text_coord_y,
        std::string button_str)
{
    button_text.setPosition(text_coord_x, text_coord_y);
    button_text.setString(button_str);
    window.draw(button);
    window.draw(button_text);
}

void GUI::delete_game_field()
{
    for (unsigned i = 0; i < game_field->get_size_y(); i++)
        delete[] cells[i];
    delete cells;
    delete game_field;
}

void GUI::update_settings()
{
    update_game_status();
    if (!game_is_running) {
        update_cells();
        if (rectangle_is_pressed(clear_button)) {
            delete game_field;
            game_field = new GameOfLife(20, 20);
        }
    }
    update_delay();
}

void GUI::update_cells()
{
    for (unsigned y = 0; y < game_field->get_size_y(); y++)
        for (unsigned x = 0; x < game_field->get_size_x(); x++)
            if (rectangle_is_pressed(cells[y][x]))
                game_field->change_cell_status(x, y);
}

void GUI::update_delay()
{
    if (rectangle_is_pressed(inc_speed_button)) {
        if (delay > MIN_DELAY + D_DELAY / 2)
            delay -= D_DELAY;
    }
    if (rectangle_is_pressed(dec_speed_button)) {
        if (delay < MAX_DELAY - D_DELAY / 2)
            delay += D_DELAY;
    }
}

void GUI::update_game_status()
{
    if (rectangle_is_pressed(pause_button))
        game_is_running = !game_is_running;
}

bool GUI::rectangle_is_pressed(RectangleShape button)
{
    return (button.getGlobalBounds().contains(
                    Mouse::getPosition(window).x, Mouse::getPosition(window).y)
            && Mouse::isButtonPressed(Mouse::Button::Left));
}

int GUI::get_speed()
{
    double percentage = (1 - delay / MAX_DELAY) * 100;
    return (int)percentage + 10;
}
