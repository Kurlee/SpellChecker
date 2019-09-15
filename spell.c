//
//  spell.c
//  SpellChecker
//
//  Created by admin on 9/4/19.
//  Copyright © 2019 Adrian Abdala. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "spell.h"
#include "AppSecAssignment1/dictionary.h"
#include "AppSecAssignment1/dictionary.c"
#include <string.h>
#include <string.h>
#include <arpa/nameser.h>




/**
 * Returns true if all words are spelled correcty, false otherwise. Array misspelled is populated with words that are misspelled.
 */
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    char *line_buff = NULL;     // String from file
    char *pos = 0;                  // position of newline character
    size_t line_buff_size = 0;  // size of string buffer
    ssize_t line_size;          // chars in string from file
    char * pch;
    char str[] = "";
    size_t word_size = 0;          // chars in string from file
    int number_misspelled = 0;

    if (fp == NULL){
        exit(5);
    }

    line_size = getline(&line_buff, &line_buff_size, fp);
    if ((pos = strchr(line_buff, '\n')) != NULL)
        *pos = '\0';

    while (line_size >= 0) {

        // set index
        pch = strtok(line_buff," ,.=");
        while (pch != NULL) {
            if (check_word(pch, hashtable)) {
                continue;
            }
            else {
                misspelled[number_misspelled] = pch;
                number_misspelled++;
            }
        }
        // Get next line in file and chomp newline
        line_size = getline(&line_buff, &line_buff_size, fp);
        if ((pos = strchr(line_buff, '\n')) != NULL)
            *pos = '\0';
    }
    return number_misspelled;
}

            



/**
 * Returns true if word is in dictionary else false.
 */
bool check_word(const char* word, hashmap_t hashtable[])
{
    int hashed = hash_function(word);       // hash value of word being passed in
    node * current = hashtable[hashed];     // current link in the list

    // hash word to be compared to get main index of array
    //iterate through linked list comparing strings
    while(current != NULL){
        if (strcmp(word, current->word) == 0) {
            // return true if one of the links matches
            return true;
        }
        else
            current=current->next;
    }
    return false;
}




/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
    FILE *dictionary_list;      // File to read dictionary
    char *line_buff = NULL;     // String from file
    char *pos = 0;                  // position of newline character
    int hashed = 0;                 // hash value of string
    size_t line_buff_size = 0;  // size of string buffer
    ssize_t line_size;          // chars in string from file


    // open file
    if ((dictionary_list = fopen(dictionary_file, "r")) == NULL)
    {
        fprintf(stderr, " Error opening file\n");
        exit(1);
    }

    // read line and chomp newline
    line_size = getline(&line_buff, &line_buff_size, dictionary_list);
    if ((pos = strchr(line_buff, '\n')) != NULL)
        *pos = '\0';

    while (line_size >= 0) {

        // set index
        hashed = hash_function(line_buff);

        //init a node and allocate memory
        struct node *current = (struct node *) malloc(sizeof(struct node));
        // set data for node
        for (int i = 0; i < line_size; i++) {
            current->word[i] = line_buff[i];
        }
        // preappend node to linked list. This elimiates the need to find the end every time
        current->next = hashtable[hashed];
        hashtable[hashed] = current;



        // Get next line in file and chomp newline
        line_size = getline(&line_buff, &line_buff_size, dictionary_list);
        if ((pos = strchr(line_buff, '\n')) != NULL)
            *pos = '\0';
    }
    free(line_buff);
    fclose(dictionary_list);
    return true;
}
