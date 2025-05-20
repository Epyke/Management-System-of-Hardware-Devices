#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "historico.h"

#define HISTORICOFILE "data/historico.dat"

ELEM_H *importHistorico()
{
    FILE *fp = fopen(HISTORICOFILE, "rb");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return NULL;
    }

    HISTORICO historico;
    ELEM_H *inicio = NULL;
    int res = 0;

    while (!feof(fp))
    {
        res = fread(&historico, sizeof(HISTORICO), 1, fp);
        if (res == 1)
        {
            insIniListaHistorico(&inicio, historico);
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

int registrarHistorico(HISTORICO historico, ELEM_H **inicio)
{

    FILE *fp = fopen(HISTORICOFILE, "ab");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    fwrite(&historico, sizeof(HISTORICO), 1, fp);
    insIniListaHistorico(inicio, historico);
    printf("Historico registado com sucesso\n");
    fclose(fp);
    return 0;
}

void printHistorico(ELEM_H *inicio)
{
    ELEM_H *aux = NULL;

    printf("----------------------------------------------------------------------------HISTORICO---------------------------------------------------------------------------------------\n");
    printf("%-20s | %-50s | %-10s \n", "TIPO", "DESCRICAO", "DATA");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf("%-20s | %-50s | %-2d/%-2d/%-2d", aux->info.tipo, aux->info.desc, aux->info.data.day, aux->info.data.month, aux->info.data.year);
    }
}