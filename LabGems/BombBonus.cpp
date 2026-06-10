#include "BombBonus.h"
#include "board.h"

#include <vector>
#include <algorithm>
#include <random>

extern std::mt19937 rng;

void BombBonus::apply(Board& board, int row, int col, int sourceColor)
{
    board.getCell(row, col).color = -1;

    std::vector<std::pair<int, int>> cells;

    for (int r = 0; r < board.getRows(); r++)
    {
        for (int c = 0; c < board.getCols(); c++)
        {
            if (r == row && c == col)
                continue;

            cells.push_back({ r,c });
        }
    }

    std::shuffle(cells.begin(), cells.end(), rng);

    int destroyed = 1;

    for (auto& p : cells)
    {
        board.getCell(p.first, p.second).color = -1;

        destroyed++;

        if (destroyed == 5)
            break;
    }
}