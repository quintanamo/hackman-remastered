#include <stdio.h>

#define SCREEN_LEFT_PAD "                "

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

int main(void) {
    printf("\x1B[2J\x1B[H");
    printf("\x1B[32m");
    draw_splash_screen();
    printf("\x1B[0m");
    return 0;
}
