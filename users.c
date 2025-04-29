#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

int AdminSetup(ELEM *inicio)
{
    ELEM *aux = NULL;

    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, "admin") == 0 && aux->info.state == 2)
        {
            // Existe perfil admin ativado
            return 2;
        }
        if (strcmp(aux->info.username, "admin") == 0 && aux->info.state == 1)
        {
            // Existe um perfil admin novo
            return 1;
        }
    }

    // Não existe perfil admin -> criação de um novo perfil
    FILE *fp = fopen("users.bat", "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    USER user;

    strcpy(user.username, "admin");
    strcpy(user.password, "admin");
    user.state = 1;
    fwrite(&user, sizeof(USER), 1, fp);
    insIniLista(&inicio, user);
    fclose(fp);
    return 0;
}

int AdminPasswordChange(ELEM *inicio)
{
    ELEM *aux = NULL;

    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, "admin") == 0 && aux->info.state == 1)
        {
            // Existe um perfil admin novo
            char input[20];
            printf("Primeira sessão iniciada como admin, introduza uma nova senha\n");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            strcpy(aux->info.password, input);

            FILE *fp = fopen("users.bat", "rb+");

            if (fp == NULL)
            {
                printf("Erro ao abrir o ficheiro\n");
                return -1;
            }

            USER temp;

            while (!feof(fp))
            {
                fread(&temp, sizeof(USER), 1, fp);
                if (strcmp(temp.username, "admin") == 0)
                {
                    strcpy(temp.password, input);
                    fwrite(&temp, sizeof(USER), 1, fp);
                    fclose(fp);
                    return 0;
                }
            }
            fclose(fp);
            return -1;
        }
    }
    return -1;
}

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
        return NULL;
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
    FILE *fp = fopen("users.bat", "ab");

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
    printf("Pedido de incricao enviado com sucesso\n");
    fclose(fp);
    return 0;
}

int usernameVerif(char username[20], ELEM *inicio)
{
    ELEM *aux = NULL;

    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, username) == 0 && aux->info.state == 1)
        {
            return 0;
        }
        if (strcmp(aux->info.username, username) == 0 && aux->info.state == 0)
        {
            printf("O utilizador introduzido se encontra na lista de ativacao\n");
            return -1;
        }
    }

    printf("Este utilizador nao existe, deseja enviar um pedido de criacao?\n");
    printf("1 - SIM\n");
    printf("0 - NAO\n");
    int option;
    scanf("%d", &option);
    getchar();
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
        if (strcmp(aux->info.password, passwd) == 0 && aux->info.state == 1)
        {
            return 0;
        }
    }
    printf("Username ou password incorreta\n");
    return -1;
}