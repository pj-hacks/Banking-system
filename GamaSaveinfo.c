
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
int Action_Sellection;

int Master_Folder(char *User_Name) {

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

  printf("0: Deposite Money\n");
  printf("1: Withdraw Money\n");
  printf("2: Transfer Money\n");
  printf("3: Change passord\n");
  printf("4: Change Passcode\n");
  printf("5: But data or Airtime\n");

  printf("What would you like to do:\n");
  printf("-> ");
  scanf("%d", &Action_Sellection);
  clear_buffer();

  switch (Action_Sellection) {
  case 0:
    // construct the full path
    snprintf(File_Path, sizeof(File_Path),
             "./Master_Folder/User/%s/Account.txt", User_Name);
    FILE *Deposite_Money;
    Deposite_Money = fopen(File_Path, "a+");
    if (Deposite_Money == NULL) {
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
      return 1;
    }

    printf("How much do you want to deposite\n");
    printf("-> ");
    scanf("%d", &Money);
    clear_buffer();

    while (fscanf(Deposite_Money, "%d", &Number) == 1) {
      Last_Number = Number; // loop updating and takes the last read integer
      // printf("money in the account is: %d\n", Last_Number);
    }

    fseek(Deposite_Money, 0, SEEK_END);
    Money = Last_Number +
            Money; // Add the last money int he account to the deposited money
    fprintf(Deposite_Money, "+%d\n",
            Money); // Writing to the file assosiated to Depasoted money
    printf("Account balance: %d\n", Money);
    fclose(Deposite_Money);
    break;

  case 1: // withdraw
    // construct the full path
    snprintf(File_Path, sizeof(File_Path),
             "./Master_Folder/User/%s/Account.txt ", User_Name);
    FILE *Withdraw_Money;
    Withdraw_Money = fopen(File_Path, "a+");
    if (Withdraw_Money == NULL) {
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }

    printf("How much do you want to withdraw\n");
    printf("-> ");
    scanf("%d", &Money);
    clear_buffer();

    while (fscanf(Withdraw_Money, "%d", &Number) == 1) {
      Last_Number = Number; // loop updating and takes the last read integer
      printf("money in the account is: %d\n", Last_Number);
    }
    fseek(Withdraw_Money, 0, SEEK_END);
    Money = Last_Number -
            Money; // Add the last money int he account to the deposited money
    fprintf(Withdraw_Money, "-%d\n",
            Money); // Writing to the file assosiated to Depasoted money
    printf("Account balance: %d\n", Money);
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
    printf("How much do you want to transfer\n");
    printf("-> ");
    scanf("%d", &Money);

    printf("Enter account number");
    printf("-> ");
    scanf("%d", &Last_Number);

    fprintf(Transfer_Money, "%d\n",
            Money); // Writing to the file assosiated to Depasoted money
    printf("Account balance: %d\n", Money);
    fclose(Transfer_Money);
    break;

  default:
    printf("Other features are not available.\b");
  }
  return 0;
}
