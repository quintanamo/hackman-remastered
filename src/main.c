#include <stdio.h>
#include <conio.h>
#include <dos.h>

#include "word_list.h"

#define SCREEN_LEFT_PAD "                "

static void set_cursor_visibility(int visible) {
    union REGS regs;

    regs.h.ah = 0x01;
    regs.h.ch = visible ? 0x0B : 0x20;
    regs.h.cl = 0x0F;
    int86(0x10, &regs, &regs);
}

void draw_splash_screen(void) {
    printf("\n");
    printf("\n");
    printf("\n");
    printf(SCREEN_LEFT_PAD "  _    _            _      __  __\n");
    printf(SCREEN_LEFT_PAD " | |  | |          | |    |  \\/  |\n");
    printf(SCREEN_LEFT_PAD " | |__| | __ _  ___| | __ | \\  / | __ _ _ __\n");
    printf(SCREEN_LEFT_PAD " |  __  |/ _` |/ __| |/ / | |\\/| |/ _` | '_ \\\n");
    printf(SCREEN_LEFT_PAD " | |  | | (_| | (__|   <  | |  | | (_| | | | |\n");
    printf(SCREEN_LEFT_PAD " |_|  |_|\\__,_|\\___|_|\\_\\ |_|  |_|\\__,_|_| |_|\n");
    printf(SCREEN_LEFT_PAD "                                  2026 Edition\n");
    printf("\n");
    printf("\n");
    printf(SCREEN_LEFT_PAD "            - Press SPACE to play -\n");
}

void draw_difficulty_selection(int selected) {
    const char *difficulty_labels[] = {
        "Easy",
        "Medium",
        "Hard"
    };
    int i;

    printf("\x1B[2J\x1B[H");
    printf("\n\n");
    printf(SCREEN_LEFT_PAD "Select Difficulty:\n");

    for (i = 0; i < 3; ++i) {
        printf(SCREEN_LEFT_PAD);
        if (i == selected) {
            printf("%s <\n", difficulty_labels[i]);
        } else {
            printf("%s\n", difficulty_labels[i]);
        }
    }
}

const char *load_selected_word(int difficulty) {
    static const char *paths[] = {
        "..\\words\\easy.txt",
        "..\\words\\medium.txt",
        "..\\words\\hard.txt"
    };
    static WordList list;
    static const char *selected_word = "";

    if (load_word_list(paths[difficulty], &list)) {
        selected_word = pick_random_word(&list);
        return selected_word;
    }

    return "";
}

int main(void) {
    int difficulty = 0;
    int key;
    const char *selected_word;

    printf("\x1B[2J\x1B[H"); // clear console
    printf("\x1B[32m"); // set color to green
    set_cursor_visibility(0); // hide cursor for splash screen

    draw_splash_screen();
    while (getch() != ' ') {
        // wait until the user presses SPACE to start the game
    }

    // handle setting the difficulty
    for (;;) {
        draw_difficulty_selection(difficulty);
        key = getch();
        if (key == 0 || key == 224) {
            key = getch();
            if (key == 72) {
                difficulty = (difficulty == 0) ? 2 : difficulty - 1;
            } else if (key == 80) {
                difficulty = (difficulty + 1) % 3;
            }
        } else if (key == 13) {
            break;
        }
    }

    printf("\x1B[2J\x1B[H"); // clear console
    
    // select a word based on the chosen difficulty
    selected_word = load_selected_word(difficulty);
    if (selected_word[0] != '\0') {
        printf(SCREEN_LEFT_PAD "Word: %s\n", selected_word);
    } else {
        printf(SCREEN_LEFT_PAD "Could not load words for the selected difficulty.\n");
    }

    while (getch() != ' ') {
        // wait until the user presses SPACE to start the game
    }

    set_cursor_visibility(1); // reset cursor
    printf("\x1B[0m"); // reset color
    printf("\x1B[2J\x1B[H"); // clear console
    return 0;
}
