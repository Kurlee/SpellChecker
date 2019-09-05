//
//  spell.c
//  SpellChecker
//
//  Created by admin on 9/4/19.
//  Copyright © 2019 Adrian Abdala. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "spell.h"
#include "AppSecAssignment1/dictionary.h"
#include "AppSecAssignment1/dictionary.c"

#define MAX_LETTERS_IN_WORD  26
#define MAX_WORDS_IN_DICTIONARY  124000


int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]);

/**
 * Returns true if word is in dictionary else false.
 */
bool check_word(const char* word, hashmap_t hashtable[]);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
    FILE * dictionary_list;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    if ((dictionary_list = fopen(dictionary_file, "r")) == NULL)
    {
        fprintf(stderr, " Error opening file");
        exit(1);
    }
    
    while ((read = getline(&line, &len, dictionary_list)) != -1)
    {
        printf("word: %s\n", line);
       // hashtable[i] = hash_function(line);
        i++;
    }

    fclose(dictionary_list);
    return true;
}
