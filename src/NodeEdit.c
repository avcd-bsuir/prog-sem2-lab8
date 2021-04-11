// License: CC BY-NC-SA 4.0
/*
 * NodeEdit.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#include "NodeEdit.h"

void nodeEditUpdateContents() {
    wmove(window->window, 1, 1);
    if (nodeEdit.option == 0) {
        windowPrintAttr(L"en:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"en: _______________________________________________________________");
    }

    wmove(window->window, 3, 1);
    if (nodeEdit.option == 1) {
        windowPrintAttr(L"ru:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"ru: _______________________________________________________________");
    }

    wmove(window->window, 5, 15);
    if (nodeEdit.option == 2)
        windowPrintAttr(L"<OK>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<OK>");

    wmove(window->window, 5, 29);
    if (nodeEdit.option == 3)
        windowPrintAttr(L"<DELETE>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<DELETE>");

    wmove(window->window, 5, 47);
    if (nodeEdit.option == 4)
        windowPrintAttr(L"<CANCEL>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<CANCEL>");

    mvwprintw(window->window, 1, 5, "%ls", nodeEdit.word);
    mvwprintw(window->window, 3, 5, "%ls", nodeEdit.translation);
}

void nodeEditHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_UP:
    case KEY_LEFT:
        if (nodeEdit.option > 0)
            nodeEdit.option--;
        break;
    case KEY_RIGHT:
    case KEY_DOWN:
        if (nodeEdit.option < 4)
            nodeEdit.option++;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (nodeEdit.option >= 2 && nodeEdit.option <= 4) {
            if (nodeEdit.option == 2) {
                deleteNode(&dictionary, nodeEdit.original_word);
                pushNode(&dictionary, nodeEdit.word, nodeEdit.translation);
            } else if (nodeEdit.option == 3) {
                deleteNode(&dictionary, nodeEdit.original_word);
            }
            window = window->parent;
            free(win);
            if (!window)
                shutdown();
        } else {
            nodeEdit.option++;
        }
    case KEY_BACKSPACE:
        if (nodeEdit.option == 0) {
            nodeEdit.word[nodeEdit.word_i] = 0;
            if (nodeEdit.word_i >= 0)
                nodeEdit.word_i--;
        } else if (nodeEdit.option == 1) {
            nodeEdit.translation[nodeEdit.translation_i] = 0;
            if (nodeEdit.translation_i >= 0)
                nodeEdit.translation_i--;
        }
        break;
    default:
        break;
    }

    if (nodeEdit.option == 0 && nodeEdit.word_i < 62 && ((inp >= L'a' && inp <= L'z') || (inp >= L'A' && inp <= L'Z'))) {
        nodeEdit.word[++nodeEdit.word_i] = inp;
        nodeEdit.word[nodeEdit.word_i + 1] = 0;
    }

    if (nodeEdit.option == 1 && nodeEdit.translation_i < 62 && ((inp >= L'а' && inp <= L'я') || (inp >= L'А' && inp <= L'Я'))) {
        nodeEdit.translation[++nodeEdit.translation_i] = inp;
        nodeEdit.translation[nodeEdit.translation_i + 1] = 0;
    }
}

void nodeEditCreateWindow() {
    newWindow(L"Edit", (getmaxx(stdscr) - 71) / 2, (getmaxy(stdscr) - 8) / 2, 71, 8, nodeEditUpdateContents, nodeEditHandleInput);
    nodeEdit.option = 0;
    memcpy(nodeEdit.original_word, nodeEdit.word, 64 * sizeof(int));
    nodeEdit.word_i = length(nodeEdit.word) - 1;
    nodeEdit.translation_i = length(nodeEdit.translation) - 1;
}

struct NodeEdit nodeEdit = {
    .option = 0,
    .word_i = 0,
    .translation_i = 0,

    .createWindow = nodeEditCreateWindow
};
