int main() {
    srand(time(NULL));
    int Account_Number = rand();
    int Existence_Indicator = 1;
    char User_Name[MAX_NAME] = {0};
    char User_Name_Checker[MAX_NAME] = {0};
    char User_Passcode[MAX_PASSCODE_LENGTH] = {0};
    char *Process[] = {"deposited", "withdrawn", "transferred", "changed password"};
    
    // Initialize external variables
    Last_Number = 0;
    Number = 0;
    Action_Sellection = -1;
    Money = 0;

    printf(".........Welcome to Gamasave, a bank for you and not against you........\n");

    printf("Enter your username\n-> ");
    fgets(User_Name, sizeof(User_Name), stdin);
    clear_buffer();
    remove_newline(User_Name);
    if (strlen(User_Name) >= MAX_NAME - 1) {
        while (1) {
            printf("\nName must not exceed %d characters\n", MAX_NAME - 1);
            printf("Retry\n-> ");
            fgets(User_Name, sizeof(User_Name), stdin);
            clear_buffer();
            remove_newline(User_Name);
            if (strlen(User_Name) < MAX_NAME - 1) {
                break;
            }
        }
    }

    printf("\nWhat is your passcode\n-> ");
    fgets(User_Passcode, sizeof(User_Passcode), stdin);
    clear_buffer();
    remove_newline(User_Passcode);
    if (strlen(User_Passcode) > 8 || strlen(User_Passcode) == 0) {
        while (1) {
            printf("\nPasscode must be 1 to 8 characters\n");
            printf("Retry\n-> ");
            fgets(User_Passcode, sizeof(User_Passcode), stdin);
            clear_buffer();
            remove_newline(User_Passcode);
            if (strlen(User_Passcode) <= 8 && strlen(User_Passcode) > 0) {
                break;
            }
        }
    }

    FILE *User_Check = fopen("User_Existence.txt", "r");
    if (User_Check == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    while (fgets(User_Name_Checker, MAX_NAME, User_Check) != NULL) {
        remove_newline(User_Name_Checker);
        if (strcmp(User_Name_Checker, User_Name) == 0) {
            printf("\nWelcome back, what would you like to do?\n");
            printf("Reconnecting to the database....\n");
            Existence_Indicator = 0;
            Master_Folder(User_Name);
            fclose(User_Check);
            break;
        }
    }

    if (Existence_Indicator == 1) {
        FILE *User_Creation = fopen("User_Existence.txt", "a");
        if (User_Creation == NULL) {
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            fclose(User_Check);
            return 1;
        }

        char Directory_Path[PATH_MAX];
        snprintf(Directory_Path, sizeof(Directory_Path), "./Master_Folder/User/%s", User_Name);
        printf("Thanks for choosing to partner with us. We offer some of the best services!\n");
        if (mkdir("./Master_Folder/User", 0755) != 0 && errno != EEXIST) {
            fprintf(stderr, "Failed to create parent directory: %s\n", strerror(errno));
            fclose(User_Creation);
            fclose(User_Check);
            return 1;
        }
        if (mkdir(Directory_Path, 0755) != 0 && errno != EEXIST) {
            fprintf(stderr, "Failed to create user directory: %s\n", strerror(errno));
            fclose(User_Creation);
            fclose(User_Check);
            return 1;
        }

        fprintf(User_Creation, "%s\n", User_Name);
        printf("Your account number has been generated\n");
        printf("Account Number = %d\n", Account_Number);
        fclose(User_Creation);
        fclose(User_Check);

        char File_Path[PATH_MAX];
        snprintf(File_Path, sizeof(File_Path), "./Master_Folder/User/%s/Account_setting.txt", User_Name);
        User_Creation = fopen(File_Path, "w+");
        if (User_Creation == NULL) {
            fprintf(stderr, "Error occurred: %s\n", strerror(errno));
            return 1;
        }
        fprintf(User_Creation, "%d\n%s\n", Account_Number, User_Passcode);
        fclose(User_Creation);
    }

    FILE *Record_Keeping = fopen("General_Record.txt", "a");
    if (Record_Keeping == NULL) {
        fprintf(stderr, "Encountered error: %s\n", strerror(errno));
        return 1;
    }
    if (Action_Sellection >= 0 && Action_Sellection < 4 && Existence_Indicator == 1 && Action_Sellection != 2) {
        char Process_Initializer[strlen(Process[Action_Sellection]) + 1];
        strcpy(Process_Initializer, Process[Action_Sellection]);
        fprintf(Record_Keeping, "\n%s %s %d from %d", User_Name, Process_Initializer, Money, Account_Number);
    } else if (Action_Sellection == 2 && Existence_Indicator == 1) {
        char Process_Initializer[strlen(Process[Action_Sellection]) + 1];
        strcpy(Process_Initializer, Process[Action_Sellection]);
        fprintf(Record_Keeping, "\n%s %s %d to %d", User_Name, Process_Initializer, Money, Last_Number);
    } else if (Action_Sellection >= 4) {
        printf("\nOperation not available\n");
    }
    fclose(Record_Keeping);

    return 0;
}
