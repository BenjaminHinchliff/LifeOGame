#pragma once

#include <vector>

#include <curses.h>

class Life
{
public:
    Life(int height, int width);

    void setPixel(int y, int x, bool value);
    void togglePixel(int y, int x);
    void clear();

    void update();
    void draw(WINDOW* win);

    const std::vector<std::vector<bool>>& getData() const;
private:
    std::vector<std::vector<bool>> m_data = {};
};