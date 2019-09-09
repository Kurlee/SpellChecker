//
//  spell.c
//  SpellChecker
//
//  Created by admin on 9/4/19.
//  Copyright © 2019 Adrian Abdala. All rights reserved.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "spell.h"
#include "AppSecAssignment1/dictionary.h"
#include "AppSecAssignment1/dictionary.c"

#define MAX_LETTERS_IN_WORD  26
#include <string.h>
#include <string.h>
#define MAX_WORDS_IN_DICTIONARY  124000


//int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]);

/**
 * Returns true if word is in dictionary else false.
 */
//bool check_word(const char* word, hashmap_t hashtable[]);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
    FILE *dictionary_list;
    char *line_buff = NULL;
    int line_count = 0;
    size_t line_buff_size = 0;
    ssize_t line_size;
    node root;
    node link;
    

    if ((dictionary_list = fopen(dictionary_file, "r")) == NULL)
    {
        fprintf(stderr, " Error opening file\n");
        exit(1);
    }
    
    line_size = getline(&line_buff, &line_buff_size, dictionary_list);
    
    while (line_size >= 0)
    {
        printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count, line_size, line_buff_size, line_buff);
        strcpy(root.word, line_buff);
        root.next = &link;
        hashtable[line_count] = &root;
        line_count = line_count + 1;

        line_size = getline(&line_buff, &line_buff_size, dictionary_list);
        
    }
    free(line_buff);
    line_buff = NULL;
    

    fclose(dictionary_list);
    return true;
}
