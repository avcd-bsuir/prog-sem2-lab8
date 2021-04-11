// License: CC BY-NC-SA 4.0
/*
 * NodeAdd.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeAdd.h"

void nodeAddUpdateContents() {
    wmove(window->window, 1, 1);
    if (nodeAdd.option == 0) {
        windowPrintAttr(L"en:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"en: _______________________________________________________________");
    }

    wmove(window->window, 3, 1);
    if (nodeAdd.option == 1) {
        windowPrintAttr(L"ru:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"ru: _______________________________________________________________");
    }

    wmove(window->window, 5, 20);
    if (nodeAdd.option == 2)
        windowPrintAttr(L"<OK>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<OK>");

    wmove(window->window, 5, 42);
    if (nodeAdd.option == 3)
        windowPrintAttr(L"<CANCEL>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<CANCEL>");

    mvwprintw(window->window, 1, 5, "%ls", nodeAdd.word);
    mvwprintw(window->window, 3, 5, "%ls", nodeAdd.translation);
}

void nodeAddHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_UP:
    case KEY_LEFT:
        if (nodeAdd.option > 0)
            nodeAdd.option--;
        break;
    case KEY_RIGHT:
    case KEY_DOWN:
        if (nodeAdd.option < 3)
            nodeAdd.option++;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (nodeAdd.option == 2 || nodeAdd.option == 3) {
            if (nodeAdd.option == 2)
                pushNode(&dictionary, nodeAdd.word, nodeAdd.translation);
            window = window->parent;
            free(win);
            if (!window)
                shutdown();
        } else {
            nodeAdd.option++;
        }
    case KEY_BACKSPACE:
        if (nodeAdd.option == 0) {
            nodeAdd.word[nodeAdd.word_i] = 0;
            if (nodeAdd.word_i >= 0)
                nodeAdd.word_i--;
        } else if (nodeAdd.option == 1) {
            nodeAdd.translation[nodeAdd.translation_i] = 0;
            if (nodeAdd.translation_i >= 0)
                nodeAdd.translation_i--;
        }
        break;
    default:
        break;
    }

    if (nodeAdd.option == 0 && nodeAdd.word_i < 62 && ((inp >= L'a' && inp <= L'z') || (inp >= L'A' && inp <= L'Z'))) {
        nodeAdd.word[++nodeAdd.word_i] = inp;
        nodeAdd.word[nodeAdd.word_i + 1] = 0;
    }

    if (nodeAdd.option == 1 && nodeAdd.translation_i < 62 && ((inp >= L'а' && inp <= L'я') || (inp >= L'А' && inp <= L'Я'))) {
        nodeAdd.translation[++nodeAdd.translation_i] = inp;
        nodeAdd.translation[nodeAdd.translation_i + 1] = 0;
    }
}

void nodeAddCreateWindow() {
    newWindow(L"Add new word", (getmaxx(stdscr) - 71) / 2, (getmaxy(stdscr) - 8) / 2, 71, 8, nodeAddUpdateContents, nodeAddHandleInput);
    nodeAdd.option = 0;
    nodeAdd.word_i = -1;
    nodeAdd.translation_i = -1;
    for (int i = 0; i < 64; i++) {
        nodeAdd.word[i] = 0;
        nodeAdd.translation[i] = 0;
    }
}

struct NodeAdd nodeAdd = {
    .option = 0,
    .word_i = 0,
    .translation_i = 0,

    .createWindow = nodeAddCreateWindow
};
