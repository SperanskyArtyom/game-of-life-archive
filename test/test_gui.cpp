#define private public
#include <lifelib/gui.h>
#undef private

#include <ctest.h>

CTEST(gui_game_field, field_size_x)
{
    // Given
    GUI test_game;
    test_game.set_game_field();

    // When
    const unsigned result = test_game.game_field->get_size_x();

    // Then
    const unsigned expected = 20U;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(gui_game_field, field_size_y)
{
    // Given
    GUI test_game;
    test_game.set_game_field();

    // When
    const unsigned result = test_game.game_field->get_size_y();

    // Then
    const unsigned expected = 20U;
    ASSERT_EQUAL_U(expected, result);
}

CTEST(gui_game_field, position)
{
    // Given
    GUI test_game;
    test_game.set_game_field();

    // When
    const bool result
            = test_game.field_bound.getPosition() == sf::Vector2f{40, 40};

    // Then
    ASSERT_TRUE(result);
}

CTEST(gui_cells, positon)
{
    // Given
    GUI test_game;
    test_game.set_game_field();

    // When
    const bool result
            = test_game.cells[0][0].getPosition() == sf::Vector2f{40, 40};

    // Then
    ASSERT_TRUE(result);
}

CTEST(game_speed, min)
{
    // Given
    GUI test_game;
    test_game.delay = 1.0;

    // When
    const int result = test_game.get_speed();

    // Then
    const int expected = 10;
    ASSERT_EQUAL(expected, result);
}

CTEST(game_speed, max)
{
    // Given
    GUI test_game;
    test_game.delay = 0.1;

    // When
    const int result = test_game.get_speed();

    // Then
    const int expected = 100;
    ASSERT_EQUAL(expected, result);
}
