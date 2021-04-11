char nodePush_word[MAX_WORD_SIZE], nodePush_description[2 * MAX_WORD_SIZE];
int nodePush_option, nodePush_last_input, nodePush_word_i, nodePush_description_i, nodePush_last_edited;

// Window updateContents() function
void UC_nodePush(Window *window) {
    werase(window->window);

    mvwprintw(window->window, 1, 1, "en: ________________________________");
    mvwprintw(window->window, 3, 1, "ru: ________________________________");
    wmove(window->window, 5, 11);
    if (!nodePush_option) {
        windowPrintAttr(window, "<OK>", A_STANDOUT);
        wprintw(window->window, "    <CANCEL>");
    } else {
        wprintw(window->window, "<OK>    ");
        windowPrintAttr(window, "<CANCEL>", A_STANDOUT);
    }

    mvwprintw(window->window, 1, 5, "%s", nodePush_word);
    mvwprintw(window->window, 3, 5, "%s", nodePush_description);

    wrefresh(window->window);
}

// Window handleInput() function
void HI_nodePush(int input, Window *window) {
    switch (input) {
    case KEY_LEFT:
    case KEY_RIGHT:
        nodePush_option = !nodePush_option;
        break;
    case KEY_ENTER:
    case KEY_RETURN:
        if (!nodePush_option)
            nodePush(&tree, nodePush_word, nodePush_description);
        windowPop();
        break;
    case KEY_BACKSPACE:
        if (!nodePush_last_edited) {
            if (!nodePush_word_i)
                break;
            nodePush_word[--nodePush_word_i] = '\0';
        } else {
            if (!nodePush_description_i)
                break;
            nodePush_description[--nodePush_description_i] = '\0';
            nodePush_description[--nodePush_description_i] = '\0';
        }
        break;
    default:
        break;
    }

    if (((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) && nodePush_word_i < MAX_WORD_SIZE) {
        nodePush_word[nodePush_word_i++] = input;
        nodePush_last_edited = 0;
    }

    if (nodePush_last_input != 0 && (input >= 176 || input <= 175) && nodePush_description_i < 2 * MAX_WORD_SIZE) {
        nodePush_description[nodePush_description_i++] = nodePush_last_input - 256;
        nodePush_description[nodePush_description_i++] = input - 256;
        nodePush_last_edited = 1;
    }

    if (input == 208 || input == 209)
        nodePush_last_input = input;
    else
        nodePush_last_input = 0;
}

// Menu function
void MENU_nodePush() {
    windowPush("Add new word", (cols - 40) / 2, (rows - 8) / 2, 40, 8, &UC_nodePush, &HI_nodePush);
    nodePush_option = 0;
    nodePush_word_i = 0;
    nodePush_description_i = 0;
    nodePush_last_edited = 0;
    for (int i = 0; i < MAX_WORD_SIZE; i++)
        nodePush_word[i] = '\0';
    for (int i = 0; i < 2 * MAX_WORD_SIZE; i++)
        nodePush_description[i] = '\0';
}
