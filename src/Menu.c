// License: CC BY-NC-SA 4.0
/*
 * Menu.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "Menu.h"

void addOption(int text[64], void (*function)()) {
    menu.options = (MenuOption *)realloc(menu.options, (menu.options_size + 1) * sizeof(MenuOption));
    if (!menu.options)
        throwError(L"realloc() returned a null pointer");

    for (int i = 0; i < 64; i++)
        menu.options[menu.options_size].text[i] = 0;
    memcpy(menu.options[menu.options_size].text, text, 64 * sizeof(int));
    menu.options[menu.options_size].function = function;
    menu.options_size++;
}

void updateContents() {
    int max = 0, center_offset_x = 0, center_offset_y = 0;
    for (int i = 0; i < menu.options_size; i++)
        if (length(menu.options[i].text) > max)
            max = length(menu.options[i].text);
    center_offset_x = (getmaxx(window->window) - max) / 2 - 2;

    if (menu.options_size < getmaxy(window->window))
        center_offset_y = (getmaxy(window->window) - menu.options_size) / 2;

    for (int i = menu.start; i < menu.end && i < menu.options_size; i++) {
        mvwaddch(window->window, center_offset_y + i - menu.start, center_offset_x, (i == menu.choice ? '>' : ' ') | A_BLINK);
        if (menu.options[i].text[0] != L'-') {
            wprintw(window->window, " %ls", menu.options[i].text);
        } else {
            for (int j = 0; j < max + 2; j++)
               wprintw(window->window, "-");
        }
    }
}

void handleInput(int ret, int inp) {
    switch (inp) {
    case KEY_UP:
        if (menu.choice > 0) {
            if (menu.choice == menu.start) {
                menu.start--;
                menu.end--;
            }
            menu.choice--;
        }
        break;
    case KEY_DOWN:
        if (menu.choice < menu.options_size - 1) {
            if (menu.choice == menu.end - 1) {
                menu.start++;
                menu.end++;
            }
            menu.choice++;
        }
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        menu.options[menu.choice].function();
        break;
    default:
        break;
    }
    if (menu.options[menu.choice].text[0] == '-')
        handleInput(ret, inp);
}

void createWindow() {
    newWindow(L"Binary trees - menu", 0, 0, getmaxx(stdscr), getmaxy(stdscr), updateContents, handleInput);
    menu.choice = 0;
    menu.start = 0;
    menu.end = getmaxy(window->window);
}

struct Menu menu = {
    .options = NULL,
    .options_size = 0,
    .choice = 0,
    .start = 0,
    .end = 0,

    .addOption = addOption,
    .createWindow = createWindow
};
