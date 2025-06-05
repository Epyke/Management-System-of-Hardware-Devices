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

    printf("----------------------------------------------------------------------------HISTORICO------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-20s | %-20s | %-3s | %-62s | %-10s \n", "TIPO", "EQUIPAMENTO", "MARCA", "MODELO", "ID", "DESCRICAO", "DATA");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {

        if (strcmp(aux->info.tipo, "Movimentacao") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Transferencia: %s -> %-40s | %02d/%02d/%04d \n",
                   aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                   aux->info.id, aux->info.desc.movimentacao.previousDep,
                   aux->info.desc.movimentacao.newDep,
                   aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
        else if (strcmp(aux->info.tipo, "Manutencao") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Tecnico: %-46s | %02d/%02d/%04d \n",
                   aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                   aux->info.id, aux->info.desc.manutencao.tecnico,
                   aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
        else if (strcmp(aux->info.tipo, "Avaria") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Gravidade: %d - %-40s | %02d/%02d/%04d\n",
                   aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                   aux->info.id, aux->info.desc.avaria.gravidade,
                   aux->info.desc.avaria.descAvaria,
                   aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
        else if (strcmp(aux->info.tipo, "Reparacao") == 0)
        {
            printf("%-20s | %-30s | %-20s | %-20s | %-3d | Custo: %.2f euros - Pecas: %-30s | %02d/%02d/%04d \n",
                   aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                   aux->info.id, aux->info.desc.reparacao.custo,
                   aux->info.desc.reparacao.pecas_substituidas,
                   aux->info.data.day, aux->info.data.month, aux->info.data.year);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void printHistoricoEquipIDMovMan(ELEM_H *inicio, int ID)
{
    if (inicio == NULL)
    {
        printf("Historico vazio\n");
        return;
    }

    ELEM_H *aux = NULL;
    printf("----------------------------------------------------------------------------HISTORICO------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-20s | %-20s | %-3s | %-50s | %-10s \n", "TIPO", "EQUIPAMENTO", "MARCA", "MODELO", "ID", "DESCRICAO", "DATA");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == ID)
        {
            if (strcmp(aux->info.tipo, "Movimentacao") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Transferencia: %s -> %-40s | %02d/%02d/%04d \n",
                       aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                       aux->info.id, aux->info.desc.movimentacao.previousDep,
                       aux->info.desc.movimentacao.newDep,
                       aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
            else if (strcmp(aux->info.tipo, "Manutencao") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Tecnico: %-46s | %02d/%02d/%04d \n",
                       aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                       aux->info.id, aux->info.desc.manutencao.tecnico,
                       aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
            else if (strcmp(aux->info.tipo, "Avaria") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Gravidade: %d - %-40s | %02d/%02d/%04d \n",
                       aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                       aux->info.id, aux->info.desc.avaria.gravidade,
                       aux->info.desc.avaria.descAvaria,
                       aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
            else if (strcmp(aux->info.tipo, "Reparacao") == 0)
            {
                printf("%-20s | %-30s | %-20s | %-20s | %-3d | Custo: %.2f euros - Pecas: %-30s | %02d/%02d/%04d \n",
                       aux->info.tipo, aux->info.equipTipo, aux->info.brand, aux->info.model,
                       aux->info.id, aux->info.desc.reparacao.custo,
                       aux->info.desc.reparacao.pecas_substituidas,
                       aux->info.data.day, aux->info.data.month, aux->info.data.year);
            }
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int verifExistingAvariaRecorrente(ELEM_H *inicio)
{
    ELEM_H *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->info.tipo, "Avaria") == 0 && aux->info.desc.avaria.recorrencias > 2)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

int printAvariasRecorrencia(ELEM_H *inicio)
{

    if (verifExistingAvariaRecorrente(inicio) == 0)
    {
        printf("Nenhuma avaria recorrente existente\n");
        return -1;
    }

    ELEM_H *aux = NULL, *previous = NULL;
    aux = inicio;
    int maiorRecorrencia;
    printf("----------------------------------------------------------------------------HISTORICO----------------------------------------------------------------------------------------------------------------------\n");
    printf("%-20s | %-30s | %-20s | %-20s | %-3s | %-50s | %-9s | %-12s| %-10s \n", "TIPO", "EQUIPAMENTO", "MARCA", "MODELO", "ID", "DESCRICAO", "GRAVIDADE", "RECORRENCIAS", "DATA");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while (aux != NULL)
    {
        {
            if (strcmp(aux->info.tipo, "Avaria") == 0 && aux->info.desc.avaria.recorrencias > 2)
            {
                // Verifica se as avarias são as mesmas
                int is_first_occurrence = 1;
                ELEM_H *temp = inicio;

                while (temp != aux)
                {
                    if (strcmp(temp->info.tipo, "Avaria") == 0 &&
                        temp->info.id == aux->info.id &&
                        strcmp(temp->info.desc.avaria.descAvaria, temp->info.desc.avaria.descAvaria) == 0)
                    {
                        is_first_occurrence = 0;
                        break;
                    }
                    temp = temp->seguinte;
                }

                if (is_first_occurrence)
                {
                    // Encontra o maior valor de recorrencia
                    ELEM_H *highest = aux;
                    ELEM_H *search = aux->seguinte;

                    while (search != NULL)
                    {
                        if (strcmp(search->info.tipo, "Avaria") == 0 &&
                            search->info.id == aux->info.id &&
                            strcmp(search->info.desc.avaria.descAvaria, aux->info.desc.avaria.descAvaria) == 0 &&
                            search->info.desc.avaria.recorrencias > highest->info.desc.avaria.recorrencias)
                        {
                            highest = search;
                        }
                        search = search->seguinte;
                    }

                    // Escreve apenas a avaria com a recorrencia mais alta
                    printf("%-20s | %-30s | %-20s | %-20s | %-3d | %-50s | %-9d | %-12d | %02d/%02d/%04d \n",
                           highest->info.tipo, highest->info.equipTipo, highest->info.brand,
                           highest->info.model, highest->info.id, highest->info.desc.avaria.descAvaria,
                           highest->info.desc.avaria.gravidade, highest->info.desc.avaria.recorrencias,
                           highest->info.data.day, highest->info.data.month, highest->info.data.year);
                }
            }
        }
        aux = aux->seguinte;
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int verifMesmaAvariaExistente(ELEM_H *inicio, char descAvaria[], int ID)
{
    if (inicio == NULL)
    {
        return 0;
    }

    ELEM_H *aux = NULL;
    int maior = 0;
    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->info.tipo, "Avaria") == 0 && strcmp(aux->info.desc.avaria.descAvaria, descAvaria) == 0 && aux->info.id == ID)
        {
            if (aux->info.desc.avaria.recorrencias > maior)
            {
                maior = aux->info.desc.avaria.recorrencias;
            }
        }
        aux = aux->seguinte;
    }
    return maior;
}

int historicoRelease(ELEM_H **inicio)
{
    if (*inicio == NULL)
    {
        return -1;
    }
    ELEM_H *aux = NULL, *next = NULL;
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

int verifAvariasRecorrentes(ELEM_H *inicio)
{
    ELEM_H *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.desc.avaria.recorrencias > 2)
        {
            return 1;
        }
    }
    return 0;
}