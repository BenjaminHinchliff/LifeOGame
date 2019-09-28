// LifeOGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

// std
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
#include <chrono>

// curses
// this must be before the other includes for the definition to have an effect
#define NCURSES_MOUSE_VERSION
#include <curses.h>

// local
#include "Life.h"
#include "StatusMessage.h"



int main()
{
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    mousemask(REPORT_MOUSE_POSITION | BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON1_CLICKED, nullptr);

    int rows;
    int cols;
    getmaxyx(stdscr, rows, cols);

    Life board{ rows, cols / 2 };

    StatusMessage test{ rows - 1, Align::CENTER, "PAUSED" };

    bool shouldExit{ false };
    bool paused{ false };
    bool mouseDown{ false };

    MEVENT eve;
    MEVENT lastEve{};
    while (!shouldExit)
    {
        auto start = std::chrono::high_resolution_clock::now();

        int ch;
        while ((ch = getch()) != ERR)
        {
            switch (ch)
            {
            case ' ':
                paused ^= true;
                break;
            case 'q':
                shouldExit = true;
                break;
            case 'r':
                board.clear();
                break;
            case KEY_MOUSE:
                if (getmouse(&eve) == OK)
                {
                    if (eve.bstate & BUTTON1_PRESSED)
                        mouseDown = true;
                    else if (eve.bstate & BUTTON1_RELEASED)
                        mouseDown = false;

                    if (eve.bstate & BUTTON1_CLICKED)
                        board.togglePixel(eve.y, eve.x / 2);

                }
                break;
            }
        }

        if (!paused)
            board.update();

        erase();
        board.draw(stdscr);

        if (paused)
            test.draw(stdscr);

        if (getmouse(&eve) == OK)
        {
            eve.x = eve.x / 2 * 2;
            move(eve.y, eve.x);
            if (mouseDown)
            {
                if (lastEve.x != eve.x || lastEve.y != eve.y)
                {
                    board.togglePixel(eve.y, eve.x / 2);
                }
                lastEve = eve;
            }
            else
            {
                for (int i{ 0 }; i < 2; ++i)
                {
                    addch(inch() | A_REVERSE);
                }
            }
        }

        refresh();

        std::this_thread::sleep_until(start + std::chrono::duration<double>{ 1.0 / 15 });
    }

    endwin();
    return 0;
}
