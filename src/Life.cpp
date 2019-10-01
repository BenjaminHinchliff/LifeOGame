#include "Life.h"

#include <iostream>

Life::Life()
    : m_height{ 0 }, m_width{ 0 }, m_data{}
{
}

Life::Life(int height, int width, const char* initialRLEFile)
    : m_data(height, std::vector<bool>(width, false)),
    m_height{ height }, m_width{ width }
{
    std::ifstream rleFile{ initialRLEFile };
    std::stringstream rleString;
    rleString << rleFile.rdbuf();
    std::string initer{ rleString.str() };

    // remove extranious lines (comments, author, name)
    std::vector<std::string> ignoreLineChars{ "#C", "#N", "#O", "#P", "#R", "#r" };
    while (strContainsStrsInArr(initer, ignoreLineChars))
    {
        initer.erase(0, initer.find('\n') + 1);
    }

    // check pattern can fit on display and ignore the rule for now
    // TODO: maybe clean this up a bit? I don't know if I can though
    int parseIndStart{ static_cast<int>(initer.find('=')) + 1 };
    int patternWidth{ stoi(initer.substr(parseIndStart, initer.find(',') - parseIndStart)) };
    parseIndStart = static_cast<int>(initer.find('=', parseIndStart + 1)) + 1;
    int patternHeight{ stoi(initer.substr(parseIndStart, initer.find(',') - parseIndStart)) };
    if (patternHeight > m_height || patternWidth > m_width)
    {
        throw std::length_error{ "pattern must fit on screen" };
    }

    // get rid of data line
    initer.erase(0, initer.find('\n') + 1);

    // delete newline character in the pattern
    int delChar{};
    while ((delChar = initer.find('\n')) != std::string::npos)
    {
        initer.erase(delChar, 1);
    }


    int yPos{ 0 };
    int xPos{ 0 };
    int numeral{ 0 };
    for (int charInd{ 0 }; initer[charInd] != '!' && charInd < static_cast<int>(initer.length()); ++charInd)
    {
        
        if (initer[charInd] == '$')
        {
            ++yPos;
            xPos = 0;
            numeral = 0;
            continue;
        }
        
        if (std::isdigit(initer[charInd]))
        {
            numeral = numeral * 10 + (initer[charInd] - '0');
            continue;
        }
        if (numeral != 0)
        {
            for (int j{ 0 }; j < numeral; ++j)
            {
                m_data[yPos][xPos++] = (initer[charInd] == 'o');
            }
            numeral = 0;
        }
        else
        {
            m_data[yPos][xPos++] = (initer[charInd] == 'o');
        }

    }
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

void Life::resize(int height, int width)
{
    m_height = height;
    m_width = width;
    m_data.resize(height);
    for_each(m_data.begin(), m_data.end(), [=](std::vector<bool>& arr) { arr.resize(width); });
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
    for (int y{ 0 }; y < static_cast<int>(m_data.size()); ++y)
    {
        for (int x{ 0 }; x < static_cast<int>(m_data[y].size()); ++x)
        {
            const chtype toApply{ m_data[y][x] ? A_REVERSE : A_NORMAL };
            mvwaddch(win, y, x * 2, inch() | toApply);
            waddch(win, inch() | toApply);
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

bool Life::strContainsStrsInArr(std::string toSearch, std::vector<std::string> searchStrs)
{
    for (std::string str : searchStrs)
    {
        if (toSearch.find(str) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}