#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void encipher(char message[], char key[]);
void decipher(char encrypted[], char key[]);
int checkInput(char str[]);

int main()
{
    int errCount = 0;
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
    errCount = checkInput(message);

    if (errCount < 2)
    {
        // printf("%d", errCount);
        printf("\033[1;36m");
        printf("\n##### Step2: Enter a NON-NUMERICAL keyword used to encipher your message:\n ");
        printf("\033[1;35m");
        errCount = checkInput(keyword);

        /* When both checks pass & session still alive, start encryption/decryption process*/
        if (errCount < 2)
        {
            // printf("%d", errCount);
            encipher(message, keyword);

            printf("\033[1;36m");
            printf("\n##### Step3(CHOOSE): Would you like to decipher this message?: \n");
            printf("\033[0m");
            printf("\n[Y or y] - Decipher this message");
            printf("\n[Anything else] - Quit Program\n");
            printf("=>: ");
            printf("\033[1;32m");
            scanf("%s", response);

            int responseLower = tolower(response[0]);
            if (responseLower == 121)
            {
                printf("\033[1;36m");
                printf("\n##### Step4: Please enter the enciphered text: \n");
                printf("\033[1;31m");
                errCount = checkInput(encrypted);
                if (errCount < 2)
                {
                    printf("\033[1;36m");
                    printf("\n##### Step5: Please enter the key word: \n");
                    printf("\033[1;35m");
                    errCount = checkInput(keyword);
                    if (errCount < 2)
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

void encipher(char message[], char key[])
{
    /*cipher = (message + keyword) % 26*/

    int i, k;
    char messageConverted[100];
    char keyConverted[100];
    char keyRepeated[100];
    char encrypted[100];

    //keyword
    for (i = 0; i < strlen(message); i++)
    {

        if (key[i] != '\0')
        {
            messageConverted[i] = tolower(message[i]) - 97;
            keyConverted[i] = tolower(key[i]) - 97;
            encrypted[i] = (char)((messageConverted[i] + keyConverted[i]) % 26) + 97;
            // printf("%c ", encrypted[i]);
        }
    }

    //keyword repeated
    k = 0;
    for (i = strlen(key); i < strlen(message); i++)
    {
        if (key[k] == '\0')
        {
            k = 0;
        }
        messageConverted[i] = tolower(message[i]) - 97;
        keyRepeated[i] = tolower(key[k] - 97);
        encrypted[i] = (char)((messageConverted[i] + keyRepeated[i]) % 26) + 97;
        // printf("%c ", encrypted[i]);
        k++;
    }

    // terminate each string with nul
    messageConverted[strlen(message)] = '\0';
    keyConverted[strlen(message)] = '\0';
    encrypted[strlen(message)] = '\0';
    keyRepeated[strlen(message)] = '\0';

    //OUTPUT RESULTS
    printf("\033[0m");
    printf("\n\n*****Encipher*****");
    printf("\nmessage:  \033[1;33m%s", message);
    printf("\033[0m");
    printf("\nkey:      \033[1;35m%s", key);
    printf("\033[1;32m");
    printf("\nenc:      \033[1;31m%s\n\n", encrypted);
}

void decipher(char encrypted[], char key[])
{

    int i, k;
    int decrypted[100] = {0};
    char message[100] = {0}, repeat[100] = {0};
    // TODO
    for (i = 0; i < strlen(key); i++)
    {
        if (encrypted[i] != '\0')
        {
            decrypted[i] = ((int)encrypted[i] - 97) - ((int)key[i] - 97);

            if (decrypted[i] < 0)
            {
                decrypted[i] += 26;
            }

            message[i] = (char)decrypted[i] + 97;

            // printf("%c ", message[i]);
        }
    }

    k = 0;
    for (i = strlen(key); i < strlen(encrypted); i++)
    {
        if (key[k] == '\0')
        {
            k = 0;
        }

        decrypted[i] = ((int)encrypted[i] - 97) - ((int)key[k] - 97);

        if (decrypted[i] < 0)
        {
            decrypted[i] += 26;
        }
        repeat[i] = (char)decrypted[i] + 97;

        // printf("%c ", repeat[i]);
        k++;
        message[i] += repeat[i];
    }

    //OUTPUT RESULTS
    printf("\033[0m");
    printf("\n\n*****Decipher*****");
    printf("\nenc:      \033[1;31m%s", encrypted);
    printf("\033[0m");
    printf("\nkey:      \033[1;35m%s", key);
    printf("\033[0m");
    printf("\033[1;32m");
    printf("\nmessage:  \033[1;33m%s\n", message);
}

int checkInput(char str[])
{

    int passCheck = 0, errCount = 0;
    while (errCount < 2 && passCheck == 0)
    {

        printf("=>: ");
        scanf("%s", str);

        for (int i = 0; i < strlen(str); i++)
        {
            /* Loop until number is found */
            if (isalpha(str[i]) == 0)
            {
                errCount += 1;
                printf("Invalid input. Please only use non-numerical characters Aa-Zz.\n");
                printf("error count: %d attempts remaining.\n", 2 - errCount);
                passCheck = 0;
                break;
            }
            else
            {
                passCheck = 1;
            }
        }
    }

    return errCount;
}