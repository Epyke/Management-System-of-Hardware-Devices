#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

int insIniLista(ELEM **inicio, USER info)
{
    ELEM *new = NULL;
    new = (ELEM *)calloc(1, sizeof(ELEM));

    if (new == NULL)
    {
        printf("Out of memory\n");
        return -1;
    }

    new->info = info;
    new->seguinte = NULL;

    if (*inicio == NULL)
    {
        *inicio = new;
    }
    else
    {
        new->seguinte = *inicio;
        *inicio = new;
    }
    return 0;
}

ELEM *importUsers()
{
    FILE *fp = fopen("users.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    USER user;
    ELEM *inicio = NULL;

    while (!feof(fp))
    {
        fread(&user, sizeof(USER), 1, fp);
        insIniLista(&inicio, user);
    }
    fclose(fp);
    return inicio;
}

int registrar(char username[20], char password[20], ELEM *inicio)
{
    FILE *fp = fopen("users.bat", "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    USER user;

    strcpy(user.username, username);
    strcpy(user.password, password);
    user.state = 0;
    fwrite(&user, sizeof(USER), 1, fp);
    insIniLista(&inicio, user);
    printf("Pedido de incrição enviado com sucesso\n");
    fclose(fp);
    return 0;
}

int usernameVerif(char username[20], ELEM *inicio)
{
    ELEM *aux = NULL;

    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, username) == 0)
        {
            return 0;
        }
    }

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

        registrar(username, password, inicio);
    }
    return -1;
}

int passwordVerif(char username[20], char passwd[20], ELEM inicio)
{
    ELEM *aux = NULL;

    for (aux = &inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, username) == 0)
        {
            fprintf("Bem-vindo %s", username);
            return 0;
        }
    }
    printf("Username ou password incorreta\n");
    return -1;
}