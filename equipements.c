#include <stdio.h>
#include <stdlib.h>
#include "equipements.h"

int getEquipsNumb()
{
    FILE *fp = fopen("equips.bat", "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    int numb = ftell(fp) / sizeof(EQUIPE);
    fclose(fp);
    return numb;
}

int insIniLista(ELEM_E **inicio, EQUIPE info)
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
            insIniLista(&inicio, equip);
        }
        else
        {
            break;
        }
    }

    fclose(fp);
    return inicio;
}

int writeChanges(ELEM_E *inicio)
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

int registrar(EQUIPE equip, ELEM_E *inicio)
{

    FILE *fp = fopen("equips.bat", "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&equip, sizeof(EQUIPE), 1, fp);
    insIniLista(&inicio, equip);
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