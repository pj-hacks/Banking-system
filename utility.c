#include <stdio.h>
#include <string.h>
#include "utility.h"



void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void clear_buffer(){
    int c;
    while((c = getchar()) != '\n' );
}

