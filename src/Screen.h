#pragma once

#include <memory>
#include <vector>
#include <stdexcept>

#include <curses.h>

#include "Life.h"

class Screen
{
public:
    Screen(int height, int width, int y0, int x0, const Life& data);

    void update();
    
private:
    // unique ptr to sore the window which deletes it with delwin
    std::unique_ptr<WINDOW, decltype(&delwin)> m_win;
    const std::vector<std::vector<bool>>& m_displayArr;
};
