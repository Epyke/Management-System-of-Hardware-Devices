#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipements.h"

#define EQUIPSFILE "data/equips.dat"

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
    FILE *fp = fopen(EQUIPSFILE, "rb");

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
    FILE *fp = fopen(EQUIPSFILE, "wb");

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

    FILE *fp = fopen(EQUIPSFILE, "ab");

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
        printf(
            "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
            aux->info.id,
            aux->info.type,
            aux->info.brand,
            aux->info.model,
            aux->info.num_serie,
            aux->info.date.day,
            aux->info.date.month,
            aux->info.date.year,
            aux->info.state,
            aux->info.departement);
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

int RemoverEquipsDepartsNum(ELEM_E **inicio, int num)
{
    ELEM_E *aux = NULL, *previous = NULL, *temp = NULL;
    aux = *inicio;
    int removeCount = 0;
    while (aux != NULL)
    {
        if (aux->info.departement == num)
        {
            temp = aux;
            if (previous == NULL)
            {
                *inicio = aux->seguinte;
            }
            else
            {
                previous->seguinte = aux->seguinte;
            }
            aux = aux->seguinte;
            free(temp);
            removeCount++;
        }
        else
        {
            previous = aux;
            aux = aux->seguinte;
        }
    }
    return removeCount;
}

ELEM_E *procurarEquipDeparts(ELEM_E *inicio, int num)
{
    ELEM_E *aux = NULL;
    int found = 0;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.departement == num)
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

void refreshEquipDeparts(ELEM_E *inicio, int num)
{
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.departement > num)
        {
            aux->info.departement -= 1;
        }
    }
}

int findExistingStrState(ELEM_E *inicio, char str[])
{
    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strstr(aux->info.state, str) != NULL)
        {
            return 0;
        }
        aux = aux->seguinte;
    }
    return -1;
}

int findExistingStrType(ELEM_E *inicio, char str[])
{
    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strstr(aux->info.type, str) != NULL)
        {
            return 0;
        }
        aux = aux->seguinte;
    }
    return -1;
}

int filterEquipsType(ELEM_E *inicio, char type[])
{
    if (findExistingStrType(inicio, type) != 0)
    {
        printf("Nenhum resultado encontrado\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-11s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strstr(aux->info.type, type) != NULL)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int filterEquipsState(ELEM_E *inicio, char state[])
{

    if (findExistingStrState(inicio, state) != 0)
    {
        printf("Nenhum resultado encontrado\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-11s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strstr(aux->info.state, state) != NULL)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int filterEquipsDeparts(ELEM_E *inicio, int num)
{

    if (procurarEquipDeparts(inicio, num) == NULL)
    {
        printf("Nenhum departamento encontrado\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-11s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.departement == num)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

// Function to split the singly linked list into two halves
ELEM_E *split(ELEM_E *inicioEquips)
{
    ELEM_E *fast = inicioEquips;
    ELEM_E *slow = inicioEquips;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->seguinte != NULL)
    {
        fast = fast->seguinte->seguinte;
        if (fast != NULL)
        {
            slow = slow->seguinte;
        }
    }

    // Split the list into two halves
    ELEM_E *temp = slow->seguinte;
    slow->seguinte = NULL;
    return temp;
}

// Function to merge two sorted singly linked lists
ELEM_E *merge(ELEM_E *first, ELEM_E *second, int num)
{

    // If either list is empty, return the other list
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    switch (num)
    {
    case 1:
        if (first->info.id <= second->info.id)
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists
            // and link the result to the current node
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 2:
        if (first->info.id >= second->info.id)
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists
            // and link the result to the current node
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 3:
        if (first->info.date.year > second->info.date.year)
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else if ((first->info.date.year == second->info.date.year) && (first->info.date.month > second->info.date.month))
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else if ((first->info.date.year == second->info.date.year) && (first->info.date.month == second->info.date.month) && (first->info.date.day > second->info.date.day))
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists
            // and link the result to the current node
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 4:
        if (strcmp(first->info.state, second->info.state) <= 0)
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists
            // and link the result to the current node
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 5:
        if (strcmp(first->info.type, second->info.type) <= 0)
        {
            // Recursively merge the rest of the lists and
            // link the result to the current node
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Recursively merge the rest of the lists
            // and link the result to the current node
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;
    default:
        break;
    }
    // Pick the smaller value between first and second nodes
}

// Function to perform merge sort on a singly linked list
ELEM_E *MergeSort(ELEM_E *inicioEquips, int num)
{

    // Base case: if the list is empty or has only one node,
    // it's already sorted
    if (inicioEquips == NULL || (inicioEquips)->seguinte == NULL)
    {
        return inicioEquips;
    }

    // Split the list into two halves
    ELEM_E *segunda = split(inicioEquips);

    // Recursively sort each half
    inicioEquips = MergeSort(inicioEquips, num);
    segunda = MergeSort(segunda, num);

    // Merge the two sorted halves
    return merge(inicioEquips, segunda, num);
}