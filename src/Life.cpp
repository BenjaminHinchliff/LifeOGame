#include "Life.h"

Life::Life(int height, int width)
    : m_data(height, std::vector<bool>(width, false)),
    m_height{ height }, m_width{ width }
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

void Life::update()
{
    auto newData{ m_data };
    for (int y{ 0 }; y < m_height; ++y)
    {
        for (int x{ 0 }; x < m_width; ++x)
        {
            int total = getSurroundingTotal(y, x);
            if (m_data[y][x] == true)
            {
                if (total < 2 || total > 3)
                    newData[y][x] = false;
            }
            else
            {
                if (total == 3)
                    newData[y][x] = true;
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
            attron(pixel ? A_REVERSE : A_NORMAL);
            waddstr(win, "  ");
            attroff(A_REVERSE);
        }
    }
}

const std::vector<std::vector<bool>>& Life::getData() const
{
    return m_data;
}

int Life::getSurroundingTotal(int y, int x)
{
    int surroundingTotal{ 0 };
    for (int row{ y - 1 }; row <= y + 1; ++row)
    {
        int modRow{ row < 0 ? m_height + row : row % m_height };
        for (int col{ x - 1 }; col <= x + 1; ++col)
        {
            int modCol{ col < 0 ? m_width + col : col % m_width };
            surroundingTotal += m_data[modRow][modCol];
        }
    }
    surroundingTotal -= m_data[y][x];
    return surroundingTotal;
}