#include "utility.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 200
#define MAX_PASSCODE_LENGTH 30
int main() {
  char User_Name[MAX_NAME];
  char User_Passcode[MAX_PASSCODE_LENGTH];

  printf("Welcome to Gamasave, we offer quality service so we are happy to "
         "have you back\n");

  printf("User name: ");
  fgets(User_Name, sizeof(User_Name), stdin);
  clear_buffer(); // used this function here so that User_name will not take more character than it is expected therby causing overflow in the system. In short in other to prevent overflow it have to be used.
  printf("printing the lenght of User_Name: %lu\n", strlen(User_Name));
  if (strlen(User_Name) > 190) { // makes sure the user_name does not exceed 190 characters
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

  FILE *User_Check;
  User_Check = fopen("User_Existence.txt", "r");
  if (User_Check == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    // I needed to use stdeer because it is an error stream and i used the strerror so that we get human readable output will be gotten.
  }
  while(fgets(User_Name_Checker, sizeof(User_Name_Checker), User_Check)){
    remove_newline(User_Name_Checker);
    if(strcmp(User_Name_Checker, User_Name) == 0){
      printf("Welcome back what do you like to do? \n);
      

  free(User_Check);

  return 0;
}
