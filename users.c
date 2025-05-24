#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"

#define USERFILE "data/users.dat"

/**
 * @brief Função que verifica se existe um perfil admin, na lista ligada cujo inicio é fornecido como parâmetro e no ficheiro users.bat.
 *  Se não existir nenhum perfil admin, a função insere um novo perfil admin com a password admin, na lista ligada e no ficheiro users.bat.
 *
 * @param inicio Apontador para o inicio da lista ligada.
 * @return int Retorna 0 se for executado com sucesso, retorna -1 se occorer um erro na abertura d
 */
int AdminSetup(ELEM_U **inicio)
{
    ELEM_U *aux = NULL;

    for (aux = *inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, "admin") == 0)
        {
            return 1;
        }
    }

    // Não existe perfil admin -> criação de um novo perfil
    FILE *fp = fopen(USERFILE, "ab");

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
    insIniLista(inicio, user);
    fclose(fp);
    return 0;
}

int writeChanges(ELEM_U *inicio)
{
    FILE *fp = fopen(USERFILE, "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    ELEM_U *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        fwrite(&aux->info, sizeof(USER), 1, fp);
        aux = aux->seguinte;
    }
    fclose(fp);
}

int AdminPasswordChange(ELEM_U *inicio)
{
    ELEM_U *aux = NULL;

    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, "admin") == 0 && aux->info.state == 1)
        {
            // Novo perfil admin
            char input[20];
            printf("Primeira sessao iniciada como admin, introduza uma nova senha\n");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';
            strcpy(aux->info.password, input);
            aux->info.state = 2;
            writeChanges(inicio);
            return 0;
        }
    }
    return -1;
}

int resetAdmin(ELEM_U **inicio)
{
    ELEM_U *aux = NULL;
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
        writeChanges(*inicio);

        return 0;
    }
    else
    {
        return -1;
    }
    printf("Conta admin reinicializada\n");
}

int insIniLista(ELEM_U **inicio, USER info)
{
    ELEM_U *new = NULL;
    new = (ELEM_U *)calloc(1, sizeof(ELEM_U));

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

ELEM_U *importUsers()
{
    FILE *fp = fopen(USERFILE, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }

    USER user;
    ELEM_U *inicio = NULL;
    int res = 0;

    while (!feof(fp))
    {
        res = fread(&user, sizeof(USER), 1, fp);
        if (res == 1)
        {
            insIniLista(&inicio, user);
        }
        else
        {
            break;
        }
    }

    fclose(fp);
    return inicio;
}

int usersRelease(ELEM_U **inicio)
{
    if (*inicio == NULL)
    {
        return -1;
    }
    ELEM_U *aux = NULL, *next = NULL;
    aux = *inicio;

    while (aux != NULL)
    {
        next = aux->seguinte;
        free(aux);
        aux = next;
    }
    *inicio = NULL;
    return 0;
}

int registrar(char username[], char password[], ELEM_U **inicio)
{

    FILE *fp = fopen(USERFILE, "ab");

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
    insIniLista(inicio, user);
    printf("Pedido de incricao enviado com sucesso\n");
    fclose(fp);
    return 0;
}

int usernameVerif(char username[], ELEM_U **inicio)
{
    ELEM_U *aux = NULL;

    for (aux = *inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.username, username) == 0)
        {

            if (aux->info.state == 0)
            {
                printf("O utilizador introduzido se encontra na lista de ativacao\n");
                return -1;
            }
            else if (aux->info.state == 1 || aux->info.state == 2)
            {
                return 0;
            }
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

int passwordVerif(char username[], char passwd[], ELEM_U inicio)
{
    ELEM_U *aux = NULL;

    for (aux = &inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.password, passwd) == 0 && (aux->info.state == 1 || aux->info.state == 2))
        {
            return 0;
        }
    }
    printf("Username ou password incorreta\n");
    return -1;
}

void printUtilizadores(ELEM_U *inicio)
{
    ELEM_U *aux = NULL;
    printf("--------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.state == 1 || aux->info.state == 0)
        {
            printf("%-20s | %-20s | %-2d \n", aux->info.username, aux->info.password, aux->info.state);
        }
    }
    printf("--------------------------------------------------------------------------------------------\n");
}

ELEM_U *procurarUserAtivo(ELEM_U *inicio, char username[])
{
    ELEM_U *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(username, aux->info.username) == 0 && aux->info.state == 1)
        {
            return aux;
            break;
        }
    }
    printf("Nenhum resultado encontrado, tente novamente\n");
    return NULL;
}

ELEM_U *procurarUser(ELEM_U *inicio, char username[])
{
    ELEM_U *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(username, aux->info.username) == 0 && (aux->info.state == 1 || aux->info.state == 0))
        {
            return aux;
            break;
        }
    }
    printf("Nenhum resultado encontrado, tente novamente\n");
    return NULL;
}

int ativarUtilizadores(ELEM_U *inicio, char username[])
{

    char input[20];

    ELEM_U *user = NULL;
    user = procurarUser(inicio, username);
    if (user == NULL)
    {
        return -1;
    }

    int input2;
    if (user->info.state == 0)
    {
        printf("Deseja ativar o utilizador %s ?\n", user->info.username);
        printf("1 - Ativar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &input2);
        getchar();

        switch (input2)
        {
        case 1:
            user->info.state = 1;
            break;
        default:
            break;
        }
    }
    else
    {

        printf("Deseja desativar o utilizador %s ?\n", user->info.username);
        printf("1 - Desativar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &input2);
        getchar();

        switch (input2)
        {
        case 1:
            user->info.state = 0;
            break;
        default:
            break;
        }
    }
    writeChanges(inicio);
    return 0;
}