// License: CC BY-NC-SA 4.0
/*
 * EquationSolver.c
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 14 apr 2021
 */

#include "EquationSolver.h"

Node *equationSolverBuildTree(int start, int end) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        throwError(L"malloc() returned a null pointer");
    node->left = NULL;
    node->right = NULL;
    for (int i = 0; i < 64; i++)
        node->word[i] = 0;

    if (start >= end)
        return node;

    int bracket_counter = 0, lowest_priority_index = -1;

    while (equationSolver.equation[start] == L' ' || equationSolver.equation[start] == L'(' || equationSolver.equation[start] == L')')
        start++;

    while (equationSolver.equation[end - 1] == L' ' || equationSolver.equation[end - 1] == L'(' || equationSolver.equation[end - 1] == L')')
        end--;

    for (int i = start; i < end; i++) {
        switch (equationSolver.equation[i]) {
        case L'+':
        case L'-':
        case L'*':
        case L'/':
            if (!bracket_counter && ((equationSolver.equation[i] == L'+' || equationSolver.equation[i] == L'-') || ((equationSolver.equation[i] == L'*' || equationSolver.equation[i] == L'/') && lowest_priority_index == -1)))
                lowest_priority_index = i;
            break;
        case L'(':
            bracket_counter++;
            break;
        case L')':
            bracket_counter--;
            break;
        case L' ':
        case L'0' ... L'9':
            break;
        default:
            equationSolver.error = true;
            break;
        }
    }

    if (lowest_priority_index != -1) {
        node->word[0] = equationSolver.equation[lowest_priority_index];
        node->left = equationSolverBuildTree(start, lowest_priority_index);
        node->right = equationSolverBuildTree(lowest_priority_index + 1, end);
    } else {
        memcpy(node->word, equationSolver.equation + start, (end - start) * sizeof(int));
    }

    return node;
}

float equationSolverCalculate(Node *node) {
    if (node->word[0] == L'+' && node->word[1] == 0) {
        return equationSolverCalculate(node->left) + equationSolverCalculate(node->right);
    } else if (node->word[0] == L'-' && node->word[1] == 0) {
        return equationSolverCalculate(node->left) - equationSolverCalculate(node->right);
    } else if (node->word[0] == L'*' && node->word[1] == 0) {
        return equationSolverCalculate(node->left) * equationSolverCalculate(node->right);
    } else if (node->word[0] == L'/' && node->word[1] == 0) {
        return equationSolverCalculate(node->left) / equationSolverCalculate(node->right);
    } else {
        float temp = 0.0f;
        for (int i = 0; i < 64 && node->word[i] != 0; i++)
            temp = temp * 10 + node->word[i] - L'0';
        return temp;
    }
}

void equationSolverEvaluate() {
    deleteTree(&equation);

    equationSolver.error = false;
    equation.root = equationSolverBuildTree(0, equationSolver.i + 1);

    for (int i = 0; i < equationSolver.eq_length; i++)
        equationSolver.equation[i] = 0;
    equationSolver.i = -1;

    if (equationSolver.error)
        wprintw(window->window, "\nError!\n");
    else
        wprintw(window->window, "\n%f\n", equationSolverCalculate(equation.root));

    int x, y;
    getyx(window->window, y, x);
    equationSolver.y = y;

    for (int y = 0; y < getmaxy(window->window); y++)
        for (int x = 0; x < getmaxx(window->window); x++)
            equationSolver.screen_data[x + y * getmaxx(window->window)] = mvwinch(window->window, y, x);

    if (equationSolver.y > getmaxy(window->window) - 2) {
        equationSolver.y--;
        for (int i = 2 * getmaxx(window->window); i < getmaxx(window->window) * getmaxy(window->window); i++)
            equationSolver.screen_data[i - 2 * getmaxx(window->window)] = equationSolver.screen_data[i];
        for (int i = getmaxx(window->window) * getmaxy(window->window) - 2 * getmaxx(window->window); i < getmaxx(window->window) * getmaxy(window->window); i++)
            equationSolver.screen_data[i] = 0;
    }
}

void equationSolverUpdateContents() {
    wprintw(window->window, "%ls", equationSolver.screen_data);
    wmove(window->window, equationSolver.y, 0);
    wprintw(window->window, "> %ls", equationSolver.equation);
}

void equationSolverHandleInput(int ret, int inp) {
    Window *win = window;
    switch (inp) {
    case KEY_ENTER:
    case KEY_RETURN:
        equationSolverEvaluate();
        break;
    case KEY_BACKSPACE:
        equationSolver.equation[equationSolver.i] = 0;
        if (equationSolver.i >= 0)
            equationSolver.i--;
        break;
    case L'0' ... L'9':
    case L'+':
    case L'-':
    case L'*':
    case L'/':
    case L'(':
    case L')':
    case L' ':
        if (equationSolver.i < equationSolver.eq_length - 2) {
            equationSolver.equation[++equationSolver.i] = inp;
            equationSolver.equation[equationSolver.i + 1] = 0;
        }
        break;
    default:
        break;
    }
}

void equationSolverCreateWindow() {
    newWindow(L"Expression solver", 5, 5, getmaxx(stdscr) - 10, getmaxy(stdscr) - 10, equationSolverUpdateContents, equationSolverHandleInput);
    keypad(window->window, true);

    equationSolver.eq_length = getmaxx(window->window) - 2;
    equationSolver.i = -1;
    equationSolver.y = 0;
    equationSolver.error = false;

    if (equationSolver.eq_length)
        free(equationSolver.equation);
    equationSolver.equation = (int *)calloc(equationSolver.eq_length, sizeof(int));

    if (equationSolver.screen_data)
        free(equationSolver.screen_data);
    equationSolver.screen_data = (int *)calloc(getmaxx(window->window) * getmaxy(window->window), sizeof(int));
}

struct EquationSolver equationSolver = {
    .equation = NULL,
    .screen_data = NULL,
    .eq_length = 0,
    .i = -1,
    .y = 0,
    .error = false,

    .createWindow = equationSolverCreateWindow
};
