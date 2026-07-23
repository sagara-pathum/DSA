#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

class Menu
{
    protected:
        int max_y, max_x;

    public:
        Menu();

        void loading();
        void screen_border();
        void plug_and_test();
        int run();
};

#endif
