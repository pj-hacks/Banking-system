#include <stdio.h>
#include <string.h>
#include "utility.h"



void remove_newline(char *str)
{
  str[strcspn(str, "\n")] = 0;
}


void clear_screen()
{
#ifdef _WIN32
  system("cls");   // Windows
#else
  // ANSI escape code for Linux/macOS
  printf("\033[2J\033[H");
#endif
}


void clear_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ; // keep discarding until newline or end of file
}

