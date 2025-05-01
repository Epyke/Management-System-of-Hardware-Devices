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
                    temp.state = 2;
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

int resetAdmin(ELEM **inicio)
{
    ELEM *aux = NULL;
    int flg = 0;
    for (aux = *inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, "admin") == 0 && aux->info.state == 2)
        {
            flg = 1;
            break;
        }
    }
    if (flg == 1)
    {
        aux->info.state = 1;
        strcpy(aux->info.password, "admin");

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
                strcpy(temp.password, "admin");
                temp.state = 1;
                fwrite(&temp, sizeof(USER), 1, fp);
                printf("Conta reiniciada com sucesso\n");
                fclose(fp);
                return 0;
            }
        }
        fclose(fp);
        return -1;
    }
    else
    {
        return -1;
    }
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

int usersRelease(ELEM **inicio)
{
    if (*inicio == NULL)
    {
        return -1;
    }
    ELEM *aux = NULL, *next = NULL;
    aux = *inicio;

    while (aux != NULL)
    {
        next = aux->seguinte;
        free(aux);
        aux = next;
    }
    *inicio = NULL;
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

void printUtilizadores(ELEM *inicio)
{
    ELEM *aux = NULL;
    printf("--------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf("%-20s | %-20s | %-2d \n", aux->info.username, aux->info.password, aux->info.state);
    }
    printf("--------------------------------------------------------------------------------------------\n");
}

int ativarUtilizadores(ELEM *inicio)
{
    char input[20];
    printUtilizadores(inicio);
    printf("\nIntroduza o nome de um utilizador: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    ELEM *aux = NULL;
    int count = 0;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strstr(aux->info.username, input))
        {
            count++;
        }
    }

    if (count > 1)
    {
        printf("--------------------------------------------------------------------------------------------\n");
        for (aux = inicio; aux != NULL; aux = aux->seguinte)
        {
            if (strstr(aux->info.username, input))
            {
                printf("%-20s | %-20s | %-2d \n", aux->info.username, aux->info.password, aux->info.state);
            }
        }
        printf("--------------------------------------------------------------------------------------------\n");
    }
    else if (count == 1)
    {
        for (aux = inicio; aux != NULL; aux = aux->seguinte)
        {
            if (strstr(aux->info.username, input))
            {
                break;
            }
        }

        int input2;
        if (aux->info.state = 0)
        {
            do
            {
                printf("Deseja ativar o utilizador %s ?\n");
                printf("1 - Ativar\n");
                printf("0 - Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &input2);
                getchar();

                switch (input2)
                {
                case 1:
                    aux->info.state = 1;
                    break;
                case 0:
                    break;
                default:
                    printf("\nValor introduzido incorreto, por favor tente novamente\n");
                    break;
                }
            } while (input2 != 0);
            return 0;
        }
        else
        {
            do
            {
                printf("Deseja desativar o utilziador %s ?\n");
                printf("1 - Desativar\n");
                printf("0 - Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &input2);
                getchar();

                switch (input2)
                {
                case 1:
                    aux->info.state = 0;
                    break;
                case 0:
                    break;
                default:
                    printf("\nValor introduzido incorreto, por favor tente novamente\n");
                    break;
                }
            } while (input2 != 0);
            return 0;
        }
    }
    return -1;
}