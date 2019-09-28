#pragma once

#include <string>

#include <curses.h>

enum class Align
{
    LEFT,
    CENTER,
    RIGHT,
};

class StatusMessage
{
public:

public:
    StatusMessage(int row, Align align, std::string message);
    StatusMessage(int row, Align align, const char* message);

    void draw(WINDOW* win);

    void setMessage(std::string message);
    void setMessage(const char* message);
private:
    Align m_align;
    int m_row;
    std::string m_message;
};

