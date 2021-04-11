// License: CC BY-NC-SA 4.0
/*
 * NodeViewNonRecursive.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODEVIEWNONRECURSIVE_H
#define NODEVIEWNONRECURSIVE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#ifndef MAIN
    #include "storage/Storage.h"
#endif

#include "Node.h"
#include "NodeEdit.h"
#include "Utils.h"
#include "Window.h"

struct NodeViewNonRecursive {
    int choice, start, end, counter;
    int word[64], translation[64];
    void (*createWindow)();
};

extern struct NodeViewNonRecursive nodeViewNonRecursive;

#endif
