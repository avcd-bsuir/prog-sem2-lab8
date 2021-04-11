// License: CC BY-NC-SA 4.0
/*
 * menu.h
 *
 * Binary trees.
 *
 * Written by AlexeyFilich
 * 02 apr 2021
 */

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

struct MenuOption {
    char text[64];
    void (*function)();
};
typedef struct MenuOption MenuOption;

MenuOption *menu_options = NULL;
int menu_options_size = 0;
int menu_choice = 0;

// Add new option to the menu
void menuAddOption(char text[], void (*function)()) {
    if (!menu_options) {
        menu_options = (MenuOption *)calloc(0, sizeof(MenuOption));
        if (!menu_options) {
            endwin();
            printf("calloc() returned a null pointer\n");
            exit(-1);
        }
    }
    menu_options = (MenuOption *)realloc(menu_options, (menu_options_size + 1) * sizeof(MenuOption));
    if (!menu_options) {
        endwin();
        printf("recalloc() returned a null pointer\n");
        exit(-1);
    }
    strcpy(menu_options[menu_options_size].text, text);
    menu_options[menu_options_size].function = function;
    menu_options_size++;
}

// Window updateContents() function
void UC_menu(Window *window) {
    werase(window->window);

    // Find max menu text length
    int max_menu = 0;
    for (int i = 0; i < menu_options_size; i++)
        if (strlen(menu_options[i].text) > max_menu)
            max_menu = strlen(menu_options[i].text);

    // Draw options in center of the window
    for (int i = 0; i < menu_options_size; i++) {
        mvwaddch(window->window, (getmaxy(window->window) - menu_options_size) / 2 + i, (getmaxx(window->window) - max_menu) / 2 - 2, (i == menu_choice ? '>' : ' ') | A_BLINK);
        if (menu_options[i].text[0] != '-') {
            wprintw(window->window, " %s", menu_options[i].text);
        } else {
            for (int j = 0; j < max_menu + 2; j++)
               wprintw(window->window, "-");
        }
    }

    wrefresh(window->window);
}

// Window handleInput() function
void HI_menu(int input, Window *window) {
    switch (input) {
    case KEY_UP:
        if (menu_choice)
            menu_choice--;
        if (menu_options[menu_choice].text[0] == '-')
            menu_choice--;
        break;
    case KEY_DOWN:
        if (menu_choice != menu_options_size - 1)
            menu_choice++;
        if (menu_options[menu_choice].text[0] == '-')
            menu_choice++;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        menu_options[menu_choice].function();
        break;
    default:
        break;
    }
}

#endif
