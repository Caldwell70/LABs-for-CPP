#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Bonus.h"

const int CELL_SIZE = 64;
const int ROWS = 8;
const int COLS = 8;
const int COLORS_COUNT = 5;

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

    void recolorBonus(int row, int col, int color);
    void bombBonus(int row, int col);

    int randomColor();

    Cell& get(int r, int c);
};