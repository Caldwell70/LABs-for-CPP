#include "Board.h"
#include <random>
#include <set>

std::mt19937 rng(std::random_device{}());

Board::Board()
{
    field.resize(ROWS, std::vector<Cell>(COLS));

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            field[i][j].color = randomColor();
}

int Board::randomColor()
{
    std::uniform_int_distribution<int> dist(0, COLORS_COUNT - 1);
    return dist(rng);
}

Cell& Board::get(int r, int c)
{
    return field[r][c];
}

void Board::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rect(sf::Vector2f(static_cast<float>(CELL_SIZE - 2),static_cast<float>(CELL_SIZE - 2)));

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            switch (field[i][j].color)
            {
            case 0: rect.setFillColor(sf::Color::Red); break;
            case 1: rect.setFillColor(sf::Color::Blue); break;
            case 2: rect.setFillColor(sf::Color::Green); break;
            case 3: rect.setFillColor(sf::Color::Yellow); break;
            case 4: rect.setFillColor(sf::Color::Magenta); break;
            }

            rect.setPosition(sf::Vector2f(static_cast<float>(j * CELL_SIZE),static_cast<float>(i * CELL_SIZE)));

            window.draw(rect);
        }
    }
}

bool Board::swapCells(int r1, int c1, int r2, int c2)
{
    std::swap(field[r1][c1], field[r2][c2]);

    if (checkMatches())
        return true;

    std::swap(field[r1][c1], field[r2][c2]);
    return false;
}

bool Board::checkMatches()
{
    for (int i = 0; i < ROWS; i++)
    {
        int count = 1;

        for (int j = 1; j < COLS; j++)
        {
            if (field[i][j].color ==
                field[i][j - 1].color)
                count++;
            else
                count = 1;

            if (count >= 3)
                return true;
        }
    }

    for (int j = 0; j < COLS; j++)
    {
        int count = 1;

        for (int i = 1; i < ROWS; i++)
        {
            if (field[i][j].color == field[i - 1][j].color)
                count++;
            else
                count = 1;

            if (count >= 3)
                return true;
        }
    }

    return false;
}

void Board::removeMatches()
{
    std::set<std::pair<int, int>> removeList;

    for (int i = 0; i < ROWS; i++)
    {
        int count = 1;

        for (int j = 1; j <= COLS; j++)
        {
            if (j < COLS && field[i][j].color == field[i][j - 1].color)
            {
                count++;
            }
            else
            {
                if (count >= 3)
                {
                    for (int k = 0; k < count; k++)
                        removeList.insert({ i,j - 1 - k });
                }
                count = 1;
            }
        }
    }

    for (int j = 0; j < COLS; j++)
    {
        int count = 1;

        for (int i = 1; i <= ROWS; i++)
        {
            if (i < ROWS && field[i][j].color == field[i - 1][j].color)
            {
                count++;
            }
            else
            {
                if (count >= 3)
                {
                    for (int k = 0; k < count; k++)
                        removeList.insert({ i - 1 - k,j });
                }
                count = 1;
            }
        }
    }

    std::uniform_real_distribution<float> bonusChance(0, 1);

    for (auto& p : removeList)
    {
        int r = p.first;
        int c = p.second;

        int sourceColor = field[r][c].color;

        if (bonusChance(rng) < 0.15f)
            processBonuses(r, c, sourceColor);

        field[r][c].color = -1;
    }
}

void Board::collapse()
{
    for (int col = 0; col < COLS; col++)
    {
        int writeRow = ROWS - 1;

        for (int row = ROWS - 1; row >= 0; row--)
        {
            if (field[row][col].color != -1)
            {
                field[writeRow][col] = field[row][col];

                writeRow--;
            }
        }

        while (writeRow >= 0)
        {
            field[writeRow][col].color = randomColor();

            writeRow--;
        }
    }
}

void Board::recolorBonus(int row, int col, int color)
{
    field[row][col].color = color;

    std::vector<std::pair<int, int>> cells;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int dist =
                abs(i - row) + abs(j - col);

            if (dist <= 3 &&
                !(i == row && j == col))
            {
                cells.push_back({ i,j });
            }
        }
    }

    std::shuffle(cells.begin(), cells.end(), rng);

    int painted = 0;

    for (auto& p : cells)
    {
        field[p.first][p.second].color = color;

        painted++;

        if (painted == 2)
            break;
    }
}

void Board::bombBonus(int row, int col)
{
    field[row][col].color = -1;

    std::vector<std::pair<int, int>> cells;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            cells.push_back({ i,j });

    std::shuffle(cells.begin(), cells.end(), rng);

    int destroyed = 0;

    for (auto& p : cells)
    {
        field[p.first][p.second].color = -1;

        destroyed++;

        if (destroyed == 5)
            break;
    }
}

void Board::processBonuses(int row, int col, int sourceColor)
{
    std::uniform_int_distribution<int> bonus(0, 1);

    int targetRow = row + (rng() % 7) - 3;

    if (targetRow < 0)
        targetRow = 0;

    if (targetRow >= ROWS)
        targetRow = ROWS - 1;

    int targetCol = col + (rng() % 7) - 3;

    if (targetCol < 0)
        targetCol = 0;

    if (targetCol >= COLS)
        targetCol = COLS - 1;

    if (bonus(rng) == 0)
        recolorBonus(targetRow, targetCol, sourceColor);
    else
        bombBonus(targetRow, targetCol);
}