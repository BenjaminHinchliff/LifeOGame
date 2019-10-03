#include "Screen.h"

Screen::Screen(int height, int width, int y0, int x0, const Life& data)
    : m_win{ newwin(height, width, y0, x0), &delwin }, m_displayArr{ data.getData() }
{
    if (static_cast<int>(m_displayArr.size()) != height)
    {
        throw std::length_error{ "Height must equal array height dimension" };
    }
    for (const auto& arr : m_displayArr)
    {
        if (static_cast<int>(arr.size()) != width / 2)
        {
            throw std::length_error{ "Width must equal array width dimension" };
        }
    }
    refresh();
}

void Screen::update()
{
    werase(m_win.get());

    wmove(m_win.get(), 0, 0);
    for (const auto& arr : m_displayArr)
    {
        for (const bool& pixel : arr)
        {
            waddch(m_win.get(), pixel ? ACS_BLOCK : ' ');
            waddch(m_win.get(), pixel ? ACS_BLOCK : ' ');
        }
    }
    wrefresh(m_win.get());
}