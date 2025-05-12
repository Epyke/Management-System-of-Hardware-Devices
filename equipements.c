#include <stdio.h>
#include <stdlib.h>
#include "equipements.h"

int getEquipsNumb(ELEM_E *inicio)
{
    if (inicio == NULL)
    {
        return 0;
    }

    ELEM_E *aux = NULL;
    aux = inicio;
    int count = 0;
    while (aux != NULL)
    {
        count++;
        aux = aux->seguinte;
    }

    return count;
}

int verifNumSerie(ELEM_E *inicio, int num_serie)
{
    if (inicio == NULL)
    {
        return 0;
    }

    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (aux->info.num_serie == num_serie)
        {
            printf("Número de serie ja usado, tente novamente\n");
            return 1;
        }
        aux = aux->seguinte;
    }

    return 0;
}

int insIniListaEquips(ELEM_E **inicio, EQUIPE info)
{
    ELEM_E *new = NULL;
    new = (ELEM_E *)calloc(1, sizeof(ELEM_E));

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

ELEM_E *importEquips()
{
    FILE *fp = fopen("equips.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }

    EQUIPE equip;
    ELEM_E *inicio = NULL;
    int res = 0;

    while (!feof(fp))
    {
        res = fread(&equip, sizeof(EQUIPE), 1, fp);
        if (res == 1)
        {
            insIniListaEquips(&inicio, equip);
        }
        else
        {
            break;
        }
    }

    fclose(fp);
    return inicio;
}

int writeChangesEquips(ELEM_E *inicio)
{
    FILE *fp = fopen("equips.bat", "wb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        fwrite(&aux->info, sizeof(EQUIPE), 1, fp);
        aux = aux->seguinte;
    }
    fclose(fp);
}

int registrarEquips(EQUIPE equip, ELEM_E **inicio)
{

    FILE *fp = fopen("equips.bat", "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&equip, sizeof(EQUIPE), 1, fp);
    insIniListaEquips(inicio, equip);
    printf("Equipamento criado com sucesso\n");
    fclose(fp);
    return 0;
}

int equipsRelease(ELEM_E **inicio)
{
    if (*inicio == NULL)
    {
        return -1;
    }
    ELEM_E *aux = NULL, *next = NULL;
    aux = *inicio;

    while (aux != NULL)
    {
        next = aux->seguinte;
        free(aux);
        aux = next;
    }
    *inicio = NULL;
}

void printEquips(ELEM_E *inicio)
{
    ELEM_E *aux = NULL;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-11s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf("%-3d | %-31s | %-21s | %-21s | %-20d | %-11s | %-21s | %-3d \n", aux->info.id, aux->info.type, aux->info.brand, aux->info.model, aux->info.num_serie, aux->info.date, aux->info.state, aux->info.departement);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int eliminarEquip(ELEM_E **inicio, int numero)
{
    ELEM_E *aux = NULL, *previous = NULL;
    aux = *inicio;
    while (aux != NULL)
    {
        if (aux->info.id == numero)
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

ELEM_E *procurarEquip(ELEM_E *inicio, int numero)
{

    ELEM_E *aux = NULL;
    int found = 0;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == numero)
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
        printf("Nenhum equipamento encontrado, tente novamente\n");
        return NULL;
    }
}

void refreshEquipCodes(ELEM_E *inicio)
{
    int count = 1;
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        aux->info.id = count++;
    }
}