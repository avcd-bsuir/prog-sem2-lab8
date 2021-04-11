// License: CC BY-NC-SA 4.0
/*
 * NodeEdit.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef NODEEDIT_H
#define NODEEDIT_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct NodeEdit {
    int word[64], translation[64], original_word[64];
    int option, word_i, translation_i;
    void (*createWindow)();
};

extern struct NodeEdit nodeEdit;

#endif
