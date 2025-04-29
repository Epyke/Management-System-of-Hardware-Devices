#include <stdio.h>
#include <string.h>
#include "users.h"

int loginMenu()
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

    int resU = usernameVerif(inputU);

    if (resU != 0)
    {
        return -1;
    }

    fgets(inputP, sizeof(inputP), stdin);
    inputP[strcspn(inputP, "\n")] = '\0';

    int resP = passwordVerif(inputU, inputP);
    if (resP != 0)
    {
        return -1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    do
    {
        res = loginMenu();
    } while (res != 0);
}
