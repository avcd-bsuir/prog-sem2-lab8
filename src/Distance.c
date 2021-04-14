// License: CC BY-NC-SA 4.0
/*
 * Distance.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#include "Distance.h"

void distanceFindDistance() {
    endwin();
    distance.output = 0;
    Node *node1 = dictionary.root, *node2 = dictionary.root;
    int cmp1 = compare(distance.word1, node1->word), cmp2 = compare(distance.word2, node2->word);
    while ((node1 && node2) && ((cmp1 > 0 && cmp2 > 0) || (cmp1 < 0 && cmp2 < 0))) {
        if (cmp1 > 0) {
            node1 = node1->right;
            node2 = node2->right;
        } else {
            node1 = node1->left;
            node2 = node2->left;
        }
        if (node1 && node2) {
            cmp1 = compare(distance.word1, node1->word);
            cmp2 = compare(distance.word2, node2->word);
        }
    }

    while (node1 && (cmp1 = compare(distance.word1, node1->word)) != 0) {
        distance.output++;
        if (cmp1 > 0)
            node1 = node1->right;
        else
            node1 = node1->left;
    }

    while (node2 && (cmp2 = compare(distance.word2, node2->word)) != 0) {
        distance.output++;
        if (cmp2 > 0)
            node2 = node2->right;
        else
            node2 = node2->left;
    }

    if (!node1 || !node2) {
        distance.output = -1;
        return;
    }
}

void distanceUpdateContents() {
    wmove(window->window, 1, 1);
    if (distance.option == 0) {
        windowPrintAttr(L"w1:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"w1: _______________________________________________________________");
    }

    wmove(window->window, 3, 1);
    if (distance.option == 1) {
        windowPrintAttr(L"w2:", A_STANDOUT);
        wprintw(window->window, "%ls", L" _______________________________________________________________");
    } else {
        wprintw(window->window, "%ls", L"w2: _______________________________________________________________");
    }

    wmove(window->window, 5, 1);
    wprintw(window->window, "Output: ");
    if (distance.output == -1) {
        wprintw(window->window, "one of the nodes does not exists");
    } else if (distance.output >= 0) {
        wprintw(window->window, "distance is %d", distance.output);
    }

    wmove(window->window, 7, 19);
    if (distance.option == 2)
        windowPrintAttr(L"<OK>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<OK>");

    wmove(window->window, 7, 44);
    if (distance.option == 3)
        windowPrintAttr(L"<BACK>", A_STANDOUT);
    else
        wprintw(window->window, "%ls", L"<BACK>");

    mvwprintw(window->window, 1, 5, "%ls", distance.word1);
    mvwprintw(window->window, 3, 5, "%ls", distance.word2);
}

void distanceHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_UP:
    case KEY_LEFT:
        if (distance.option > 0)
            distance.option--;
        break;
    case KEY_RIGHT:
    case KEY_DOWN:
        if (distance.option < 3)
            distance.option++;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (distance.option == 2) {
            distanceFindDistance();
        } else if (distance.option == 3) {
            window = window->parent;
            free(win);
            if (!window)
                shutdown();
        } else {
            distance.option++;
        }
    case KEY_BACKSPACE:
        if (distance.option == 0) {
            distance.word1[distance.word1_i] = 0;
            if (distance.word1_i >= 0)
                distance.word1_i--;
        } else if (distance.option == 1) {
            distance.word2[distance.word2_i] = 0;
            if (distance.word2_i >= 0)
                distance.word2_i--;
        }
        break;
    default:
        break;
    }

    if (distance.option == 0 && distance.word1_i < 62 && ((inp >= L'a' && inp <= L'z') || (inp >= L'A' && inp <= L'Z'))) {
        distance.word1[++distance.word1_i] = inp;
        distance.word1[distance.word1_i + 1] = 0;
    }

    if (distance.option == 1 && distance.word2_i < 62 && ((inp >= L'a' && inp <= L'z') || (inp >= L'A' && inp <= L'Z'))) {
        distance.word2[++distance.word2_i] = inp;
        distance.word2[distance.word2_i + 1] = 0;
    }
}

void distanceCreateWindow() {
    newWindow(L"Distance", (getmaxx(stdscr) - 71) / 2, (getmaxy(stdscr) - 10) / 2, 71, 10, distanceUpdateContents, distanceHandleInput);
    distance.option = 0;
    distance.word1_i = -1;
    distance.word2_i = -1;
    distance.output = -2;
    for (int i = 0; i < 64; i++) {
        distance.word1[i] = 0;
        distance.word2[i] = 0;
    }
}

struct Distance distance = {
    .option = 0,
    .word1_i = 0,
    .word2_i = 0,
    .output = -2,

    .createWindow = distanceCreateWindow
};
