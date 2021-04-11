// License: CC BY-NC-SA 4.0
/*
 * Window.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 02 apr 2021
 */

#ifndef WINDOW_H
#define WINDOW_H

struct Window {
    WINDOW *window, *window_decorator;
    char name[64];
    void (*updateContents)(struct Window *);
    void (*handleInput)(int, struct Window *);
};
typedef struct Window Window;

Stack *window_stack = NULL;

// Redraw window border and name
void windowRedrawDecorator(Window *window) {
    werase(window->window_decorator);
    box(window->window_decorator, 0, 0);
    mvwprintw(window->window_decorator, 0, (getmaxx(window->window) - strlen(window->name)) / 2 + 1, "%s", window->name);
    wrefresh(window->window_decorator);
}

// Add new window to the stack
void windowPush(char name[], int x, int y, int width, int height, void (*updateContents)(Window *), void (*handleInput)(int, struct Window *)) {
    Window *window = (Window *)malloc(sizeof(Window));
    strcpy(window->name, name);
    window->updateContents = updateContents;
    window->handleInput = handleInput;
    window->window_decorator = newwin(height, width, y, x);
    window->window = newwin(height - 2, width - 2, y + 1, x + 1);
    wtimeout(window->window, 500); // Set getch() lock time to 500ms
    keypad(window->window, true);  // Enable easy keypad keys
    windowRedrawDecorator(window);
    aStackPush(&window_stack, window);
}

// Remove top (current focused) window from stack
void windowPop() {
    aStackPop(&window_stack);
}

// Print string with attributes
void windowPrintAttr(Window *window, char str[], int attr) {
    int i = 0;
    while (str[i] != '\0') {
        waddch(window->window, str[i] | attr);
        i++;
    }
}

#define windowTop() ((Window *)aStackTop(&window_stack))

#endif
