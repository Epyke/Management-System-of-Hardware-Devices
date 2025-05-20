#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "historico.h"

#define HISTORICOFILE "data/hisotrico.dat"

ELEM_H *importHistorico()
{
    FILE *fp = fopen(HISTORICOFILE, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }

    HISTORICO equip;
    ELEM_H *inicio = NULL;
    int res = 0;

    while (!feof(fp))
    {
        res = fread(&equip, sizeof(HISTORICO), 1, fp);
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

int insIniListaHistorico(ELEM_H **inicio, HISTORICO info)
{
    ELEM_H *new = NULL;
    new = (ELEM_H *)calloc(1, sizeof(ELEM_H));

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

int registrarHistorico(HISTORICO equip, ELEM_H **inicio)
{

    FILE *fp = fopen(HISTORICOFILE, "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&equip, sizeof(HISTORICO), 1, fp);
    insIniListaEquips(inicio, equip);
    printf("Historico registado com sucesso\n");
    fclose(fp);
    return 0;
}