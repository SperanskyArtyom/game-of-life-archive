#define private public
#include <lifelib/GameOfLife.h>
#undef private

#include <ctest.h>

CTEST(game_field_size, size_x)
{
    // Given
    const unsigned x = 9;
    const unsigned y = 1;
    GameOfLife test_field(x, y);

    // When
    const unsigned result = test_field.get_size_x();

    // Then
    const unsigned expected = x;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(game_field_size, size_y)
{
    // Given
    const unsigned x = 1;
    const unsigned y = 5;
    GameOfLife test_field(x, y);

    // When
    const unsigned result = test_field.get_size_y();

    // Then
    const unsigned expected = y;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(game_field_size, standart_size_x)
{
    // Given
    GameOfLife test_field;

    // When
    const unsigned result = test_field.get_size_x();

    // Then
    const unsigned expected = 10;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(game_field_size, standart_size_y)
{
    // Given
    GameOfLife test_field;

    // When
    const unsigned result = test_field.get_size_y();

    // Then
    const unsigned expected = 10;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(cell_status, dead_cell)
{
    // Given
    GameOfLife test_field;

    // When
    const bool result = test_field.get_cell_status(0, 0);

    // Then
    ASSERT_FALSE(result);
}

CTEST(cell_status, alive_cell)
{
    // Given
    GameOfLife test_field;
    test_field.change_cell_status(0, 0);

    // When
    const bool result = test_field.get_cell_status(0, 0);

    // Then
    ASSERT_TRUE(result);
}

CTEST(cell_status, clear_field)
{
    // Given
    GameOfLife test_field;

    // When
    int result = 0;
    for (unsigned i = 0; i < test_field.get_size_y(); i++)
        for (unsigned j = 0; j < test_field.get_size_x(); j++)
            result += test_field.get_cell_status(j, i);

    // Then
    const unsigned expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(cell_status, will_dead_cell_be_alive)
{
    // Given
    GameOfLife test_field(3, 3);
    test_field.change_cell_status(2, 0);
    test_field.change_cell_status(2, 1);
    test_field.change_cell_status(0, 1);

    // When
    const bool result = test_field.will_be_alive(0, 0);

    // Then
    ASSERT_TRUE(result);
}

CTEST(cell_status, will_dead_cell_be_alive_2)
{
    // Given
    GameOfLife test_field(3, 3);

    test_field.change_cell_status(1, 0);
    test_field.change_cell_status(2, 0);
    test_field.change_cell_status(2, 1);
    test_field.change_cell_status(0, 1);

    // When
    const bool result = test_field.will_be_alive(0, 0);

    // Then
    ASSERT_FALSE(result);
}

CTEST(cell_status, will_alive_cell_be_alive)
{
    // Given
    GameOfLife test_field(3, 3);

    test_field.change_cell_status(0, 0);
    test_field.change_cell_status(2, 1);
    test_field.change_cell_status(0, 1);

    // When
    const bool result = test_field.will_be_alive(0, 0);

    // Then
    ASSERT_TRUE(result);
}

CTEST(cell_status, will_alive_cell_be_alive_2)
{
    // Given
    GameOfLife test_field(3, 3);
    test_field.change_cell_status(0, 0);

    // When
    const bool result = test_field.will_be_alive(0, 0);

    // Then
    ASSERT_FALSE(result);
}

CTEST(correct_next_generation, empty)
{
    // Given
    GameOfLife test_field(5, 5);
    test_field.move_to_next_generation();

    // When
    bool result = true;
    for (unsigned i = 0; i < 5; i++)
        for (unsigned j = 0; j < 5; j++)
            if (test_field.get_cell_status(i, j))
                result = false;

    // Then
    ASSERT_TRUE(result);
}

CTEST(correct_next_generation, line)
{
    // Given
    GameOfLife test_field(7, 7);
    for (unsigned j = 0; j < 3; j++)
        test_field.change_cell_status(j, 3);
    test_field.move_to_next_generation();

    // When
    bool result = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (j == 1 && i < 5 && i > 1) {
                if (!test_field.get_cell_status(j, i))
                    result = false;
            } else if (test_field.get_cell_status(j, i))
                result = false;
        }
    }

    // Then
    ASSERT_TRUE(result);
}
