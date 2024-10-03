#pragma once

class GameOfLife {
public:
    GameOfLife(unsigned x, unsigned y);
    GameOfLife();

    ~GameOfLife();

    [[nodiscard]] unsigned get_size_x() const;
    [[nodiscard]] unsigned get_size_y() const;

    bool get_cell_status(unsigned x, unsigned y);

    void move_to_next_generation();
    void change_cell_status(unsigned x, unsigned y);

private:
    const unsigned size_x;
    const unsigned size_y;
    bool** field;

    [[nodiscard]] bool** create_field() const;
    bool** create_next_generation();

    bool is_alive(int x, int y);
    bool will_be_alive(unsigned x, unsigned y);

    void delete_field();
};
