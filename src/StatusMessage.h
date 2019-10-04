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
    void moveToRow(int row);
private:
    int m_row;
    Align m_align;
    std::string m_message;
};

