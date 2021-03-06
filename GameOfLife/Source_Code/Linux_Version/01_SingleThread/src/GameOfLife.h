#pragma once

#include "Cell.h"

#include <SFML/System/Vector2.hpp>

#include <cstdint>
#include <vector>

class GameOfLife
{
public:
    GameOfLife(sf::Vector2i size);

    // Set the value of the cell at the given grid position to the given alive state.
    void setCell(int x, int y, bool alive);

    // Updates the state of the game world by one tick.
    void update();

    // Returns a reference to the cell value at the given grid position.
    std::uint8_t & getCell(int x, int y);

    // Returns a vector of the given cell's grid position by its cell index.
    sf::Vector2i get2D(int index) const;

    auto const& getLivingCells() const { return aliveCells; }

    // Returns a color to use for cells/backgrounds based on the thread ID #.
    static sf::Color getThreadColor(int index);

    // Represents the width and height of the simulated world.
    const sf::Vector2i worldSize;

private:

    // A cache of all the alive cells at the end of the update() call.
    std::vector<Cell> aliveCells = {};

    // A 1D representation of the 2D grid that is the world.
    std::vector<std::uint8_t> world;

    // A buffer where the next world state is prepared, swapped with world at end of update().
    std::vector<std::uint8_t> worldBuffer;
};