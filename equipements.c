#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipements.h"
#include <time.h>

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
    return 0;
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
    return 0;
}

void printEquips(ELEM_E *inicio)
{
    ELEM_E *aux = NULL;

    if (inicio == NULL)
    {
        printf("Nenhum equipamento existente\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        printf(
            "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
            aux->info.id,
            aux->info.type,
            aux->info.brand,
            aux->info.model,
            aux->info.num_serie,
            aux->info.date.day,
            aux->info.date.month,
            aux->info.date.year,
            aux->info.state,
            aux->info.departement,
            aux->info.tecnico);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int verifEquipsExistTecnico(ELEM_E *inicio, char tecnico[])
{
    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->info.tecnico, tecnico) == 0)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

void printEquipsTecnico(ELEM_E *inicio, char tecnico[])
{
    if (inicio == NULL)
    {
        printf("Nenhum equipamento existente\n");
        return;
    }

    if (verifEquipsExistTecnico(inicio, tecnico) != 1)
    {
        printf("Nenhum equipamento atribuido\n");
        return;
    }

    ELEM_E *aux = NULL;
    int found = 0;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.tecnico, tecnico) == 0)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement,
                aux->info.tecnico);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
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

int verifEquipDeparts(ELEM_E *inicio, int num)
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
        return 1;
    }
    else
    {
        printf("Nenhum equipamento encontrado, tente novamente\n");
        return 0;
    }
}

ELEM_E *procurarEquipDanificados(ELEM_E *inicio, int num)
{
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == num && strcmp(aux->info.state, "Danificado") == 0)
        {
            return aux;
            break;
        }
    }
    printf("Nenhum resultado encontrado\n");
    return NULL;
}

ELEM_E *procurarEquipManutencaoUser(ELEM_E *inicio, int num, char username[])
{
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == num && strcmp(aux->info.tecnico, username) == 0 && strcmp(aux->info.state, "Manutencao") == 0)
        {
            return aux;
            break;
        }
    }
    printf("Nenhum resultado encontrado\n");
    return NULL;
}

ELEM_E *procurarEquipUsoDesativado(ELEM_E *inicio, int num)
{
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.id == num && (strcmp(aux->info.state, "Desativado") == 0 || strcmp(aux->info.state, "Uso") == 0))
        {
            return aux;
            break;
        }
    }
    printf("Nenhum resultado encontrado\n");
    return NULL;
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
        if (strcmp(aux->info.state, str) == 0)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

int findExistingStrType(ELEM_E *inicio, char str[])
{
    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strstr(aux->info.type, str) == 0)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

int findExistingStateDanificadoUso(ELEM_E *inicio)
{
    ELEM_E *aux = NULL;
    aux = inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->info.state, "Uso") == 0 || strcmp(aux->info.state, "Desativado") == 0)
        {
            return 1;
        }
        aux = aux->seguinte;
    }
    return 0;
}

