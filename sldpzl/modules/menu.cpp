#include "../libs/menu.h"
#include <cstring>

Menu::Menu() {
    static bool ncurses_initialized = false;
    if (!ncurses_initialized) {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        ncurses_initialized = true;
    } // for protection. cuz i have added ncurses function many times. in many wheres in development
    getmaxyx(stdscr, max_y, max_x);
}

void Menu::loading() {
    const char* msg = "Loading ";
    int len = strlen(msg);
    int center_y = max_y / 2;
    int center_x = max_x / 2;
    int start_x = center_x - (len + 6) / 2;

    move(center_y, start_x);
    printw("%s", msg);
    refresh();

    long j = 0;
    int key_position = start_x + len;

    for (long i = 0; i <= 2400000000; i++) {
        if (j == 400000000) {
            move(center_y, key_position);
            printw("#");
            refresh();
            key_position++;
            j = -1;
        }
        j++;
    }
}

void Menu::screen_border() {
    int x_left = 1;
    int y_top = 1;
    int x_right = max_x - 1;
    int y_bottom = max_y - 2;
    int x_long = max_x - 2;
    int y_long = max_y - 3;

    mvhline(y_top, x_left, ACS_HLINE, x_long);
    mvhline(y_bottom, x_left, ACS_HLINE, x_long);
    mvvline(y_top, x_left, ACS_VLINE, y_long);
    mvvline(y_top, x_right, ACS_VLINE, y_long);

    mvaddch(y_top, x_left, ACS_ULCORNER);
    mvaddch(y_top, x_right, ACS_URCORNER);
    mvaddch(y_bottom, x_left, ACS_LLCORNER);
    mvaddch(y_bottom, x_right, ACS_LRCORNER);
}

void Menu::plug_and_test() {
}

int Menu::run() {
    curs_set(0);
    const char* options[] = {"Play", "Plug and Test (On Development)", "Exit"};
    int num_options = 3;
    int selected = 0;
    int ch;

    while (1) {
        clear();
        screen_border();

        int center_y = max_y / 2;
        int center_x = max_x / 2;

        const char* title = "PUZZLE MIND";
        int title_len = strlen(title);
        int banner_width = title_len + 6;
        int banner_start_x = center_x - banner_width / 2;
        int banner_y = center_y - 6;

        
        mvhline(banner_y, banner_start_x, ACS_HLINE, banner_width);
        mvprintw(banner_y + 1, center_x - title_len / 2, "%s", title);
        mvhline(banner_y + 2, banner_start_x, ACS_HLINE, banner_width);


        for (int i = 0; i < num_options; i++) {
            int opt_len = strlen(options[i]);
            int opt_x = center_x - opt_len / 2;
            int opt_y = center_y + i * 2;

            if (i == selected) {
                mvprintw(opt_y, opt_x - 2, "> ");
                attron(A_REVERSE);
                mvprintw(opt_y, opt_x, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(opt_y, opt_x, "%s", options[i]);
            }
        }

        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                selected = (selected == 0) ? num_options - 1 : selected - 1;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % num_options;
                break;
            case '\n':
            case '\r':
            case KEY_ENTER:
                if (selected == 0) {clear();return 1;}
                if (selected == 1) plug_and_test();
                if (selected == 2) return 3;
                break;
        }
    }
}
