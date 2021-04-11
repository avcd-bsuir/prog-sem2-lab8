// License: CC BY-NC-SA 4.0
/*
 * Utils.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 11 apr 2021
 */

#ifndef Error_H
#define Error_H

#define KEY_ESC 27
#define KEY_RETURN 10
#define NCURSES_WIDECHAR 1

#include <ncurses.h>
#include <stdlib.h>

void shutdown();

void throwError(int text[]);

int length(int text[]);

int compare(int a[64], int b[64]);

#endif
