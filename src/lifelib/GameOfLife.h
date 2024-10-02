#pragma once

class GameOfLife {
public:
    GameOfLife(unsigned x, unsigned y);
    GameOfLife();
    GameOfLife(const GameOfLife& model);

    ~GameOfLife();

    unsigned get_size_x();
    unsigned get_size_y();

    bool get_cell_status(unsigned x, unsigned y);

    void move_to_next_generation();
    void change_cell_status(unsigned x, unsigned y);
    void print();

private:
    const unsigned size_x;
    const unsigned size_y;
    bool** field;

    bool** create_field();
    bool** create_next_generation();

    bool is_alive(int x, int y);
    bool will_be_alive(unsigned x, unsigned y);

    void delete_field();
};
