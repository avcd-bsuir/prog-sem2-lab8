// License: CC BY-NC-SA 4.0
/*
 * Menu.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef MENU_H
#define MENU_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Utils.h"
#include "Window.h"

struct MenuOption {
    int text[64];
    void (*function)();
};
typedef struct MenuOption MenuOption;

struct Menu {
    struct MenuOption *options;
    int options_size, choice, start, end;

    void (*addOption)(int[], void (*function)());
    void (*createWindow)();
};

extern struct Menu menu;

#endif