int filterEquipsType(ELEM_E *inicio, char type[])
{
    if (findExistingStrType(inicio, type) != 1)
    {
        printf("Nenhum equipamento com o tipo %s encontrado\n", type);
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.type, type) == 0)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement,
                aux->info.tecnico);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int filterEquipsState(ELEM_E *inicio, char state[])
{

    if (findExistingStrState(inicio, state) != 1)
    {
        printf("Nenhum equipamento com o estado %s encontrado\n", state);
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.state, state) == 0)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement,
                aux->info.tecnico);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int filterEquipsStateUsoDesativado(ELEM_E *inicio)
{

    if (findExistingStateDanificadoUso(inicio) != 1)
    {
        printf("Nenhum equipamento em uso ou desativado\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.state, "Uso") == 0 || strcmp(aux->info.state, "Desativado") == 0)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement,
                aux->info.tecnico);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

int filterEquipsDeparts(ELEM_E *inicio, int num)
{

    if (verifEquipDeparts(inicio, num) != 1)
    {
        return -1;
    }

    ELEM_E *aux = NULL;
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s | %-20s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO", "TECNICO");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.departement == num)
        {
            printf(
                "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-13d | %-20s\n",
                aux->info.id,
                aux->info.type,
                aux->info.brand,
                aux->info.model,
                aux->info.num_serie,
                aux->info.date.day,
                aux->info.date.month,
                aux->info.date.year,
                aux->info.state,
                aux->info.departement,
                aux->info.tecnico);
        }
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return 0;
}

// Função para dividir a lista ligada em dois
ELEM_E *split(ELEM_E *inicioEquips)
{
    ELEM_E *fast = inicioEquips;
    ELEM_E *slow = inicioEquips;

    // o apontador fast percorre dois elementos
    // o apontador slow percorre apenas um
    while (fast != NULL && fast->seguinte != NULL)
    {
        fast = fast->seguinte->seguinte;
        if (fast != NULL)
        {
            slow = slow->seguinte;
        }
    }

    // Divisão da lista ligada em dois
    ELEM_E *temp = slow->seguinte;
    slow->seguinte = NULL;
    // Retorna o início da segunda metade da lista ligada
    return temp;
}

// Função que junta duas listas ligadas
ELEM_E *merge(ELEM_E *first, ELEM_E *second, int num)
{

    // Se um dos apontadores for nulo, a outra lista ligada está ordenada
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    switch (num)
    {
    case 1:
        if (first->info.id <= second->info.id)
        {
            // Junta recursivamente o first com os restantes elementos
            // Como o ID do first é menor que o do second, vamos comparar o second com o elemento seguinte do first
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            // Junta recursivamente o second com os restantes elementos
            // Como o ID do second é menor que o do first, vamos comparar o first com o elemento seguinte do second
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 2:
        if (first->info.id >= second->info.id)
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 3:
        if (first->info.date.year > second->info.date.year)
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else if ((first->info.date.year == second->info.date.year) && (first->info.date.month > second->info.date.month))
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else if ((first->info.date.year == second->info.date.year) && (first->info.date.month == second->info.date.month) && (first->info.date.day > second->info.date.day))
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 4:
        if (strcmp(first->info.state, second->info.state) <= 0)
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;

    case 5:
        if (strcmp(first->info.type, second->info.type) <= 0)
        {
            first->seguinte = merge(first->seguinte, second, num);
            return first;
        }
        else
        {
            second->seguinte = merge(first, second->seguinte, num);
            return second;
        }
        break;
    default:
        break;
    }
    // Pick the smaller value between first and second nodes
}

// Função que efetua o algoritmo Merge Sort numa lista ligada
ELEM_E *MergeSort(ELEM_E *inicioEquips, int num)
{

    // Caso base, se a lista não tiver nenhum elemento
    // Está ordenada
    if (inicioEquips == NULL || (inicioEquips)->seguinte == NULL)
    {
        return inicioEquips;
    }

    // Divide a lista em dois, segunda é o apontador para o inicio da segunda lista
    ELEM_E *segunda = split(inicioEquips);

    // Ordenação recursiva de cada metade
    inicioEquips = MergeSort(inicioEquips, num);
    segunda = MergeSort(segunda, num);

    // Junta as duas metades ordenadas
    return merge(inicioEquips, segunda, num);
}

int escreverRelatorioDeparts(ELEM_E *inicioEquips, int num)
{
    if (verifEquipDeparts(inicioEquips, num) != 0)
    {
        return -1;
    }
    char name[50] = "Relatorios/Departs/Depart";
    char ext[] = ".txt";
    char departNum[2];
    sprintf(departNum, "%d", num);
    strcat(name, departNum);
    strcat(name, ext);
    FILE *fp = NULL;
    fp = fopen(name, "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }
    fprintf(fp, "--------------------------------------------------------------------------RELATORIO--------------------------------------------------------------------------------------\n\n");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    ELEM_E *aux;
    aux = inicioEquips;
    while (aux != NULL)
    {
        if (aux->info.departement == num)
        {
            fprintf(fp, "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
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

        aux = aux->seguinte;
    }
    fclose(fp);
    printf("Relatorio criado com sucesso\n");
    return 0;
}

int escreverRelatorioEstado(ELEM_E *inicioEquips, char state[])
{

    if (findExistingStrState(inicioEquips, state) != 1)
    {
        printf("Nenhum equipamento com o estado %s encontrado\n", state);
        return -1;
    }

    char name[100] = "Relatorios/Estados/";
    strcat(name, state);
    char ext[] = ".txt";
    strcat(name, ext);
    FILE *fp = NULL;
    fp = fopen(name, "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }
    fprintf(fp, "--------------------------------------------------------------------------RELATORIO--------------------------------------------------------------------------------------\n\n");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp, "%-3s | %-31s | %-21s | %-21s | %-20s | %-10s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    ELEM_E *aux;
    aux = inicioEquips;
    while (aux != NULL)
    {
        if (strcmp(aux->info.state, state) == 0)
        {
            fprintf(fp, "%-3d | %-31s | %-21s | %-21s | %-20d | %02d/%02d/%04d | %-21s | %-3d \n",
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

        aux = aux->seguinte;
    }
    fclose(fp);
    printf("Relatorio criado com sucesso\n");
    return 0;
}

int escreverEquipsCSV(ELEM_E *inicioEquips, char username[])
{

    if (inicioEquips == NULL)
    {
        printf("Nenhum equipamento existente\n");
        return 1;
    }

    if (verifEquipsExistTecnico(inicioEquips, username) != 1)
    {
        printf("Nenhum equipamento atribuido\n");
        return 1;
    }

    FILE *fp = NULL;
    char str[50] = "Relatorios/Equipamentos";
    strcat(str, username);
    strcat(str, ".csv");
    fp = fopen(str, "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir o ficheiro\n");
        return -1;
    }

    ELEM_E *aux = NULL;
    fprintf(fp, "ID,Tipo,Marca,Modelo,NumeroSerie,Data,Estado,Departamento,Tecnico\n");

    for (aux = inicioEquips; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->info.tecnico, username) == 0)
        {
            fprintf(fp, "%d,%s,%s,%s,%d,%d/%d/%d,%s,%d \n",
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
    fclose(fp);
    printf("Ficheiro CSV criado com sucesso\n");
    return 0;
}

DATE ObterDataAtual()
{
    time_t current_time;
    struct tm *time_info;
    DATE current_date;

    // obter a data atual
    time(&current_time);
    time_info = localtime(&current_time);

    // Extrair os elementos da data
    current_date.day = time_info->tm_mday;
    current_date.month = time_info->tm_mon + 1;    // tm_mon, como janeiro começa no 0, +1 porque guardas os meses num array
    current_date.year = time_info->tm_year + 1900; // tm_year, corresponde aos ano desde 1900

    return current_date;
}

void printAlertas(ELEM_E *inicio)
{
    DATE data_atual = ObterDataAtual();
    ELEM_E *aux = inicio;
    printf("-------------------------------------------------------------------ALERTAS (> 5 anos)-------------------------------------------------------------------\n");
    printf("%-3s | %-31s | %-21s | %-21s | %-20s | %-11s | %-21s | %-13s \n", "ID", "TIPO", "MARCA", "MODELO", "NUMERO DE SERIE", "DATA", "ESTADO", "DEPARTAMENTO");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (data_atual.year - aux->info.date.year > 5 || data_atual.year - aux->info.date.year == 5 && data_atual.month > aux->info.date.month || data_atual.year - aux->info.date.year == 5 && data_atual.month == aux->info.date.month && data_atual.day > aux->info.date.day)
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
}

int verifAlertasEquipamentos(ELEM_E *inicio)
{
    ELEM_E *aux = NULL;
    for (aux = inicio; aux != NULL; aux = aux->seguinte)
    {
        if (aux->info.date.year < 2020)
        {
            return 1;
        }
    }
    return 0;
}