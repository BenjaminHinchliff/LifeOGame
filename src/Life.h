#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>

#include <curses.h>

class Life
{
public:
    Life();
    Life(int height, int width, const char* initialRLE = "");

    void setPixel(int y, int x, bool value);
    void togglePixel(int y, int x);
    void clear();
    void resize(int height, int width);

    void update();
    void draw(WINDOW* win);

    const std::vector<std::vector<bool>>& getData() const;
private:
    int getSurroundingTotal(int y, int x);
    bool strContainsStrsInArr(std::string toSearch, std::vector<std::string> searchStrs);

    int m_height = 0;
    int m_width = 0;
    std::vector<std::vector<bool>> m_data = {};
    std::vector<int> m_bornRules = { 3 };
    std::vector<int> m_survivalRules = { 2, 3 };
};
