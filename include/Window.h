// License: CC BY-NC-SA 4.0
/*
 * Window.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef WINDOW_H
#define WINDOW_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "Utils.h"

struct Window {
    int name[64];
    WINDOW *window, *decorator;
    struct Window *parent;
    void (*updateContents)();
    void (*handleInput)(int, int);
};
typedef struct Window Window;

extern Window *window;

void updateWindow();

void newWindow(int name[64], int x, int y, int w, int h, void (*updateContents)(), void (*handleInput)(int, int));

#endif
