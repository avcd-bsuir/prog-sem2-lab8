// License: CC BY-NC-SA 4.0
/*
 * NodeDeleteAll.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeDeleteAll.h"

/*
// Window updateContents() function
void UC_nodeDeleteAll(Window *window) {
    werase(window->window);

    wmove(window->window, 1, 0);
    wprintw(window->window, "   Are you sure you want to    delete the whole dictionary?");

    wmove(window->window, 4, 7);
    if (!nodeDeleteAll_option) {
        windowPrintAttr(window, "<NO>", A_STANDOUT);
        wprintw(window->window, "       <YES>");
    } else {
        wprintw(window->window, "<NO>       ");
        windowPrintAttr(window, "<YES>", A_STANDOUT);
    }

    wrefresh(window->window);
}
*/

void nodeDeleteAllUpdateContents() {
    wmove(window->window, 1, 3);
    wprintw(window->window, "%ls", L"Are you sure you want to    delete the whole dictionary?");

    wmove(window->window, 4, 7);
    if (!nodeDeleteAll.option) {
        windowPrintAttr(L"<NO>", A_STANDOUT);
        wprintw(window->window, "%ls", L"       <YES>");
    } else {
        wprintw(window->window, "%ls", L"<NO>       ");
        windowPrintAttr(L"<YES>", A_STANDOUT);
    }
}

void nodeDeleteAllHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_LEFT:
    case KEY_RIGHT:
        nodeDeleteAll.option = !nodeDeleteAll.option;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (nodeDeleteAll.option)
            deleteTree(&dictionary);
        window = window->parent;
        free(win);
        if (!window)
            shutdown();
        break;
    default:
        break;
    }
}

void nodeDeleteAllCreateWindow() {
    newWindow(L"Delete dictionary", (getmaxx(stdscr) - 32) / 2, (getmaxy(stdscr) - 7) / 2, 32, 7, nodeDeleteAllUpdateContents, nodeDeleteAllHandleInput);
    nodeDeleteAll.option = 0;
}

struct NodeDeleteAll nodeDeleteAll = {
    .option = 0,

    .createWindow = nodeDeleteAllCreateWindow
};
