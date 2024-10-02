#include <lifelib/GameOfLife.h>

#include <iostream>

GameOfLife::GameOfLife(unsigned x, unsigned y) : size_x{x}, size_y{y}
{
    field = create_field();
}
GameOfLife::GameOfLife() : GameOfLife::GameOfLife(10, 10)
{
}
GameOfLife::GameOfLife(const GameOfLife& model)
    : GameOfLife::GameOfLife(model.size_x, model.size_y)
{
}

GameOfLife::~GameOfLife()
{
    delete_field();
}

void GameOfLife::move_to_next_generation()
{
    bool** next_generation = create_next_generation();
    delete_field();
    field = next_generation;
}

void GameOfLife::print()
{
    for (unsigned i = 0; i < size_y; i++) {
        for (unsigned j = 0; j < size_x; j++)
            if (field[i][j])
                std::cout << '*';
            else
                std::cout << 'O';
        std::cout << std::endl;
    }
}

void GameOfLife::change_cell_status(unsigned x, unsigned y)
{
    field[y][x] = !field[y][x];
}

unsigned GameOfLife::get_size_x()
{
    return size_x;
}
unsigned GameOfLife::get_size_y()
{
    return size_y;
}
bool GameOfLife::get_cell_status(unsigned x, unsigned y)
{
    return field[y][x];
}

bool** GameOfLife::create_field()
{
    bool** clear_field = new bool*[size_y];
    for (unsigned i = 0; i < size_y; i++) {
        clear_field[i] = new bool[size_x];
        for (unsigned j = 0; j < size_x; j++)
            clear_field[i][j] = false;
    }
    return clear_field;
}

void GameOfLife::delete_field()
{
    for (unsigned i = 0; i < size_y; i++)
        delete[] field[i];
    delete[] field;
}

bool GameOfLife::is_alive(int x, int y)
{
    if (x < 0)
        x = size_x - 1;
    else if (x == (int)size_x)
        x = 0;
    if (y < 0)
        y = size_y - 1;
    else if (y == (int)size_y)
        y = 0;
    return field[y][x];
}

bool GameOfLife::will_be_alive(unsigned x, unsigned y)
{
    int alive_neighbors = 0;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            alive_neighbors += is_alive(x + j, y + i);
    if (field[y][x]) {
        if ((alive_neighbors - 1) == 2 || (alive_neighbors - 1) == 3)
            return true;
        return false;
    }
    if (alive_neighbors == 3)
        return true;
    return false;
}

bool** GameOfLife::create_next_generation()
{
    bool** next_generation = create_field();
    for (unsigned i = 0; i < size_y; i++)
        for (unsigned j = 0; j < size_x; j++)
            next_generation[i][j] = will_be_alive(j, i);
    return next_generation;
}
