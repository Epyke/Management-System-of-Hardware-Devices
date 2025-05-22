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

void printHistoricoMovMan(ELEM_H *inicio)
{
    if (inicio == NULL)
    {
        printf("Historico vazio\n");
        return;
    }

    ELEM_H *aux = NULL;

    printf("----------------------------------------------------------------------------HISTORICO---------------------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-20s | %-20s | %-3s | %-62s | %-10s \n", "TIPO", "EQUIPAMENTO", "MARCA", "MODELO", "ID", "DESCRICAO", "DATA");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {

        if (strcmp(aux->info.tipo, "Movimentacao") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Transferencia: %s --> %-40s | %-2d/%-2d/%-2d \n", aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model, aux->info.id, aux->info.desc.movimentacao.previousDep, aux->info.desc.movimentacao.newDep, aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
        if (strcmp(aux->info.tipo, "Manutencao") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Novo tecnico: %-46s | %-2d/%-2d/%-2d \n", aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model, aux->info.id, aux->info.desc.manutencao.tecnico, aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void printHistoricoEquipIDMovMan(ELEM_H *inicio, int ID)
{
    if (inicio == NULL)
    {
        printf("Historico vazio\n");
        return;
    }

    ELEM_H *aux = NULL;
    printf("----------------------------------------------------------------------------HISTORICO---------------------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-20s | %-20s | %-3s | %-50s | %-10s \n", "TIPO", "EQUIPAMENTO", "MARCA", "MODELO", "ID", "DESCRICAO", "DATA");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == ID)
        {
            if (strcmp(aux->info.tipo, "Movimentacao") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Transferencia: %s --> %-40s | %-2d/%-2d/%-2d \n", aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model, aux->info.id, aux->info.desc.movimentacao.previousDep, aux->info.desc.movimentacao.newDep, aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
            if (strcmp(aux->info.tipo, "Manutencao") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Novo tecnico: %-46s | %-2d/%-2d/%-2d \n", aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model, aux->info.id, aux->info.desc.manutencao.tecnico, aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
        }
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}