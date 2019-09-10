//
//  main.c
//  SpellChecker
//
//  Created by admin on 9/4/19.
//  Copyright © 2019 Adrian Abdala. All rights reserved.
//

#include <stdio.h>
#include <errno.h>
#include <argp.h>
#include "spell.c"



struct arguments
{
    char *args[1];          // Arguments 1 and 2
    int verbose;            // -v verbosity flag
    char *dictionary_file;  // Reference file to set correctly spelled words
    char *checked_file;     // File to be compared against
    char *output_file;      // Optionally set file for output
};



static struct argp_option options[] =
        {
                {"verbose", 'v', 0, 0, "Produce verbose output"},
                {"dictionary_file", 'd', "../dictionary_file", 0, "Set Dictionary File"},
                {"checked_file", 'c', 0, 0, "Set checked file"},
                {"output_file", 'o', "output", 0, "Optionally set output file "},
                {0}
        };
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch(key) {
        case 'v':
            arguments->verbose = 1;
            break;
        case 'd':
            arguments->dictionary_file = arg;
            break;
        case 'c':
            arguments->checked_file = arg;
            break;
        case 'o':
            arguments->output_file = arg;
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {
                argp_usage(state);
            }
            arguments->args[state->arg_num] = arg;
            break;
        case ARGP_KEY_END:
            if (state->arg_num < 1) {
                argp_usage(state);
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}


// Documentation for required argument
static char args_doc[] = "DICT_FILE";

// Documentation purpose of program
static char doc[] = "A spell checker";

// Documentation optional flags
static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, const char ** argv) {

    struct arguments arguments;
    FILE *outstream;

    arguments.output_file = NULL;
    arguments.checked_file = NULL;
    arguments.verbose = 0;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.output_file)
        outstream = fopen(arguments.output_file, 'w');
    else
        outstream = stdout;

    if (arguments.output_file)
        fprintf(outstream, "dictionary file: %s\nChecked File: %s\n", arguments.args[0]);
    else
        fprintf(outstream, "dictionary file: %s\nNo Checked file passed", arguments.args[0], arguments.checked_file);

    if (arguments.verbose)
        printf("VERBOSE");

    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(arguments.args[0], hashtable);
    return 0;
}
