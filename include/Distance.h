// License: CC BY-NC-SA 4.0
/*
 * Distance.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 13 apr 2021
 */

#ifndef DISTANCE_H
#define DISTANCE_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <stdlib.h>
#include <string.h>

#include "Node.h"
#include "Utils.h"
#include "Window.h"

struct Distance {
    int word1[64], word2[64];
    int option, word1_i, word2_i, output;
    void (*createWindow)();
};

extern struct Distance distance;

#endif
