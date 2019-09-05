//
//  main.c
//  SpellChecker
//
//  Created by admin on 9/4/19.
//  Copyright © 2019 Adrian Abdala. All rights reserved.
//

#include <stdio.h>
#include "spell.c"

int main(int argc, const char * argv[]) {
    hashmap_t hashie;
    load_dictionary("dictionary_file", &hashie);
    return 0;
}
