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


/**
 * Returns true if all words are spelled correcty, false otherwise. Array misspelled is populated with words that are misspelled.
 */
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    char* buff[45];
    int number_misspelled = 0;
    while(fscanf(fp, "%s", buff)==1){
        if(!check_word(buff, hashtable)){
            misspelled[number_misspelled] = buff;
            number_misspelled++;
        }
    }
    return(!number_misspelled);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check_word(const char* word, hashmap_t hashtable[])
{
    int hashed = hash_function(word);
    node * current = hashtable[hashed];

    while(current != NULL){
        if (current->word == word)
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
    FILE *dictionary_list;
    char *line_buff = NULL;
    int hashed;
    size_t line_buff_size = 0;
    ssize_t line_size;
    struct node *head = NULL;
    struct node *current = NULL;


    if ((dictionary_list = fopen(dictionary_file, "r")) == NULL)
    {
        fprintf(stderr, " Error opening file\n");
        exit(1);
    }

    line_size = getline(&line_buff, &line_buff_size, dictionary_list);

    while (line_size >= 0)
    {
        hashed = hash_function(line_buff);
        head = hashtable[hashed];
        if (head == NULL){
            struct node* link = (struct node*)malloc(sizeof(struct node));
            strcpy(link->word, line_buff);
            link->next = head;
            head = link;
            continue;
        }
        while (current->next != NULL) {
            current = current->next;
        }

        strcpy(current->word, line_buff);
        line_size = getline(&line_buff, &line_buff_size, dictionary_list);
    }
    free(line_buff);
    line_buff = NULL;
    

    fclose(dictionary_list);
    return true;
}
