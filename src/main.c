// License: CC BY-NC-SA 4.0
/*
 * main.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1
#define STORAGE_OPTIMAL

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menu.h"
#include "Node.h"
#include "Utils.h"
#include "Window.h"

#include "dictionary.h"

void print(Node *node) {
    if (node) {
        printf("{");
        print(node->left);
        if (node == dictionary.root)
            printf(":*%ls:", node->word);
        else
            printf(":%ls:", node->word);
        print(node->right);
        printf("}");
    }
}

int main(int argc, char *argv[]) {
    DICTIONARY_10;

    // Setup
    setlocale(LC_ALL, ""); // Support for cyrillic letters
    initscr();             // Init ncurses
    curs_set(0);           // Hide cursor
    keypad(stdscr, true);  // Enable easy keypad keys
    noecho();              // Disable echo

    // Create menu window
    menu.addOption(L"Hello", shutdown);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"View dictionary (recursive)", shutdown);
    menu.addOption(L"View dictionary (non-recursive)", shutdown);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"Exit", shutdown);
    menu.createWindow();

    // Update loop
    while (true)
        updateWindow();
}
//
//     // Root window
//     windowPush("Binary trees", 0, 0, cols, rows, &UC_menu, &HI_menu);
//
//     // Menu
//     menuAddOption("Add new word", &MENU_nodePush);
//     menuAddOption("Delete dictionary", &MENU_nodeDeleteAll);
//     menuAddOption("-", &cleanup);
//     menuAddOption("View recursive", &MENU_viewRecursive);
//     menuAddOption("View non-recursive", &MENU_viewNonRecursive);
//     // menuAddOption("View as tree", &MENU_viewNonRecursive);
//     menuAddOption("-", &cleanup);
//     menuAddOption("Exit", &cleanup);
//
//     // Dictionary
//     // DICTIONARY_10;
//     // DICTIONARY_200;
//
//     while (true) {
//         // Updating
//         windowTop()->updateContents(windowTop());
//
//         // Input handling
//         input = wgetch(windowTop()->window);
//         switch (input) {
//         case KEY_RESIZE:
//             break;
//         case KEY_ESC:
//             windowPop();
//             if (!window_stack)
//                 cleanup();
//             break;
//         default:
//             windowTop()->handleInput(input, windowTop());
//             break;
//         }
//         frame++;
//     }
//
//     return 0;
// }
