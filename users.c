#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

int registrar(char newUsername[20])
{
    FILE *fp = fopen("usersWaiting.txt", "w");
}

int usernameVerif(char username[20])
{
    FILE *fp = fopen("users.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    USER temp;
    int found = 0;

    while (!feof(fp))
    {
        fread(&temp, sizeof(USER), 1, fp);
        if (strcmp(temp.username, username) = 0)
        {
            found = 1;
            break;
        }
    }

    if (found == 1)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        printf("Este utilizador não existe, deseja enviar um pedido de criação?\n");
        printf("1 - SIM\n");
        print("0 - NÃO\n");
        int option;
        scanf("%d", &option);
        if (option == 1)
        {
            registrar(username);
            printf("Pedido de incrição enviado com sucesso\n");
        }
        return -1;
    }
}

int passwordVerif(char username[20], char passwd[20])
{
    FILE *fp = fopen("users.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    USER temp;
    int found = 0;

    while (!feof(fp))
    {
        fread(&temp, sizeof(USER), 1, fp);
        if (strcmp(temp.username, username) = 0 && strcmp(temp.password, passwd) = 0)
        {
            found = 1;
            break;
        }
    }

    if (found == 1)
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        printf("Username ou password incorreta\n");
        return -1;
    }
}