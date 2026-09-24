#ifndef WORD_LIST_H
#define WORD_LIST_H

#define MAX_WORD_LEN 32
#define MAX_WORDS 256

typedef struct {
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

int load_word_list(const char *path, WordList *list);
const char *pick_random_word(const WordList *list);

#endif
