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

    char word[123132][26];
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
    FILE * dict = NULL;
    int i = 0;
    ssize_t read;
    size_t * len = 0;
    
    int max_word_length = 26;
    int line_buffer = 100;
    char ** words = (char **)malloc(sizeof(char *)*line_buffer);
    if (words == NULL)
    {
        fprintf( stderr, "Out of memory(1)\n" );
        exit(1);
    }
    if ((dict = fopen(dictionary_file, "r")) == NULL)
    {
        fprintf( stderr, "Error opening file");
        exit(2);
    }

    fclose(dict);
    
}

