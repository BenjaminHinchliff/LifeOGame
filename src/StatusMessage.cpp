#include "StatusMessage.h"

StatusMessage::StatusMessage(int row, Align align, std::string message)
    : m_row{ row }, m_align{ align }, m_message{ message }
{
}

StatusMessage::StatusMessage(int row, Align align, const char* message)
    : StatusMessage(row, align, std::string{ message })
{
}

void StatusMessage::draw(WINDOW* win)
{
    int rows;
    int cols;
    getmaxyx(win, rows, cols);

    switch (m_align)
    {
    case Align::LEFT:
        mvaddstr(m_row, 0, m_message.c_str());
        break;
    case Align::CENTER:
        mvaddstr(m_row, (cols - m_message.length()) / 2, m_message.c_str());
        break;
    case Align::RIGHT:
        mvaddstr(m_row, cols - m_message.length(), m_message.c_str());
        break;
    }
}

void StatusMessage::setMessage(std::string message)
{
    m_message = message;
}

void StatusMessage::setMessage(const char* message)
{
    setMessage(std::string{ message });
}