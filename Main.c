#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utility.h"

int Master_Folder(char *User_Name);
#define PATH_MAX 200
#define MAX_NAME 30
#define MAX_PASSCODE_LENGTH 15

// From the GamaSaveInfo.c file
 int Last_Number;
 int Number;
 int Action_Sellection;
 int Money;
 long Account_Number;
 int Account_Balance ;
int main(){

  // srand will constantly generate constant number
  /*This constant number will be feed to the if statement
    that handles the user creation process. and will be
    stored in the user file
  */
  
  srand(time(NULL));
  
  int Existence_Indicator = 1;
  char User_Name[MAX_NAME];
  char User_Name_Checker[MAX_NAME];
  char User_Passcode[MAX_PASSCODE_LENGTH];
  const char *Process[] = {"deposited", "withdrawed", "transfered", "chaged password"};

  printf(".........Welcome to Gamasave, a bank for you and not against you........\n");

  printf("Enter your username\n");
  printf("-> ");
  fgets(User_Name, sizeof(User_Name), stdin);
  clear_buffer(); // This clears the remianing input that overflows.
  remove_newline(User_Name); // This removes the newline left in the stream.
  if (strlen(User_Name) > 25) { // makes sure the user_name does not exceed 190 characters
    while (1) {
      printf("\nName must not exceed 25\n");
      printf("Retry\n");
      printf("-> ");
      fgets(User_Name, sizeof(User_Name), stdin);
      clear_buffer();
      remove_newline(User_Name);
      if (strlen(User_Name) < 25) {
        break;
      }
    }
  }

  printf("\nWhat is your passcode\n");
  printf("-> ");
  fgets(User_Passcode, sizeof(User_Passcode), stdin);
  clear_buffer();
  remove_newline(User_Passcode);
  if (strlen(User_Passcode) > 8) {
    while (1) {
      printf("\nPasscode must not exceed 8\n");
      printf("Retry");
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

  while (fgets(User_Name_Checker, MAX_NAME, User_Check) !=
         NULL) {
    remove_newline(User_Name_Checker);

    if ((strcmp(User_Name_Checker, User_Name)) == 0) {
      printf("\nWelcome back what do you like to do? \n");
      printf("Reconnecting to the database....\n");
      sleep(1);
      printf("Initializing hand shake>>>><<<<\n");
      sleep(2);
      printf("Welcome back %s\n", User_Name);
      Existence_Indicator = 0;
      Master_Folder(User_Name);
      fclose(User_Check);
      break;
    }
  }

    if(Existence_Indicator == 1){
      unsigned long New_User_Accout_Number =rand();
      // Creation of files
      FILE *User_Creation;
      User_Creation = fopen("User_Existence.txt", "a");
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
	printf("New_User_Account Number = %lu\n", New_User_Accout_Number);
	Master_Folder(User_Name);
       }
      fclose(User_Check);
      fclose(User_Creation);

      // Reusing the User_Creation pointer so that i can open
      //and write user account number to the user personal file
      char File_Path[PATH_MAX];
      snprintf(File_Path, sizeof(File_Path), "./Master_Folder/User/%s/Account_setting.txt",User_Name);
      User_Creation = fopen(File_Path, "w+");
      if(User_Creation == NULL){
	fprintf(stderr, "Error occured: %s\n", strerror(errno));
	return 1;
      }
      else{
	fprintf(User_Creation, "%lu\n", New_User_Accout_Number);
	fclose(User_Creation);
	Account_Number = 0;
      }
    }

     // Keeps record of all the activities done in the system
    FILE *Record_Keeping;
    Record_Keeping = fopen("General_Record.txt", "a");
    if(Record_Keeping == NULL){
      fprintf(stderr, "Encountered error: %s\n\n", strerror(errno));
      return 1;
    }

    // Controls the way the input is saved to the file General_Record.txt
    if(Action_Sellection >= 0 && Action_Sellection <= 3 && Existence_Indicator == 1 && Action_Sellection != 2){
      char Process_Initializer[strlen(Process[Action_Sellection] +1 )];
      strcpy(Process_Initializer, Process[Action_Sellection]);
      if(fprintf(Record_Keeping, "\n%s %s %d from %ld", User_Name,Process_Initializer, Money, Account_Number)){
	fclose(Record_Keeping);
      }
    }
    
    else if(Action_Sellection == 2){
      char Process_Initializer[strlen(Process[Action_Sellection] +1 )];
      strcpy(Process_Initializer, Process[Action_Sellection]);
      if(fprintf(Record_Keeping, "\n%s %s %d to %ld", User_Name,Process_Initializer, Money, Account_Number)){
	fclose(Record_Keeping);
      }
    }
    
    else if(Action_Sellection >= 5){
      printf("\nOperation not availabel\n");
      /*char Process_Initializer[strlen(Process[Action_Sellection] +1 )];
      strcpy(Process_Initializer, Process[Action_Sellection]);
      if(fprintf(Record_Keeping, "\n%s %s %d ", User_Name,Process_Initializer, Money)){
	fclose(Record_Keeping);
	}*/
    }

    return 0;
}





int Master_Folder(char *User_Name) {
  char Continuation_Flag;
  int While_Loop_controller = 1;
  /*Last number holds the last amount read
    from the file and number holds the number
    read from the file then saves it into the
    last_number.
  */
  char File_Path[PATH_MAX + 100]; // stores the full path
  /*Decision array was created so that
    i will not have to reteat
    "snprintf(File_Path, sizeof(File_Path), "%s/%s.txt", cwd, User_Name);"
  */
  while (While_Loop_controller) {

    printf("\n0: Deposit Money\n");
    printf("1: Withdraw Money\n");
    printf("2: Transfer Money\n");
    printf("3: Change password\n");
    printf("4: Change Pass-code\n");
    printf("5: Buy data or Airtime\n");
    printf("6: Exit\n");

    printf("What would you like to do:\n");
    printf("-> ");
    scanf(" %d", &Action_Sellection);
    clear_buffer();

    while (1) {
      if (Action_Sellection >= 5) {
        printf("Enter between 0 - 5\n");
        printf("-> ");
        scanf(" %d", &Action_Sellection);
        clear_buffer();
      } else {
        break;
      }
    }
    switch (Action_Sellection) {
    case 0: // Deposite
      // construct the full path
      snprintf(File_Path, sizeof(File_Path),
               "./Master_Folder/User/%s/Account.txt", User_Name);
      FILE *Deposite_Money;
      Deposite_Money = fopen(File_Path, "a+");
      if (Deposite_Money == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
      }

      Number = 0;
      Money = 0;
      Last_Number = 0;
      Account_Balance = 0;

      printf("\nHow much do you want to deposite\n");
      printf("-> ");
      scanf(" %d", &Money);
      clear_buffer();

      while (1) {
        if (Money < 1) {
          printf("\nAmount should not be less than 1\n");
          printf("Retry");
          printf("-> ");
          scanf(" %d", &Money);
          clear_buffer();
        } else {
          break;
        }
      }

      while (fscanf(Deposite_Money, "%d", &Number) == 1) {
        Last_Number = Number; // loop updating and takes the last read integer
        // printf("money in the account is: %d\n", Last_Number);
      }

      fseek(Deposite_Money, 0, SEEK_END);
      Account_Balance  = Last_Number +
              Money; // Add the last money int he account to the deposited money
      fprintf(Deposite_Money, "%d\n",
              Account_Balance); // Writing to the file assosiated to Depasoted money
      printf("Account balance: %d\n", Account_Balance);
      fclose(Deposite_Money);
      break;

    case 1: // withdraw
      // construct the full path
      snprintf(File_Path, sizeof(File_Path),
               "./Master_Folder/User/%s/Account.txt", User_Name);
      FILE *Withdraw_Money;
      Withdraw_Money = fopen(File_Path, "a+");
      if (Withdraw_Money == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
      }
      
      Number = 0;
      Money = 0;
      Last_Number = 0;
      Account_Balance = 0;

      printf("How much do you want to withdraw\n");
      printf("-> ");
      scanf(" %d", &Money);
      clear_buffer();

      while (fscanf(Withdraw_Money, "%d", &Number) == 1) {
        Last_Number = Number; // loop updating and takes the last read integer
      }

      while (1) {
        if (Money > Last_Number) {
          printf("\nAccount balance is low, enter between account range\n");
          printf("Account balance is %d\n", Last_Number);
          printf("Retry");
          printf("-> ");
          scanf(" %d", &Money);
          clear_buffer();
        } else if (Money < 1) {
          printf("\nAmount should not be less than 1\n");
          printf("Retry");
          printf("-> ");
          scanf(" %d", &Money);
          clear_buffer();
        } else {
          break;
        }
      }

      fseek(Withdraw_Money, 0, SEEK_END);
      Account_Balance  = Last_Number - Money; // subtracted the amount in the account with
                                   // the one that have been withdraeened
      fprintf(Withdraw_Money, "%d\n",
              Account_Balance); // Writing to the file assosiated to Depasoted money
      printf("\nAccount balance: %d\n", Account_Balance);
      fclose(Withdraw_Money);
      break;

    case 2:

      // construct the full path
      snprintf(File_Path, sizeof(File_Path),
               "./Master_Folder/User/%s/Account.txt", User_Name);
      FILE *Transfer_Money;
      Transfer_Money = fopen(File_Path, "a+");
      if (Transfer_Money == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
      }

      Number = 0;
      Money = 0;
      Last_Number = 0;
      Account_Balance = 0;

      printf("How much do you want to transfer\n");
      printf("-> ");
      scanf(" %d", &Money);

      printf("Enter account number");
      printf("-> ");
      scanf(" %lu", &Account_Number);

      while (fscanf(Transfer_Money, "%d", &Number) == 1) {
        Last_Number = Number; // loop updating and takes the last read integer
      }

      fseek(Transfer_Money, 0, SEEK_END);
      Account_Balance = Last_Number - Money; // Subtract the Amount remaining in the
                                   // account with the one transfered

      fprintf(Transfer_Money, "%d\n",
              Account_Balance); // Writing to the file assosiated to Depasoted money
      printf("Account balance: %d\n", Account_Balance);
      fclose(Transfer_Money);
      break;

    } // switch

    if (Action_Sellection <= 5) {
      printf("Do you want to continue (y or n): ");
      scanf(" %c", &Continuation_Flag);
      clear_buffer();

      // This loop make sure the user enter onlu (y or n)
      while (1) {
        if ((Continuation_Flag != 'n' && Continuation_Flag != 'N') &&
            (Continuation_Flag != 'y' && Continuation_Flag != 'Y')) {
          printf("\nPlease enter a valid character (y or n)\n");
          printf("Do you want to continue (y or n): ");
          scanf(" %c", &Continuation_Flag);
          clear_buffer();
          if (Continuation_Flag != 'n' || Continuation_Flag != 'N') {
            break;
          } else if (Continuation_Flag != 'y' || Continuation_Flag != 'Y') {
            break;
          } else {
            continue;
          }
        }
        break;
      }

      // This part of the code decide if the code will continue or end
      if (Continuation_Flag == 'y' || Continuation_Flag == 'Y') {
        While_Loop_controller = 1;
        continue;
      } else if (Continuation_Flag == 'n' || Continuation_Flag == 'N') {
        While_Loop_controller = 0;
        printf("\nThanks for working with us we are expecting to have you back "
               "later thanks\n");
        break;
      }
    }
  } // end of the control while statement

  return 0;
}

