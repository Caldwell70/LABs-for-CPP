#pragma once

#include <SFML/Graphics.hpp>
#include "bonus.h"

#include <vector>
#include <memory>

constexpr int CELL_SIZE = 64;
constexpr int ROWS = 8;
constexpr int COLS = 8;
constexpr int COLORS_COUNT = 5;

struct Cell
{
    int color;
};

class Board
{
private:
    std::vector<std::vector<Cell>> field;
public:
    Board();

    void draw(sf::RenderWindow& window);

    bool swapCells(int r1, int c1, int r2, int c2);

    bool checkMatches();
    void removeMatches();
    void collapse();

    void processBonuses(int row, int col, int sourceColor);

    Cell& getCell(int row, int col);

    int getRows() const;
    int getCols() const;

    bool hasGroup(int minSize = 3);

    int randomColor();

    Cell& get(int r, int c);
};
