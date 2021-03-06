// License: CC BY-NC-SA 4.0
/*
 * NodeViewRecursive.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODEVIEWRECURSIVE_H
#define NODEVIEWRECURSIVE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "NodeEdit.h"
#include "Utils.h"
#include "Window.h"

struct NodeViewRecursive {
    int choice, start, end, counter;
    int word[64], translation[64];
    void (*createWindow)();
};

extern struct NodeViewRecursive nodeViewRecursive;

#endif
