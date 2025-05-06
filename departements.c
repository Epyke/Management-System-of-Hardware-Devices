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
    int count = 0;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        count++;
    }

    return count;
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

int registrarDeparts(DEPART equip, ELEM_D **inicio)
{

    FILE *fp = fopen("departements.bat", "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&equip, sizeof(DEPART), 1, fp);
    insIniListaDeparts(inicio, equip);
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

void printDeparts(ELEM_D *inicio)
{
    ELEM_D *aux = NULL;
    printf("--------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf("%-20s | %d \n", aux->info.name, aux->info.code);
    }
    printf("--------------------------------------------------------------------------------------------\n");
}