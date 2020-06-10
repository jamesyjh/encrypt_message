/**
 * File:    Assignment1_JamesHong.c
 *
 * Author:  James Hong (hongjame@sheridancollege.ca)
 * Term:    Spring / Summer 2020
 * Course:  PROG20799 - Data Structures and Algorithm Development - C
 *
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void encipher(char message[], char key[]);
void decipher(char encrypted[], char key[]);
int checkInput(char str[]);

int main() {
  int errCount = 0, responseLower;
  char keyword[100], message[100], encrypted[100];
  char response[100];

  printf("\033[1;33m");
  printf("\n-----------------------------\n");
  printf("\033[1;36m");
  printf("Welcome to Encrypt-A-Message");
  printf("\033[1;33m");
  printf("\n\n-----------------------------\n");
  printf("\033[1;36m");
  printf("Created by: James Hong 2020 ");
  printf("\033[1;33m");
  printf("\n\n***************************\n");

  sleep(1);

  printf("\033[1;36m");
  printf("\n##### Step1: Enter the NON-NUMERICAL message to encrypt:\n ");
  printf("\033[1;33m");
  /* Get user input and check for errors */
  errCount = checkInput(message);

  if (errCount < 2) {
    /* printf("%d", errCount); */
    printf("\033[1;36m");
    printf("\n##### Step2: Enter a NON-NUMERICAL keyword used to encipher your "
           "message:\n ");
    printf("\033[1;35m");
    errCount = checkInput(keyword);

    /* When both checks pass & session still alive, start encryption/decryption
     */
    if (errCount < 2) {
      /* printf("%d", errCount); */
      encipher(message, keyword);

      printf("\033[1;36m");
      printf("\n##### Step3(CHOOSE): Would you like to decipher this message?: "
             "\n");
      printf("\033[0m");
      printf("\n[Y or y] - Decipher this message");
      printf("\n[Anything else] - Quit Program\n");
      printf("=>: ");
      printf("\033[1;32m");
      scanf("%s", response);

      /* Normalize input to lowercase then check for 'y' or ascii number 121 */
      responseLower = tolower(response[0]);
      if (responseLower == 121) {
        printf("\033[1;36m");
        printf("\n##### Step4: Please enter the enciphered text: \n");
        printf("\033[1;31m");
        errCount = checkInput(encrypted);
        if (errCount < 2) {
          printf("\033[1;36m");
          printf("\n##### Step5: Please enter the key word: \n");
          printf("\033[1;35m");
          errCount = checkInput(keyword);
          if (errCount < 2)
            /* When all checks pass, begin deciphering encrypted message*/
            decipher(encrypted, keyword);
        }
      }
    }
  }

  /* End the program*/
  printf("\033[1;36m");
  printf("\n\nExiting program..\n\n");
  return 0;
}

/*
 * Function: encipher
 * ----------------------------
 *   Enciphers a raw message using a keyword then prints results
 *
 *   message: the raw message
 *   key: the keyword
 */
void encipher(char message[], char key[]) {
  /*cipher = (message + keyword) % 26*/

  int i, k;
  char messageConverted[100];
  char keyConverted[100];
  char keyRepeated[100];
  char encrypted[100];

  /* Encipher the message using the keyword */
  for (i = 0; i < strlen(message); i++) {
    if (key[i] != '\0') {
      messageConverted[i] = tolower(message[i]) - 97;
      keyConverted[i] = tolower(key[i]) - 97;
      encrypted[i] = (char)((messageConverted[i] + keyConverted[i]) % 26 + 97);
      /* printf("%c ", encrypted[i]); */
    }
  }

  /* Encipher the repeated portion of the message using the keyword*/
  k = 0;
  for (i = strlen(key); i < strlen(message); i++) {
    if (key[k] == '\0') {
      k = 0;
    }
    messageConverted[i] = tolower(message[i]) - 97;
    keyRepeated[i] = tolower(key[k]) - 97;
    encrypted[i] = (char)((messageConverted[i] + keyRepeated[i]) % 26 + 97);
    /* printf("%c ", encrypted[i]); */
    k++;
  }

  /* Terminate each string with a nul char '\0' */
  messageConverted[strlen(message)] = '\0';
  keyConverted[strlen(message)] = '\0';
  encrypted[strlen(message)] = '\0';
  keyRepeated[strlen(message)] = '\0';

  /* Display results */
  printf("\033[0m");
  printf("\n\n*****Encipher*****");
  printf("\nmessage:  \033[1;33m%s", message);
  printf("\033[0m");
  printf("\nkey:      \033[1;35m%s", key);
  printf("\033[1;32m");
  printf("\nenc:      \033[1;31m%s\n\n", encrypted);
}

/*
 * Function: decipher
 * ----------------------------
 *   Deciphers an encoded message to its original using a keyword
 *   and prints results
 *
 *   encrypted: the encrypted message
 *   key: the keyword
 */
void decipher(char encrypted[], char key[]) {

  int i, k;
  int decrypted[100] = {0};
  char message[100] = {0}, repeat[100] = {0};

  /* Decrypt encoded message as a function of key length */
  for (i = 0; i < strlen(key); i++) {
    if (encrypted[i] != '\0') {
      decrypted[i] =
          ((int)tolower(encrypted[i]) - 97) - ((int)tolower(key[i]) - 97);

      if (decrypted[i] < 0) {
        decrypted[i] += 26;
      }

      message[i] = (char)(decrypted[i] + 97);

      /* printf("%c ", message[i]); */
    }
  }

  /*
   * Decrypt the remaining encoded message as a function determined by
   * number of key repeats
   */

  for (i = strlen(key); i < strlen(encrypted); i++) {
    if (key[k] == '\0') {
      k = 0;
    }

    decrypted[i] =
        ((int)tolower(encrypted[i]) - 97) - ((int)tolower(key[k]) - 97);

    if (decrypted[i] < 0) {
      decrypted[i] += 26;
    }
    repeat[i] = (char)(decrypted[i] + 97);

    /* printf("%c ", repeat[i]); */
    k++;
    message[i] += repeat[i];
  }

  /* Display Results */
  printf("\033[0m");
  printf("\n\n*****Decipher*****");
  printf("\nenc:      \033[1;31m%s", encrypted);
  printf("\033[0m");
  printf("\nkey:      \033[1;35m%s", key);
  printf("\033[0m");
  printf("\033[1;32m");
  printf("\nmessage:  \033[1;33m%s\n", message);
}

/*
 * Function: checkInput
 * ----------------------------
 *   Returns an integer indicating number of accumulated input errors
 *   (ie. non-alpha characters)
 *
 *   str[]: string to be checked
 */
int checkInput(char str[]) {

  int passCheck = 0, errCount = 0, i;
  while (errCount < 2 && passCheck == 0) {

    printf("=>: ");
    scanf("%s", str);

    for (i = 0; i < strlen(str); i++) {
      /* Loop until number is found */
      if (isalpha(str[i]) == 0) {
        errCount += 1;
        printf(
            "Invalid input. Please only use non-numerical characters Aa-Zz.\n");
        printf("error count: %d attempts remaining.\n", 2 - errCount);
        passCheck = 0;
        break;
      } else {
        passCheck = 1;
      }
    }
  }

  return errCount;
}