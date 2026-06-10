#include <SFML/Graphics.hpp>
#include "board.h"

#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(COLS * CELL_SIZE, ROWS * CELL_SIZE)), "GEMS");

    Board board;
    bool selected = false;
    int sr, sc;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                int c = mouse->position.x / CELL_SIZE;
                int r = mouse->position.y / CELL_SIZE;

                if (r < 0 || r >= ROWS)
                    continue;

                if (c < 0 || c >= COLS)
                    continue;

                if (!selected)
                {
                    sr = r;
                    sc = c;
                    selected = true;
                }
                else
                {
                    if (abs(sr - r) + abs(sc - c) == 1)
                    {
                        if (board.swapCells(
                            sr, sc, r, c))
                        {
                            do
                            {
                                board.removeMatches();
                                board.collapse();
                            } while (board.checkMatches());
                        }
                    }

                    selected = false;
                }
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}