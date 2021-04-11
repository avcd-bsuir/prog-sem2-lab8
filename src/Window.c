// License: CC BY-NC-SA 4.0
/*
 * Window.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "Window.h"

Window *window = NULL;

void updateWindow() {
    werase(window->decorator);
    werase(window->window);

    box(window->decorator, 0, 0);
    mvwprintw(window->decorator, 0, (getmaxx(window->decorator) - length(window->name)) / 2, "%ls", window->name);

    window->updateContents();

    wrefresh(window->decorator);
    wrefresh(window->window);

    int ret, inp;
    ret = wget_wch(window->window, &inp);

    Window *win = window;
    switch (inp) {
    case KEY_RESIZE:
        break;
    case KEY_ESC:
        window = window->parent;
        free(win);
        if (!window)
            shutdown();
        break;
    default:
        window->handleInput(ret, inp);
        break;
    }
}

void newWindow(int name[64], int x, int y, int w, int h, void (*updateContents)(), void (*handleInput)(int, int)) {
    Window *win = (Window *)malloc(sizeof(Window));
    if (!win)
        throwError(L"malloc() returned a null pointer");

    win->decorator = newwin(h, w, y, x);
    win->window = newwin(h - 2, w - 2, y + 1, x + 1);
    keypad(win->window, true);

    for (int i = 0; i < 64; i++)
        win->name[i] = 0;
    memcpy(win->name, name, 64 * sizeof(int));

    win->updateContents = updateContents;
    win->handleInput = handleInput;

    win->parent = window;
    window = win;
}
