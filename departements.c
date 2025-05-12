#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "departements.h"

int getDepartsNumb(ELEM_D *inicio)
{
    if (inicio == NULL)
    {
        return 0;
    }

    ELEM_D *aux = NULL;
    aux = inicio;
    int count = 0;
    while (aux != NULL)
    {
        count++;
        aux = aux->seguinte;
    }

    return count;
}

int verifDepartNum(ELEM_D *inicio, int num)
{
    ELEM_D *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (aux->info.code == num)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    printf("Numero de departamento nao encontrado\n");
    return 0;
}

int VerificaNome(ELEM_D *inicio, char nome[])
{
    if (inicio == NULL)
    {
        return 0;
    }

    ELEM_D *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->info.name, nome) == 0)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

ELEM_D *procurarDepart(ELEM_D *inicio, int numero)
{

    ELEM_D *aux = NULL;
    int found = 0;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.code == numero)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        return aux;
    }
    else
    {
        printf("Nenhum utilizador encontrado, tente novamente\n");
        return NULL;
    }
}

int eliminarDepart(ELEM_D **inicio, int numero)
{
    ELEM_D *aux = NULL, *previous = NULL;
    aux = *inicio;
    while (aux != NULL)
    {
        if (aux->info.code == numero)
        {
            if (previous == NULL)
            {
                *inicio = aux->seguinte;
            }
            else
            {
                previous->seguinte = aux->seguinte;
            }
            free(aux);
            return 0;
        }
        previous = aux;
        aux = aux->seguinte;
    }

    printf("Nenhum resultado encontrado, tente novamente\n");
    return -1;
}

int insIniListaDeparts(ELEM_D **inicio, DEPART info)
{
    ELEM_D *new = NULL;
    new = (ELEM_D *)calloc(1, sizeof(ELEM_D));

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

ELEM_D *importDeparts()
{
    FILE *fp = fopen("departements.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }

    DEPART equip;
    ELEM_D *inicio = NULL;
    int res = 0;

    while (!feof(fp))
    {
        res = fread(&equip, sizeof(DEPART), 1, fp);
        if (res == 1)
        {
            insIniListaDeparts(&inicio, equip);
        }
        else
        {
            break;
        }
    }

    fclose(fp);
    return inicio;
}

int writeChangesDeparts(ELEM_D *inicio)
{
    FILE *fp = fopen("departements.bat", "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    ELEM_D *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        fwrite(&aux->info, sizeof(DEPART), 1, fp);
        aux = aux->seguinte;
    }
    fclose(fp);
}

int registrarDeparts(DEPART info, ELEM_D **inicio)
{

    if (VerificaNome(*inicio, info.name) == 1)
    {
        printf("Nome de departamento ja existente\n");
        return -1;
    }

    FILE *fp = fopen("departements.bat", "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&info, sizeof(DEPART), 1, fp);
    insIniListaDeparts(inicio, info);
    printf("Equipamento criado com sucesso\n");
    fclose(fp);
    return 0;
}

int departsRelease(ELEM_D **inicio)
{
    if (*inicio == NULL)
    {
        return -1;
    }
    ELEM_D *aux = NULL, *next = NULL;
    aux = *inicio;

    while (aux != NULL)
    {
        next = aux->seguinte;
        free(aux);
        aux = next;
    }
    *inicio = NULL;
}

void refreshDepartCodes(ELEM_D *inicio)
{
    int count = 1;
    ELEM_D *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        aux->info.code = count++;
    }
}

void printDeparts(ELEM_D *inicio)
{
    ELEM_D *aux = NULL;
    printf("------------------------------\n");
    printf("%-20s | %-10s \n", "NOME", "ID");
    printf("------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf("%-20s | %d \n", aux->info.name, aux->info.code);
    }
    printf("------------------------------\n");
}