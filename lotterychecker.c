//definition of some error codes
#define ERROR_CODE 1
#define SUCCESS_CODE 0
#define MAX_NUMBER 39

//limits for file size and the amount of numbers you can have on each line
#define NUMBERS_SIZE 5
#define MAX_FILE_NAME_SIZE 255

//C libraries used for this project
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Parses through arguments provided and uses '-f' and '-n' to know when to take a file name or winning numbers respectively.
int parseArguments(int argc, char* argv[], int numbers[], char filename[]) {
    bool file_command = false;
    bool num_command = false;
    bool file = false;
    bool num = false;
    //Initiate the string to "  " to avoid potential garbage values.
    char number[3] = {' ', ' ', '\0'};
    int n = 0;
    int digits = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) file_command = true;
        else if (strcmp(argv[i], "-n") == 0) num_command = true;
        else if (file_command && num_command) {
            printf("There's something wrong with your input.\nA file input should be in the format [-f filename] without the brackets.\nThe 5 winning numbers input should be in the format [-n num1,num2,num3,num4,num5] without the brackets.\n");
            return ERROR_CODE;
        }
        else if (file_command) {
            if (strlen(argv[i]) > MAX_FILE_NAME_SIZE) {
                printf("File name size is too big. The length must be %d or less.", MAX_FILE_NAME_SIZE);
                return ERROR_CODE;
            }
            else {
                if (file) {
                    printf("You cannot pass more than one file as an argument.\n");
                    return ERROR_CODE;
                }
                else {
                    strcpy(filename, argv[i]);
                    file_command = false;
                    file = true;
                }
            }
        }
        else if (num_command) {
            for (int j = 0; j <= strlen(argv[i]); j++) {
                if (argv[i][j] > 47 && argv[i][j] < 58 && digits < 2) {
                    number[digits] = argv[i][j];
                    digits++;
                }
                else if (argv[i][j] > 47 && argv[i][j] < 58 && digits == 2) {
                    printf("Winning numbers can only be between 1 and 39 (inclusive).\n");
                    return ERROR_CODE;
                }
                else {
                    if (j == strlen(argv[i])) {
                        num_command = false;
                        num = true;
                    }
                    if (atoi(number) > 39 || atoi(number) < 1) {
                        printf("Winning numbers can only be between 1 and 39 (inclusive).\n");
                        return ERROR_CODE;
                    }
                    else {
                        if (n == 5) {
                            printf("You can only have 5 winning numbers.\n");
                            return ERROR_CODE;
                        }
                        else if (strcmp(number, "  ") != 0){
                            numbers[n] = atoi(number);
                            digits = 0;
                            n++;
                            number[0] = ' ';
                            number[1] = ' ';
                        }
                        else continue;
                    }
                }
            }
        }
        else continue;
    }
    if (!file) {
        printf("Please provide a file in the format [-f filename] without the brackets.\n");
        return ERROR_CODE;
    }
    if (!num) {
        printf("Please provide 5 winning numbers in the format [-n num1,num2,num3,num4,num5] without the brackets.\n");
        return ERROR_CODE;
    }
    if (n < 5) {
        printf("Please provide 5 winning numbers in the format [-n num1,num2,num3,num4,num5] without the brackets.\n");
        return ERROR_CODE;
    }
    return SUCCESS_CODE;
}

//Prints an error message for the user.
void userHelpInfo() {
  printf("An error has occured. Please read the above messages for clarification on what went wrong.\n");
}

