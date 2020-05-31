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
    char keyword[100], message[100], encrypted[100];
    char response[100];

    printf("\n___________________________\n");
    printf("Welcome to Encrypt-A-Message");
    printf("\n___________________________\n");
    printf("Created by: James Hong 2020 ");
    printf("\n***************************\n");

    sleep(1);

    printf("\n#####Step1: Enter the non-numerical message to encrypt =>\n ");
    int messageCheck = checkInput(message);

    if (messageCheck < 2)
    {
        printf("\n#####Step2: Enter a non-numerical keyword used to encipher your message =>\n ");
        int keyCheck = checkInput(keyword);
        /* When both checks pass & session still alive, start encryption/decryption process*/
        if (keyCheck < 2)
        {
            encipher(message, keyword);

            printf("\n##### Would you like to decipher this message?: \n");
            printf("\n[Y or y] - Decipher this message");
            printf("\n[Anything else] - Quit Program\n");
            scanf("%s", response);

            int responseLower = tolower(response[0]);
            if (responseLower == 121)
            {
                printf("\nPlease enter the enciphered text: \n");
                int encCheck = checkInput(encrypted);
                if (encCheck < 2)
                {
                    decipher(encrypted, keyword);
                }
            }
        }
    }

    /* End the program*/
    printf("\n\tExiting program..\n");
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
    printf("\n\n*****Encipher*****");
    printf("\nmessage:  %s", message);
    printf("\nkey:      %s", key);
    printf("\nenc:      %s", encrypted);
}

void decipher(char encrypted[], char key[])
{
    // TODO

    //OUTPUT RESULTS
    printf("\n*****Decipher*****");
    printf("\nenc:      %s", encrypted);
    printf("\nkey:      %s", key);
    // printf("\nmessage:  %s", message);
}

int checkInput(char str[])
{
    int errCount = 0;
    int flag = 1;

    while (errCount < 2 && flag != 0)
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
                break;
            }
            else
            {
                /* Set flag to 0 and exit loop if no numbers found.*/
                flag = 0;
            }
        }
    }

    return errCount;
}