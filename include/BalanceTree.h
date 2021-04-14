// License: CC BY-NC-SA 4.0
/*
 * BalanceTree.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#ifndef BALANCETREE_H
#define BALANCETREE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct BalanceTree {
    Node **nodes;
    int counter;
    void (*createWindow)();
};

extern struct BalanceTree balanceTree;

#endif