//Goes through the file and inserts the numbers on each line according to their line and makes sure that limits are followed.
int readFile(char *filename, int numbers_to_check[][NUMBERS_SIZE], int* lines) {
    int numbers_checked = 0;
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("The file that you provided does not seem to exist. Please try again and make sure it is a .txt file.");
        return ERROR_CODE;
    }
    else {
        char line_of_numbers[100];
        //Initiate the string to "  " to avoid potential garbage values.
        char number[3] = {' ', ' ', '\0'};
        int n = 0;
        int digits = 0;
        while(fgets(line_of_numbers, 100, fptr)) {
            if (strcmp(line_of_numbers, "\n") == 0) continue;
            else {
                //Note: That extra boolean condition in the for loop is to take care of files that end right after the last number.
                //It makes sure that the last number gets checked.
                for (int i = 0; i < strlen(line_of_numbers) || strcmp(number, "  ") != 0; i++) {
                    if (line_of_numbers[i] > 47 && line_of_numbers[i] < 58 && digits < 2) {
                        number[digits] = line_of_numbers[i];
                        digits++;
                    }
                    else if (line_of_numbers[i] > 47 && line_of_numbers[i] < 58 && digits == 2 && line_of_numbers[i] != ' ') {
                        printf("Numbers in the file can only be between 1 and 39 (inclusive), and they must be in the format [num1 num2 num3 num4 num5] for each line (not including empty lines) without the brackets.\n");
                        return ERROR_CODE;
                    }
                    else {
                        int num = atoi(number);
                        if (num > 39 || num < 1) {
                            printf("Numbers in the file can only be between 1 and 39 (inclusive), and they must be in the format [num1 num2 num3 num4 num5] for each line (not including empty lines) without the brackets.\n");
                            return ERROR_CODE;
                        }
                        else {
                            if (n == 5) {
                                printf("You can only have 5 numbers per line in the file.\n");
                                return ERROR_CODE;
                            }
                            else {
                                for (int j = 0; j < 5; j++) {
                                    if (num == numbers_to_check[*lines][j]) {
                                        printf("The numbers on a single line of the file must be unique.\n");
                                        return ERROR_CODE;
                                    }
                                }
                                numbers_to_check[*lines][n] = num;
                                digits = 0;
                                n++;
                                number[0] = ' ';
                                number[1] = ' ';
                                numbers_checked++;
                            }
                        }
                    }
                }
                if (n < 5) {
                    printf("There needs to be at least 5 numbers per line in the file (not including empty lines).\n");
                    return ERROR_CODE;
                }
                *lines = *lines + 1;
                n = 0;
                if (*lines > 20) {
                    printf("There should only be 100 numbers total. 5 per line, so 20 lines total. This does not include empty lines.\n");
                    return ERROR_CODE;
                }
            }
        }
    }
    if (numbers_checked > 100) {
        printf("The file should only contain a minimum of 5 numbers and a maximum of 100 numbers. They must be in the format [num1 num2 num3 num4 num5] for each line (not including empty lines) without the brackets.\n");
        return ERROR_CODE;
    }
    return SUCCESS_CODE;
}

//Finds matches using the array that was used to store values from the file provided. A hashing technique is used here (an array with indexes to match a line is used).
void getMatches(int numbers_to_check[][NUMBERS_SIZE], int your_number_hash[], int matches_per_line[], int lines) {
    int n = 0;
    char set[255] = "{";
    char number[255];
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < NUMBERS_SIZE; j++) {
            if (your_number_hash[numbers_to_check[i][j]]) matches_per_line[i]++;
        }
    }
}

//Goes through the array that was used to store values from the file provided and prints the number sets with their respective matches.
void printWinners(int numbers_to_check[][NUMBERS_SIZE], int matches_per_line[], int lines) {
    for (int i = 5; i > 0; i--) {
        bool match_print = false;
        bool match_found = false;
        for (int j = 0; j < lines; j++) {
            if (matches_per_line[j] == i) {
                match_found = true;
                if (!match_print) {
                    if (i > 1) printf("%d matches: ", i);
                    else printf("1 match: ");
                    match_print = true;
                }
                for (int k = 0; k < 5; k++) {
                    if (k == 0) printf("{");
                    printf("%d", numbers_to_check[j][k]);
                    if (k < 4) printf(",");
                }
                printf("} ");
            }
            else continue;
        }
        if (match_found) {
            printf("\n");
            match_found = false;
        }
    }
}

//main function simply uses the functions specified above to do the heavy lifting.
int main(int argc, char* argv[]) {
    int numbers[NUMBERS_SIZE];
    char filename[MAX_FILE_NAME_SIZE];
    if (parseArguments(argc, argv, numbers, filename)) {
        userHelpInfo();
        return ERROR_CODE;
    }
    int your_numbers_hash[MAX_NUMBER + 1] = {0};
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        if (your_numbers_hash[numbers[i]] == 1) {
            printf("The 5 winning numbers must be unique. You have multiple %ds.\n", numbers[i]);
            userHelpInfo();
            return ERROR_CODE;
        } 
        else {
            your_numbers_hash[numbers[i]] = 1;
        }
    }
    int numbers_to_check[20][NUMBERS_SIZE];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < NUMBERS_SIZE; j++) {
            numbers_to_check[i][j] = -1;
        }
    }
    int n;
    int lines = 0;
    if ((n = readFile(filename, numbers_to_check, &lines)) == 1) {
        userHelpInfo();
        return ERROR_CODE;
    }
    int matches_per_line[lines];
    for (int i = 0; i < lines; i++) matches_per_line[i] = 0;
    getMatches(numbers_to_check, your_numbers_hash, matches_per_line, lines);
    printWinners(numbers_to_check, matches_per_line, lines);
    return 0;
}


