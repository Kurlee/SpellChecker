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
//#include "dictionary.h"
#include <ctype.h>
#include <arpa/nameser.h>




char * str_to_lower(char *str);
char * str_to_lower(char *str)
{
    char *pNew1 = str;
    char *pNew2 = str;

    if(str != NULL) //NULL ?
    {
        if(strlen(str) != 0) //"" ?
        {
            while(*pNew1)
            {
                *pNew2 = tolower(*pNew1);
                ++pNew2;
                ++pNew1;
            }
            *pNew2 = '\0';

            return str;// return changed string
        }              // and prevent returning null to caller
    }
    return "";//Will never get here for non-null input argurment
}



char *rm_punct(char *str);
char *rm_punct(char *str) {
    if (str == NULL){
        return NULL;
    }
    char *p = str;
    char *t = str + strlen(str) - 1;
    while (ispunct(*p)) p++;
    while (ispunct(*t) && p < t) { *t = 0; t--; }
    /* also if you want to preserve the original address */
    { int i;
        for (i = 0; i <= t - p + 1; i++) {
            str[i] = p[i];
        } p = str; } /* --- */

    return p;
}



/**
 * Returns true if all words are spelled correcty, false otherwise. Array misspelled is populated with words that are misspelled.
 */
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    char *line_buff = malloc(45);     // String from file
    char *pos = 0;                  // position of newline character
    size_t line_buff_size = 0;  // size of string buffer
    ssize_t line_size;          // chars in string from file
    char * pch;
    int number_misspelled = 0;
    char * pch_copy;

    if (fp == NULL){
        exit(5);
    }

    line_size = getline(&line_buff, &line_buff_size, fp);

    while (line_size > 95){
        line_size = getline(&line_buff, &line_buff_size, fp);
    }
    if ((pos = strchr(line_buff, '\n')) != NULL)
        *pos = '\0';



    while (line_size >= 0) {

        // from line, get first word
        pch = strtok(line_buff," ");
        if (pch != NULL && strlen(pch) > LENGTH)
            pch = NULL;
        pch = rm_punct(pch);
        pch_copy = (char *)malloc((LENGTH+1)*sizeof(char));



        while (pch != NULL) {
            strcpy(pch_copy,pch);
            // check original word
            if (check_word(pch, hashtable)) {
                pch = strtok(NULL, " ");
                pch = rm_punct(pch);
                pch_copy = realloc(pch_copy,(LENGTH+1)*sizeof(char));
                //pch_copy = (char *)malloc((LENGTH+1)*sizeof(char));
            }
            // if not on list, check lowercase version
            else if (check_word(str_to_lower(pch), hashtable)) {
                pch = strtok(NULL, " ");
                pch = rm_punct(pch);
                pch_copy = realloc(pch_copy,(LENGTH+1)*sizeof(char));
                //pch_copy = (char *)malloc((LENGTH+1)*sizeof(char));
            }
            // else is not a word, add to misspelled and move onto next word
            else {
                //add_to_misspelled(number_misspelled, pch_copy, misspelled);
                misspelled[number_misspelled] = (char *)malloc((LENGTH+1)*sizeof(char));
                strcpy(misspelled[number_misspelled],pch);
                number_misspelled++;
                pch = strtok(NULL, " ");
                pch = rm_punct(pch);
                pch_copy = realloc(pch_copy,(LENGTH+1)*sizeof(char));
                //pch_copy = (char *)malloc((LENGTH+1)*sizeof(char));
            }
        }
        // Get next line in file and chomp newline
        line_size = getline(&line_buff, &line_buff_size, fp);
        while (line_size > 100){
            line_size = getline(&line_buff, &line_buff_size, fp);
        }
        if ((pos = strchr(line_buff, '\n')) != NULL)
            *pos = '\0';
    }
    free(pch_copy);
    return number_misspelled;
}

            



/**
 * Returns true if word is in dictionary else false.
 */
bool check_word(const char* word, hashmap_t hashtable[])
{
    int hashed = hash_function(word);       // hash value of word being passed in
    node * current = hashtable[hashed];     // current link in the list

    while(current != NULL){
        if (strcmp(word, current->word) == 0)
            return true;
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

        if (line_size > LENGTH+1){

            line_size = getline(&line_buff, &line_buff_size, dictionary_list);
            if ((pos = strchr(line_buff, '\n')) != NULL)
                *pos = '\0';
            continue;
        }
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
