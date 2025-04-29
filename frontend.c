#include <stdio.h>
#include <string.h>
#include "users.h"

int loginMenu(ELEM *inicio)
{
    char inputU[20];
    char inputP[20];

    printf("\n-----------------------------------WELCOME-----------------------------------\n");
    printf("Escreva EXIT se pretender terminar o programa\n");
    printf("\nUsername: ");
    fgets(inputU, sizeof(inputU), stdin);
    inputU[strcspn(inputU, "\n")] = '\0';

    if (strcmp(inputU, "exit") == 0 || strcmp(inputU, "Exit") == 0 || strcmp(inputU, "EXIT") == 0)
    {
        return 0;
    }

    int resU = usernameVerif(inputU, inicio);

    if (resU != 0)
    {
        return -1;
    }

    printf("\nPassword: ");
    fgets(inputP, sizeof(inputP), stdin);
    inputP[strcspn(inputP, "\n")] = '\0';

    if (strcmp(inputP, "exit") == 0 || strcmp(inputP, "Exit") == 0 || strcmp(inputP, "EXIT") == 0)
    {
        return 0;
    }

    int resP = passwordVerif(inputU, inputP, *inicio);

    if (resP != 0)
    {
        return -1;
    }

    AdminPasswordChange(inicio);
    printf("Bem-vindo %s", inputU);

    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM *inicio = NULL;
    inicio = importUsers();
    AdminSetup(inicio);
    do
    {
        res = loginMenu(inicio);
    } while (res != 0);
}
