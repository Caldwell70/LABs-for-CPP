#include "RecolorBonus.h"
#include "board.h"

#include <vector>
#include <algorithm>
#include <random>

extern std::mt19937 rng;

void RecolorBonus::apply(Board& board, int row, int col, int sourceColor)
{
    std::vector<std::pair<int, int>> cells;

    for (int r = 0; r < board.getRows(); r++)
    {
        for (int c = 0; c < board.getCols(); c++)
        {
            if (r == row && c == col)
                continue;

            int dist = std::abs(r - row) + std::abs(c - col);

            if (dist > 1 && dist <= 3)
            {
                cells.push_back({ r,c });
            }
        }
    }

    std::shuffle(cells.begin(), cells.end(), rng);

    board.getCell(row, col).color = sourceColor;

    int painted = 0;

    for (auto& p : cells)
    {
        board.getCell(p.first, p.second).color = sourceColor;

        painted++;

        if (painted == 2)
            break;
    }
}