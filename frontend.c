#include <stdio.h>
#include <string.h>
#include "users.h"

int loginMenu(ELEM *inicio)
{
    char inputU[20];
    char inputP[20];
    FILE *fp = fopen("users.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    printf("-----------------------------------WELCOME-----------------------------------\n");
    printf("Username: ");
    fgets(inputU, sizeof(inputU), stdin);
    inputU[strcspn(inputU, "\n")] = '\0';

    int resU = usernameVerif(inputU, inicio);

    if (resU != 0)
    {
        return -1;
    }

    printf("\nPassword: ");
    fgets(inputP, sizeof(inputP), stdin);
    inputP[strcspn(inputP, "\n")] = '\0';

    int resP = passwordVerif(inputU, inputP, *inicio);

    if (resP != 0)
    {
        return -1;
    }

    fprintf("Bem-vindo %s", inputU);
    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM *inicio = NULL;
    inicio = importUsers();
    do
    {
        res = loginMenu(inicio);
    } while (res != 0);
}
