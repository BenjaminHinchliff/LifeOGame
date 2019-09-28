#include "Life.h"

Life::Life(int height, int width)
    : m_data(height, std::vector<bool>(width, false))
{
}

void Life::setPixel(int y, int x, bool value)
{
    m_data[y][x] = value;
}

void Life::togglePixel(int y, int x)
{
    m_data[y][x] = !m_data[y][x];
}

void Life::clear()
{
    int width{ static_cast<int>(m_data[0].size()) };
    std::fill(m_data.begin(), m_data.end(), std::vector<bool>(width, false));
}

// no you have too many for loops
void Life::update()
{
    std::vector<std::vector<bool>> newData{ m_data };
    int height = m_data.size();
    for (int i{ 0 }; i < height; ++i)
    {
        int width = m_data[i].size();
        for (int j{ 0 }; j < width; ++j)
        {
            int surroundingTotal{ 0 };
            for (int row{ i - 1 }; row <= i + 1; ++row)
            {
                int modRow{ row < 0 ? height + row : row % height};
                for (int col{ j - 1 }; col <= j + 1; ++col)
                {
                    int modCol{ col < 0 ? width + col : col % width };
                    surroundingTotal += m_data[modRow][modCol];
                }
            }
            surroundingTotal -= m_data[i][j];
            if (m_data[i][j] == true)
            {
                if (surroundingTotal < 2 || surroundingTotal > 3)
                    newData[i][j] = false;
            }
            else
            {
                if (surroundingTotal == 3)
                    newData[i][j] = true;
            }
        }
    }
    m_data = newData;
}

void Life::draw(WINDOW* win)
{
    wmove(win, 0, 0);
    for (const auto& arr : m_data)
    {
        for (const bool& pixel : arr)
        {
            waddch(win, ' ' | (pixel ? A_REVERSE : A_NORMAL));
            waddch(win, ' ' | (pixel ? A_REVERSE : A_NORMAL));
            //waddch(win, pixel ? ACS_BLOCK : ' ');
        }
    }
}

const std::vector<std::vector<bool>>& Life::getData() const
{
    return m_data;
}