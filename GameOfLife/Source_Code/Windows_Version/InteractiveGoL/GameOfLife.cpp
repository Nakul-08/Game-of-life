#include "GameOfLife.h"

#include <omp.h>

#include <array>

GameOfLife::GameOfLife(sf::Vector2i size)
    : worldSize(size),
    world(size.x* size.y, false),
    worldBuffer(world)
{
    aliveCells.reserve(size.x * size.y); // reserve space for worst-case(all cells are alive)

    // place an "acorn"
    int midX = worldSize.x / 2;
    int midY = worldSize.y / 2;
    getCell(midX + 0, midY + 0) = 1;
    getCell(midX + 1, midY + 0) = 1;
    getCell(midX + 4, midY + 0) = 1;
    getCell(midX + 5, midY + 0) = 1;
    getCell(midX + 6, midY + 0) = 1;
    getCell(midX + 3, midY + 1) = 1;
    getCell(midX + 1, midY + 2) = 1;
}

std::uint8_t& GameOfLife::getCell(int x, int y)
{

    return world[y * worldSize.x + x];
}

sf::Vector2i GameOfLife::get2D(int index) const
{
    int y = index / worldSize.x;
    int x = index % worldSize.x;
    return { x, y };
}

sf::Color GameOfLife::getThreadColor(int index)
{
    switch (index % 4) {
    case 0:
        return sf::Color::Red;
    case 1:
        return sf::Color::Green;
    case 2:
        return sf::Color::Blue;
    case 3:
        return sf::Color::Yellow;
    }

    return sf::Color::White;
}

void GameOfLife::update()
{
    // clear aliveCells cache
    aliveCells.clear();

#pragma omp parallel
    {
        // private, per-thread variables
        auto this_thread_color = getThreadColor(omp_get_thread_num());
        std::vector<Cell> next_generation;

#pragma omp for
        for (int i = 0; i < worldSize.x * worldSize.y; ++i) {
            auto const pos = get2D(i);
            int aliveCount = 0;

            // check all 8 neighbors
            static const std::array<std::array<int, 2>, 8> neighbours{ {{-1, -1}, {0, -1}, {1, -1},
                                                                       {-1,  0},          {1,  0},
                                                                       {-1,  1}, {0,  1}, {1,  1}} };
            for (auto const [nX, nY] : neighbours) {
                // wrap around to other side if neighbor would be outside world
                int newX = (nX + pos.x + worldSize.x) % worldSize.x;
                int newY = (nY + pos.y + worldSize.y) % worldSize.y;

                aliveCount += getCell(newX, newY);
            }

            // Evaluate game rules on current cell
            bool dies = aliveCount == 2 || aliveCount == 3;
            bool lives = aliveCount == 3;
            worldBuffer[i] = world[i] ? dies : lives;

            // if the cell's alive push it into the vector
            if (worldBuffer[i])
                next_generation.emplace_back(Cell{ pos, this_thread_color });
        }

#pragma omp critical
        aliveCells.insert(aliveCells.end(), next_generation.begin(), next_generation.end());
    }

    // apply updates
    world.swap(worldBuffer);
}

void GameOfLife::setCell(int x, int y, bool alive)
{
    // constrain x and y
    x = std::max(std::min(x, (int)worldSize.x - 1), 0);
    y = std::max(std::min(y, (int)worldSize.y - 1), 0);
    getCell(x, y) = alive;
    aliveCells.push_back(Cell{ sf::Vector2i(x, y), sf::Color::White });
}