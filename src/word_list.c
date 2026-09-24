#include "word_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void trim_line(char *text) {
    size_t len;

    if (text == NULL) {
        return;
    }

    len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r' || text[len - 1] == ' ' || text[len - 1] == '\t')) {
        text[len - 1] = '\0';
        --len;
    }
}

int load_word_list(const char *path, WordList *list) {
    FILE *file;
    char buffer[64];

    if (path == NULL || list == NULL) {
        return 0;
    }

    file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }

    list->count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (list->count >= MAX_WORDS) {
            break;
        }

        trim_line(buffer);
        if (buffer[0] == '\0') {
            continue;
        }

        strncpy(list->words[list->count], buffer, MAX_WORD_LEN - 1);
        list->words[list->count][MAX_WORD_LEN - 1] = '\0';
        ++list->count;
    }

    fclose(file);
    return (list->count > 0);
}

const char *pick_random_word(const WordList *list) {
    if (list == NULL || list->count <= 0) {
        return "";
    }

    srand((unsigned)time(NULL));
    return list->words[rand() % list->count];
}
