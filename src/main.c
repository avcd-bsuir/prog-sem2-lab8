// License: CC BY-NC-SA 4.0
/*
 * main.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#define MAIN
#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1
#define STORAGE_OPTIMAL

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BalanceTree.h"
#include "Distance.h"
#include "EquationSolver.h"
#include "Layers.h"
#include "Menu.h"
#include "Node.h"
#include "NodeAdd.h"
#include "NodeDeleteAll.h"
// #include "NodeEdit.h"
#include "NodeViewNonRecursive.h"
#include "NodeViewRecursive.h"
#include "NodeViewTree.h"
#include "Utils.h"
#include "Window.h"

#include "dictionary.h"

int main(int argc, char *argv[]) {
    DICTIONARY_10;
    // DICTIONARY_200;

    // Setup
    setlocale(LC_ALL, ""); // Support for cyrillic letters
    initscr();             // Init ncurses
    curs_set(0);           // Hide cursor
    keypad(stdscr, true);  // Enable easy keypad keys
    noecho();              // Disable echo

    // Create menu window
    menu.addOption(L"Add word", nodeAdd.createWindow);
    menu.addOption(L"Delete dictionary", nodeDeleteAll.createWindow);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"View dictionary (recursive)", nodeViewRecursive.createWindow);
    menu.addOption(L"View dictionary (non-recursive)", nodeViewNonRecursive.createWindow);
    menu.addOption(L"View dictionary (tree)", nodeViewTree.createWindow);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"Balance tree", balanceTree.createWindow);
    menu.addOption(L"View tree layer info", layers.createWindow);
    menu.addOption(L"Distance between two nodes", distance.createWindow);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"Evaluate expression", equationSolver.createWindow);
    menu.addOption(L"-", shutdown);
    menu.addOption(L"Exit", shutdown);
    menu.createWindow();

    // Update loop
    while (true)
        updateWindow();
}
