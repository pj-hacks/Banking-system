#include "GamaSaveinfo.h"
#include "utility.h"
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PATH_MAX 200
#define MAX_NAME 30
#define MAX_PASSCODE_LENGTH 15
int main(){

  // srand will constantly generate constant number
  /*This constant number will be feed to the if statement
    that handles the user creation process. and will be
    stored in the user file
  */
  
  srand(time(NULL));
  int Account_Number =rand();
  
  int Existence_Indicator;
  char User_Name[MAX_NAME];
  char User_Name_Checker[MAX_NAME];
  char User_Passcode[MAX_PASSCODE_LENGTH];

  printf(".........Welcome to Gamasave, a bank for you and not against you........\n");

  printf("Enter your username\n");
  printf("-> ");
  fgets(User_Name, sizeof(User_Name), stdin);
  clear_buffer(); // This clears the remianing input that overflows.
  remove_newline(User_Name); // This removes the newline left in the stream.
  if (strlen(User_Name) > 25) { // makes sure the user_name does not exceed 190 characters
    while (1) {
      printf("\nName must not exceed 190\n");
      printf("Reenter your name\n");
      printf("-> ");
      fgets(User_Name, sizeof(User_Name), stdin);
      clear_buffer();
      remove_newline(User_Name);
      if (strlen(User_Name) < 25) {
        break;
      }
    }
  }

  printf("\n\nWhat is your passcode\n");
  printf("-> ");
  fgets(User_Passcode, sizeof(User_Passcode), stdin);
  clear_buffer();
  remove_newline(User_Passcode);
  if (strlen(User_Passcode) > 8) {
    while (1) {
      printf("\nPasscode must not exceed 20\n");
      printf("Renter your passcode");
      printf("-> ");
      fgets(User_Passcode, sizeof(User_Passcode), stdin);
      clear_buffer();
      remove_newline(User_Passcode);
      if (strlen(User_Passcode) < 8) {
        break;  // runs only when the passcode is less than 20 character
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
      printf("Reconnecting to the database....\n");
      sleep(1);
      printf("Initializing hand shake>>\n");
      sleep(2);
      printf("Welcome back %s\n", User_Name);
      Existence_Indicator = 0;
      Master_Folder(User_Name);
      fclose(User_Check);
      return 0;
    }
    else{
      Existence_Indicator = 1;
      }
  }

    if(Existence_Indicator == 1){
      // Creation of files
      FILE *User_Creation;
      User_Creation = fopen("User_Existence.txt", "a+");
      if(User_Creation == NULL){
	fprintf(stderr, "Error opening file: %s\n", strerror(errno));
	fclose(User_Check);
	return 1;
      }
      // Create directory for the user
      char Directory_Path[PATH_MAX];
      snprintf(Directory_Path, sizeof(Directory_Path), "./Master_Folder/User/%s",User_Name);
       printf("Thanks for coming to pathner with us we have one of the best services\n");
       if(mkdir(Directory_Path, 0755) == 0){}
      else{
	perror("mkdir error");
	fclose(User_Creation);
	fclose(User_Check);
	return 1;
      }
       // write user name to user_existence.txt
      if(fprintf(User_Creation, "%s\n", User_Name)){
	printf("Your account number have been generated\n");
	printf("Account Number = %d\n", Account_Number);
	Master_Folder(User_Name);
       }
      fclose(User_Check);
      fclose(User_Creation);

      // Reusing the User_Creation pointer so that i can open and write to the user fiel
      char File_Path[PATH_MAX];
      snprintf(File_Path, sizeof(File_Path), "./Master_Folder/User/%s/Account_setting.txt",User_Name);
      User_Creation = fopen(File_Path, "w+");
      if(User_Creation == NULL){
	fprintf(stderr, "Error occured: %s\n", strerror(errno));
	return 1;
      }
      else{
	fprintf(User_Creation, "%d\n", Account_Number);
	fclose(User_Creation);
      }
    }
  

}
