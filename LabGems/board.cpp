#include "board.h"
#include "BonusFactory.h"

#include <random>
#include <set>
#include <queue>

std::mt19937 rng(std::random_device{}());

Board::Board()
{
    field.resize(ROWS, std::vector<Cell>(COLS));

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            field[i][j].color = randomColor();
        }
    }

    while (hasGroup())
    {
        removeMatches();
        collapse();
    }
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
    return hasGroup(3);
}

void Board::removeMatches()
{
    std::vector<std::vector<bool>> used(ROWS, std::vector<bool>(COLS, false));

    std::set<std::pair<int, int>> removeList;

    int dx[4] = { 1,-1,0,0 };
    int dy[4] = { 0,0,1,-1 };

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (used[r][c])
                continue;

            int color = field[r][c].color;

            std::queue<std::pair<int, int>> q;

            std::vector<std::pair<int, int>> component;

            q.push({ r,c });
            used[r][c] = true;

            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();

                component.push_back({ x,y });

                for (int k = 0; k < 4; k++)
                {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if (nx < 0 || nx >= ROWS)
                        continue;

                    if (ny < 0 || ny >= COLS)
                        continue;

                    if (used[nx][ny])
                        continue;

                    if (field[nx][ny].color != color)
                        continue;

                    used[nx][ny] = true;
                    q.push({ nx,ny });
                }
            }

            if (component.size() >= 3)
            {
                for (auto& p : component)
                {
                    removeList.insert(p);
                }
            }
        }
    }

    std::uniform_real_distribution<float>
        bonusChance(0.f, 1.f);

    for (auto& p : removeList)
    {
        int r = p.first;
        int c = p.second;

        int sourceColor = field[r][c].color;

        if (bonusChance(rng) < 0.15f)
        {
            processBonuses(r, c, sourceColor);
        }

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

Cell& Board::getCell(int row, int col)
{
    return field[row][col];
}

int Board::getRows() const
{
    return ROWS;
}

int Board::getCols() const
{
    return COLS;
}

void Board::processBonuses(int row, int col, int sourceColor)
{
    auto bonus = BonusFactory::create();
    bonus->apply(*this, row, col, sourceColor);
}

bool Board::hasGroup(int minSize)
{
    std::vector<std::vector<bool>> used(ROWS, std::vector<bool>(COLS, false));

    int dx[4] = { 1,-1,0,0 };
    int dy[4] = { 0,0,1,-1 };

    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (used[r][c])
                continue;

            int color = field[r][c].color;

            std::queue<std::pair<int, int>> q;

            q.push({ r,c });

            used[r][c] = true;

            int count = 0;

            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();

                count++;

                for (int k = 0; k < 4; k++)
                {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if (nx < 0 || nx >= ROWS)
                        continue;

                    if (ny < 0 || ny >= COLS)
                        continue;

                    if (used[nx][ny])
                        continue;

                    if (field[nx][ny].color != color)
                        continue;

                    used[nx][ny] = true;

                    q.push({ nx,ny });
                }
            }

            if (count >= minSize)
                return true;
        }
    }

    return false;
}