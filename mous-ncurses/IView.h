#ifndef IVIEW_H
#define IVIEW_H

#include <ncurses.h>
#include <panel.h>

#include <string>

class IView
{
public:
    virtual ~IView() { }

    virtual void OnResize(int x, int y, int w, int h) = 0;
    virtual void Refresh(int x, int y, int w, int h) = 0;

    virtual bool InjectKey(int key) = 0;

    virtual void Show(bool show) = 0;
    virtual bool IsShown() const = 0;

    virtual void SetFocus(bool focus) { }
    virtual bool HasFocus() const { return false; }
};

namespace ViewHelper {

const int LEFT_MARGIN = 4;

using namespace std;

static inline void PrintAtCenter(WINDOW* wnd, int y, int w, const string& str)
{
    // NOTE: wide character not considered presently
    int x = (w - str.size()) / 2;
    mvwprintw(wnd, y, x, str.c_str());
}

};

#endif
