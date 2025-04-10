#include "GamaSaveinfo.h"
#include "utility.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME 200
#define MAX_PASSCODE_LENGTH 30
int main() {
  srand(time(NULL));
  int Account_Number = rand();
  char User_Name[MAX_NAME];
  char User_Name_Checker[MAX_NAME];

  char User_Passcode[MAX_PASSCODE_LENGTH];

  printf("Welcome to Gamasave, we offer quality service so we are happy to "
         "have you back\n");

  printf("User name");
  printf("-> ");
  fgets(User_Name, sizeof(User_Name), stdin);
  clear_buffer(); // This clears the remianing input that overflows.
  remove_newline(User_Name); // This removes the newline left in the stream.
  if (strlen(User_Name) >
      190) { // makes sure the user_name does not exceed 190 characters
    while (1) {
      printf("Name must not exceed 190\n");
      printf("What is your Name: ");
      fgets(User_Name, sizeof(User_Name), stdin);
      clear_buffer();
      printf("Indicator: %s\n", User_Name);
      if (strlen(User_Name) < 190) {
        break;
      }
    }
  }

  printf("What is your passcode: ");
  fgets(User_Passcode, sizeof(User_Passcode), stdin);
  remove_newline(User_Passcode);
  clear_buffer();
  printf("printing the lenght of User_Name: %lu\n", strlen(User_Passcode));

  if (strlen(User_Passcode) > 20) {
    while (1) {
      printf("Passcode must not exceed 20\n");
      printf("What is your passcode: ");
      fgets(User_Passcode, sizeof(User_Passcode), stdin);
      clear_buffer();
      printf("Indicator: %s\n", User_Passcode);
      if (strlen(User_Passcode) < 20) {
        break;
      }
    }
  }


  /* This part check if the user exists, if the user does
     not exist a folder will be created for the person
     in the Master_folder folder, so when ever and what
     you are doing bear it in mind that that folder is
     very essectial for this project.
  */
  
  FILE *User_Check;
  User_Check = fopen("User_Existence.txt", "r");
  if (User_Check == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    // I needed to use stdeer because it is an error stream and i used the
    // strerror so that we get human readable output will be gotten.
    return 1;
  }

  while (fgets(User_Name_Checker, sizeof(User_Name_Checker), User_Check) !=
         NULL) {
    remove_newline(User_Name_Checker);

    if ((strcmp(User_Name_Checker, User_Name)) == 0) {
      printf("user efef  name is %s\n", User_Name_Checker);
      printf("Welcome back what do you like to do? \n");
      Master_Folder(User_Name);
      fclose(User_Check);
      return 0;
    }
  }

  return 0;
}
