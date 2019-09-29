#pragma once

#include <vector>
#include <algorithm>

#include <curses.h>

class Life
{
public:
    Life(int height, int width);

    void setPixel(int y, int x, bool value);
    void togglePixel(int y, int x);
    void clear();
    void resize(int height, int width);

    void update();
    void draw(WINDOW* win);

    const std::vector<std::vector<bool>>& getData() const;
private:
    int getSurroundingTotal(int y, int x);

    int m_height = 0;
    int m_width = 0;
    std::vector<std::vector<bool>> m_data = {};
};