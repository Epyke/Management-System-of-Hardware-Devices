#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

int registrar(char username[20], char password[20])
{
    FILE *fp = fopen("users.bat", "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }
    USER user;
    user.username = username;
    user.password = password;
    user.state = 0;
    fwrite(&user, sizeof(USER), 1, fp);
    printf("Pedido de incrição enviado com sucesso\n");
    fclose(fp);
    return 0;
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
        printf("0 - NÃO\n");
        int option;
        scanf("%d", &option);
        if (option == 1)
        {
            printf("Introduza uma password de acesso\n");
            char password[20];
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = '\0';

            registrar(username, password);
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