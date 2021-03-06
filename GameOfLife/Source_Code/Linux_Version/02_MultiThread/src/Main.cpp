#include <iostream> // +
#include <cstdlib> // +
#include <ctime> // +
#include <chrono> // +
#include <string>
#include "GameOfLife.h"
#include "WorldRenderer.h"
#include <SFML/Graphics.hpp>

static const sf::Vector2i World_Size = { 256, 256 };

int main()
{
    std::cout << "Enter number of generations: ";
    int num_generations;
    std::cin >> num_generations;

    auto start = std::chrono::high_resolution_clock::now();
    
    // Random seed
    srand((unsigned) time(0));

    // create the window
    sf::RenderWindow window({256, 256}, "Game of Life");
    // scale the image up 2x size
    window.setSize({512, 512});

    sf::View view(sf::FloatRect(0, 0, 256, 256));
    view.zoom(0.5f);
    window.setView(view);

    // disable vsync and uncap framerate limit
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(0);

    // Create the game
    GameOfLife game(World_Size);

    // Create a world renderer
    WorldRenderer worldRenderer;

    // // Track if mouse button is being held down
    // bool mouseHeld = false;

    int generation = 0;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            // // capture if the user is holding left mouse button down
            // if (event.type == sf::Event::MouseButtonPressed) {
            //     if (event.mouseButton.button == sf::Mouse::Left)
            //         mouseHeld = true;
            // } else if (event.type == sf::Event::MouseButtonReleased) {
            //     if (event.mouseButton.button == sf::Mouse::Left)
            //         mouseHeld = false;
            // }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // // if left mouse button held down then make cells under cursor alive and pause simulation
        // if (mouseHeld)
        // {
        //     auto mousePosition = sf::Mouse::getPosition(window);

        //     // normalize mouse pos
        //     int x = mousePosition.x * World_Size.x / window.getSize().x;
        //     int y = mousePosition.y * World_Size.y / window.getSize().y;

        //     // set cell under cursor to alive
        //     game.setCell(x, y, true);
        // }
        // else
        // {
        //     // update the game world
        //     game.update();
        // }
        // make random cells alive
        int x = (rand() % window.getSize().x) + 1;
        int y = (rand() % window.getSize().y) + 1;
        game.setCell(x, y, true);

        // update the game world
        game.update();
        
        // render the game
        worldRenderer.render(window, game);

        if (++generation == num_generations)
        {
            window.close();
            break;
        }
        std::cout << generation << "\n";
        // sf::Text gen;
        // gen.setFillColor(sf::Color::White);
        // gen.setString(std::to_string(generation++));
        // window.draw(gen);

        // end the current frame
        window.display();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << " s" << std::endl;
}
