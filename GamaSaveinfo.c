#include "GamaSaveinfo.h"
#include "utility.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// i declared this variables as global so that i wont have to repeat it's
// definition again.
int Money;
int Last_Number;
int Number;
long Account_Number;
int Account_Balance ;
int Action_Sellection = 1;

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
