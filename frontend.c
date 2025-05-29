#include <stdio.h>
#include <string.h>
#include "users.h"
#include "departements.h"
#include "equipements.h"
#include "historico.h"

/**
 * @file frontend.c
 * Ficheiro principal que contêm todas as funções relativas ao menu.
 * @author Henrique Fernandes
 * @date 24/04/2025
 * @version 0.1
 */

/**
 * @fn inputDeparts(ELEM_D **inicioDeparts)
 * @brief Cria um novo user, com os dados inseridos pelo utilizador.
 * @param inicioDeparts
 * @return int
 */
int inputDeparts(ELEM_D **inicioDeparts)
{
    DEPART depart;

    printf("Introduza o nome do novo departamento.\n");
    fgets(depart.name, sizeof(depart.name), stdin);
    depart.name[strcspn(depart.name, "\n")] = '\0';

    int numb = getDepartsNumb(*inicioDeparts);
    numb = numb + 1;
    depart.code = numb;
    registrarDeparts(depart, inicioDeparts);
    return 0;
}

/**
 * @fn altDepartMenu(ELEM_D *inicioDeparts)
 * @brief Escreve o menu, que permite alterar as informações de um departamento.
 * @param inicioDeparts
 */
void altDepartMenu(ELEM_D *inicioDeparts)
{
    int input, target;
    char newName[20];
    ELEM_D *depart = NULL;

    printDeparts(inicioDeparts);
    printf("Introduza o numero do departamento: ");
    scanf("%d", &target);
    getchar();
    depart = procurarDepart(inicioDeparts, target);
    if (depart == NULL)
    {
        return;
    }

    do
    {
        printf("\n-----------------------------------ALTERAR-----------------------------------\n");
        printf("Selecionou o departamento %s, numero %d \n\n", depart->info.name, depart->info.code);
        printf("1 - Nome\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Introduza um novo nome\n");
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';
            strcpy(depart->info.name, newName);
            writeChangesDeparts(inicioDeparts);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn filtrarMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts)
 * @brief Escreve o menu que permite filtrar os equipamentos.
 * @param inicioEquips
 * @param inicioDeparts
 */
void filtrarMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts)
{
    int input, dep;
    char str[20];
    do
    {
        printf("\n-----------------------------------FILTRAR-----------------------------------\n");
        printf("1 - Estado\n");
        printf("2 - Tipo\n");
        printf("3 - Departamento\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            int escolha;
            do
            {
                printf("Escolha do estado:\n");
                printf("1 - Uso (equipamento em uso)\n");
                printf("2 - Manutencao (equipamento em manutencao)\n");
                printf("3 - Danificado\n");
                printf("4 - Desativado\n");
                printf("0 - Voltar\n");
                scanf("%d", &escolha);
                getchar();
                switch (escolha)
                {
                case 1:
                    filterEquipsState(inicioEquips, "Uso");
                    break;
                case 2:
                    filterEquipsState(inicioEquips, "Manutencao");
                    break;
                case 3:
                    filterEquipsState(inicioEquips, "Danificado");
                    break;
                case 4:
                    filterEquipsState(inicioEquips, "Desativado");
                    break;
                case 0:
                    break;
                default:
                    printf("Escolha invalida, tente novamente\n");
                    break;
                }
            } while (escolha != 0);

            break;
        case 2:
            printf("Introduza um tipo de equipamento\n");
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = '\0';
            filterEquipsType(inicioEquips, str);
            break;
        case 3:
            printDeparts(inicioDeparts);
            printf("Introduza o numero de um departamento\n");
            scanf("%d", &dep);
            filterEquipsDeparts(inicioEquips, dep);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn OrdenarMenu(ELEM_E **inicioEquips)
 * @brief Escreve o menu que permite ordenar equipamentos.
 * @param inicioEquips
 */
void OrdenarMenu(ELEM_E **inicioEquips)
{
    int input;
    char str[20];
    do
    {
        printf("\n-----------------------------------Ordenar-----------------------------------\n");
        printf("1 - Criacao mais recente\n");
        printf("2 - Criacao mais antiga\n");
        printf("3 - Data de aquisicao mais recente\n");
        printf("4 - Estado\n");
        printf("5 - Tipo\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        if (input > 0 && input < 6)
        {
            *inicioEquips = MergeSort(*inicioEquips, input);
            printEquips(*inicioEquips);
        }
        else if (input != 0)
        {
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn listEquips(ELEM_E **inicioEquips, ELEM_D *inicioDeparts)
 * @brief Escreve o menu que permite escolher o tipo de listagem de equipamentos.
 * @param inicioEquips
 * @param inicioDeparts
 */
void listEquips(ELEM_E **inicioEquips, ELEM_D *inicioDeparts)
{
    int input;
    do
    {
        printf("\n-----------------------------------LISTAR-----------------------------------\n");
        printf("1 - Ordenar\n");
        printf("2 - Filtrar\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            OrdenarMenu(inicioEquips);
            break;
        case 2:
            filtrarMenu(*inicioEquips, inicioDeparts);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn verifYear(int year)
 * @brief Verifica a validade do ano passado como argumento.
 * Se 1900<ano<2026 retorna 1
 * Se não retorna 0
 * @param year
 * @return int
 */
int verifYear(int year)
{
    if (year < 1900 || year > 2026)
    {
        return 0;
    }
    return 1;
}
/**
 * @fn verifMonth(int month)
 * @brief Verifica o mês passado como argumento.
 * Se 1<mês<12 retorna 1
 * Se não retorna 0
 * @param month
 * @return int
 */
int verifMonth(int month)
{
    if (month < 1 || month > 12)
    {
        return 0;
    }
    return 1;
}

/**
 * @fn verifDay(int day, int month, int year)
 * @brief Verifica o dia passado por argumento.
 * Retorna 1 se for valido
 * Avril, Junho, Setembro Novembro: 30 dias
 * Restantes meses exeto fevreiro: 31 dias
 * Fevreiro: 28 dias
 * Ano bissexto, fevreiro: 29 dias
 * Retorna 0, se for invalido
 * @param day
 * @param month
 * @param year
 * @return int
 */
int verifDay(int day, int month, int year)
{
    if ((day < 1 || day > 31))
    {
        return 0;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return 0;
    }

    if (month == 2 && (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) && day > 29)
    {
        return 0;
    }
    else if (month == 2 && day > 28)
    {
        return 0;
    }
    return 1;
}

/**
 * @fn equipsDateSystem(DATE date)
 * @brief Agrupa todas as funções que verificam a data (equipamentos).
 * Retorna 1 se tudo correr bem
 * Se não retorna 0
 * @param date
 * @return int
 */
int equipsDateSystem(DATE date)
{
    if (!verifYear(date.year))
    {
        printf("Erro relativamente ao ano introduzido\n");
        return 0;
    }

    if (!verifMonth(date.month))
    {
        printf("Erro relativamente ao mes introduzido\n");
        return 0;
    }

    if (!verifDay(date.day, date.month, date.year))
    {
        printf("Erro relativamente ao dia introduzido\n");
        return 0;
    }

    return 1;
}

/**
 * @fn HistoricoDateSystem(DATE_H date)
 * @brief Agrupa todas as funções que verificam a data (historico).
 * Retorna 1 se tudo correr bem
 * Se não retorna 0
 * @param date
 * @return int
 */
int HistoricoDateSystem(DATE_H date)
{
    if (!verifYear(date.year))
    {
        printf("Erro relativamente ao ano introduzido\n");
        return 0;
    }

    if (!verifMonth(date.month))
    {
        printf("Erro relativamente ao mes introduzido\n");
        return 0;
    }

    if (!verifDay(date.day, date.month, date.year))
    {
        printf("Erro relativamente ao dia introduzido\n");
        return 0;
    }

    return 1;
}

/**
 * @fn inputEquips(ELEM_E **inicioEquips, ELEM_D *inicioDeparts)
 * @brief Cria um equipamento, com os dados introduzidos pelo utilizador.
 * @param date
 * @return int
 */
void inputEquips(ELEM_E **inicioEquips, ELEM_D *inicioDeparts)
{
    EQUIPE equip;
    int id = getEquipsNumb(*inicioEquips);
    id++;
    equip.id = id;
    printf("Introduza o tipo de equipamento\n");
    fgets(equip.type, sizeof(equip.type), stdin);
    equip.type[strcspn(equip.type, "\n")] = '\0';

    printf("Introduza a marca do equipamento\n");
    fgets(equip.brand, sizeof(equip.brand), stdin);
    equip.brand[strcspn(equip.brand, "\n")] = '\0';

    printf("Introduza o modelo do equipamento\n");
    fgets(equip.model, sizeof(equip.model), stdin);
    equip.model[strcspn(equip.model, "\n")] = '\0';

    do
    {
        printf("Introduza o numero de serie\n");
        scanf("%d", &equip.num_serie);
        getchar();
    } while (verifNumSerie(*inicioEquips, equip.num_serie == 1));

    int res;
    do
    {
        printf("\nIntroduza a data de aquisicao no formate DD/MM/YYYY\n"); // Sistema de data, para mais tarde
        char inputStr[11];
        fgets(inputStr, sizeof(inputStr), stdin);
        inputStr[strcspn(inputStr, "\n")] = '\0';
        res = sscanf(inputStr, "%d/%d/%d", &equip.date.day, &equip.date.month, &equip.date.year);
        getchar();
        if (res != 3)
        {
            printf("Erro relativamente ao formato introduzido\n");
            continue;
        }

        if (!equipsDateSystem(equip.date))
        {
            continue;
        }

        break;
    } while (1);

    int escolha;
    do
    {
        printf("Escolha do estado:\n");
        printf("1 - Uso (equipamento em uso)\n");
        printf("2 - Danificado\n");
        printf("3 - Desativado\n");
        scanf("%d", &escolha);
        getchar();
        switch (escolha)
        {
        case 1:
            strcpy(equip.state, "Uso");
            break;
        case 2:
            strcpy(equip.state, "Danificado");
            break;
        case 3:
            strcpy(equip.state, "Desativado");
            break;
        default:
            printf("Escolha invalida, tente novamente\n");
            break;
        }
    } while (escolha < 1 && escolha > 4);

    do
    {
        printDeparts(inicioDeparts);
        printf("Associe o equipamento ao departamento\n");
        scanf("%d", &equip.departement);
        getchar();
    } while (verifDepartNum(inicioDeparts, equip.departement) == 0);

    strcpy(equip.tecnico, "Nenhum");

    registrarEquips(equip, inicioEquips);
}

/**
 * @fn altEquipMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts, ELEM_H **inicioHistorico)
 * @brief Escreve o menu que permite a alteração de equipamentos
 * @param inicioEquips
 * @param inicioDeparts
 * @param inicioHistorico
 */
void altEquipMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts, ELEM_H **inicioHistorico)
{
    int input, target, res;
    char newName[20];
    ELEM_E *equip = NULL;

    printEquips(inicioEquips);
    printf("Introduza o ID do equipamento: ");
    scanf("%d", &target);
    getchar();
    equip = procurarEquip(inicioEquips, target);
    if (equip == NULL)
    {
        return;
    }

    do
    {
        printf("\n-----------------------------------ALTERAR-----------------------------------\n");
        printf("Selecionou o equipamento %s, %s, ID = %d \n\n", equip->info.model, equip->info.brand, equip->info.id);
        printf("1 - Tipo\n");
        printf("2 - Marca\n");
        printf("3 - Modelo\n");
        printf("4 - Numero de serie\n");
        printf("5 - Data de aquisisao\n");
        printf("6 - Estado\n");
        printf("7 - Departamento\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printf("Introduza o novo tipo de equipamento\n");
            fgets(equip->info.type, sizeof(equip->info.type), stdin);
            equip->info.type[strcspn(equip->info.type, "\n")] = '\0';
            break;
        case 2:
            printf("Introduza a nova marca do equipamento\n");
            fgets(equip->info.brand, sizeof(equip->info.brand), stdin);
            equip->info.brand[strcspn(equip->info.brand, "\n")] = '\0';
            break;
        case 3:
            printf("Introduza o novo modelo do equipamento\n");
            fgets(equip->info.model, sizeof(equip->info.model), stdin);
            equip->info.model[strcspn(equip->info.model, "\n")] = '\0';
            break;
        case 4:
            do
            {
                printf("Introduza o novo número de serie\n");
                scanf("%d", &equip->info.num_serie);
                getchar();
            } while (verifNumSerie(inicioEquips, equip->info.num_serie == 1));
            break;
        case 5:
            do
            {
                printf("\nIntroduza a nova data de aquisicao no formate DD/MM/YYYY\n");
                char inputStr[11];
                fgets(inputStr, sizeof(inputStr), stdin);
                inputStr[strcspn(inputStr, "\n")] = '\0';
                res = sscanf(inputStr, "%d/%d/%d", &equip->info.date.day, &equip->info.date.month, &equip->info.date.year);

                if (res != 3)
                {
                    printf("Erro relativamente ao formato introduzido\n");
                    continue;
                }

                if (!equipsDateSystem(equip->info.date))
                {
                    continue;
                }
                break;
            } while (1);
            break;
        case 6:
            if (strcmp(equip->info.state, "Manutencao") == 0)
            {
                printf("O estado dos equipamentos em manutencao, apenas podem ser alterados pelo respetivo tecnico\n");
                break;
            }
            int escolha;
            do
            {
                printf("Escolha do novo estado:\n");
                printf("1 - Uso (equipamento em uso)\n");
                printf("2 - Danificado\n");
                printf("3 - Desativado\n");
                scanf("%d", &escolha);
                getchar();
                switch (escolha)
                {
                case 1:
                    strcpy(equip->info.state, "Uso");
                    break;
                case 2:
                    strcpy(equip->info.state, "Danificado");
                    break;
                case 3:
                    strcpy(equip->info.state, "Desativado");
                    break;
                default:
                    printf("Escolha invalida, tente novamente\n");
                    break;
                }
            } while (escolha < 1 && escolha > 4);
        case 7:

            int previous = equip->info.departement;

            do
            {
                printDeparts(inicioDeparts);
                printf("Introduza o novo departamento\n");
                scanf("%d", &equip->info.departement);
                getchar();
                if (equip->info.departement == previous)
                {
                    printf("Mesmo departamento, tente novamente\n");
                }
            } while (verifDepartNum(inicioDeparts, equip->info.departement) == 0 || equip->info.departement == previous);

            ELEM_D *newDepart = NULL;
            newDepart = procurarDepart(inicioDeparts, equip->info.departement);

            ELEM_D *previousDepart = NULL;
            previousDepart = procurarDepart(inicioDeparts, previous);

            char str[200];
            sprintf(str, "Transferencia de Departamento: %s ===> %s", previousDepart->info.name, newDepart->info.name);

            HISTORICO historico;
            strcpy(historico.tipo, "Movimentacao");
            strcpy(historico.equipTipo, equip->info.type);
            strcpy(historico.brand, equip->info.brand);
            strcpy(historico.model, equip->info.model);
            historico.id = equip->info.id;
            strcpy(historico.desc.movimentacao.previousDep, previousDepart->info.name);
            strcpy(historico.desc.movimentacao.newDep, newDepart->info.name);

            do
            {
                printf("\nIntroduza a data de movimentacao no formate DD/MM/YYYY\n"); // Sistema de data, para mais tarde
                char inputStr[11];
                fgets(inputStr, sizeof(inputStr), stdin);
                inputStr[strcspn(inputStr, "\n")] = '\0';
                res = sscanf(inputStr, "%d/%d/%d", &historico.data.day, &historico.data.month, &historico.data.year);
                getchar();
                if (res != 3)
                {
                    printf("Erro relativamente ao formato introduzido\n");
                    continue;
                }

                if (!HistoricoDateSystem(historico.data))
                {
                    continue;
                }

                break;
            } while (1);

            registrarHistorico(historico, inicioHistorico);

        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
    writeChangesEquips(inicioEquips);
}

/**
 * @fn equipsMenu(ELEM_E **inicioEquips, ELEM_D *inicioDeparts, ELEM_H **inicioHistorico)
 * @brief Menu que permite gerir todos os equipamentos.
 * Listar, Adicionar, Alterar, Remover
 * @param inicioEquips
 * @param inicioDeparts
 * @param inicioHistorico
 */
void equipsMenu(ELEM_E **inicioEquips, ELEM_D *inicioDeparts, ELEM_H **inicioHistorico)
{
    int input, num;

    if (inicioDeparts == NULL)
    {
        printf("Nenhum departamento existente\n");
        return;
    }

    do
    {
        printf("\n-----------------------------------EQUIPAMENTOS-----------------------------------\n");
        printf("1 - Listar\n");
        printf("2 - Adicionar\n");
        printf("3 - Alterar\n");
        printf("4 - Remover\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            if (inicioEquips == NULL)
            {
                printf("Nenhum equipamento existente\n");
                return;
            }
            listEquips(inicioEquips, inicioDeparts);
            break;
        case 2:
            inputEquips(inicioEquips, inicioDeparts);
            break;
        case 3:
            if (inicioEquips == NULL)
            {
                printf("Nenhum equipamento existente\n");
                return;
            }

            altEquipMenu(*inicioEquips, inicioDeparts, inicioHistorico);
            break;
        case 4:
            if (inicioEquips == NULL)
            {
                printf("Nenhum equipamento existente\n");
                return;
            }
            printEquips(*inicioEquips);
            scanf("%d", &num);
            getchar();
            int numb_equips = getEquipsNumb(*inicioEquips);
            if (eliminarEquip(inicioEquips, num) == 0)
            {
                if (num != numb_equips)
                {
                    refreshEquipCodes(*inicioEquips);
                }
                writeChangesEquips(*inicioEquips);
            }
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn departsMenu(ELEM_D **inicioDeparts, ELEM_E **inicioEquips)
 * @brief Escrever o menu que permite gerir todos os departamentos.
 * Listar, Adicionar, Alterar, Remover
 * @param inicioDeparts
 * @param inicioEquips
 */
void departsMenu(ELEM_D **inicioDeparts, ELEM_E **inicioEquips)
{
    int input, num;
    do
    {
        printf("\n-----------------------------------DEPARTAMENTOS-----------------------------------\n");
        printf("1 - Listar\n");
        printf("2 - Adicionar\n");
        printf("3 - Alterar\n");
        printf("4 - Remover\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            if (*inicioDeparts == NULL)
            {
                printf("Nenhum departamento criado\n");
                break;
            }
            printDeparts(*inicioDeparts);
            break;
        case 2:
            printDeparts(*inicioDeparts);
            inputDeparts(inicioDeparts);
            break;
        case 3:
            if (*inicioDeparts == NULL)
            {
                printf("Nenhum departamento criado\n");
                break;
            }
            altDepartMenu(*inicioDeparts);
            break;
        case 4:
            if (*inicioDeparts == NULL)
            {
                printf("Nenhum departamento criado\n");
                break;
            }
            printDeparts(*inicioDeparts);
            printf("Introduza o numero do departamento\n");
            scanf("%d", &num);
            getchar();
            int num_departs = getDepartsNumb(*inicioDeparts);

            if (verifEquipDeparts(*inicioEquips, num) == 1)
            {
                printf("Este departamente possui equipamentos atribuidos, tem de elimina-los para concluir a operacao, deseja remove-los ?\n");
                printf("Y/n\n");
                char opc;
                scanf("%c", &opc);
                getchar();
                if (opc == 'Y' || opc == 'y')
                {
                    int removedItems = RemoverEquipsDepartsNum(inicioEquips, num);
                    printf("Removeu com sucesso %d equipamentos\n", removedItems);
                    writeChangesEquips(*inicioEquips);
                    refreshEquipCodes(*inicioEquips);
                }
                else
                {
                    printf("Operacao cancelada, devido a presenca de equipamentos no departamento escolhido\n");
                    break;
                }
            }

            if (eliminarDepart(inicioDeparts, num) == 0)
            {
                if (num != num_departs)
                {
                    refreshDepartCodes(*inicioDeparts);
                    refreshEquipDeparts(*inicioEquips, num);
                    writeChangesEquips(*inicioEquips);
                }
                writeChangesDeparts(*inicioDeparts);
                printf("Departamento removido com sucesso\n");
            }
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn RelatoriosMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts)
 * @brief Escreve o menu que permite escrever relatorios.
 * Escolha entre escrever um relatorio por estado ou por departamento.
 * @param inicioEquips
 * @param inicioDeparts
 */
void RelatoriosMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts)
{
    int input, num;

    if (inicioDeparts == NULL)
    {
        printf("Nenhum departamento criado\n");
        return;
    }

    if (inicioEquips == NULL)
    {
        printf("Nenhum equipamento criado\n");
        return;
    }

    do
    {
        printf("\n-----------------------------------RELATORIOS-----------------------------------\n");
        printf("1 - Departamentos\n");
        printf("2 - Estado\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printDeparts(inicioDeparts);
            printf("Introduza o numero de um departamento\n");
            scanf("%d", &num);
            getchar();
            escreverRelatorioDeparts(inicioEquips, num);
            break;
        case 2:
            int escolha;
            do
            {
                printf("Escolha do estado:\n");
                printf("1 - Uso (equipamento em uso)\n");
                printf("2 - Manutencao (equipamento em manutencao)\n");
                printf("3 - Danificado\n");
                printf("4 - Desativado\n");
                printf("0 - Voltar\n");
                scanf("%d", &escolha);
                getchar();
                switch (escolha)
                {
                case 1:
                    escreverRelatorioEstado(inicioEquips, "Uso");
                    break;
                case 2:
                    escreverRelatorioEstado(inicioEquips, "Manutencao");
                    break;
                case 3:
                    escreverRelatorioEstado(inicioEquips, "Danificado");
                    break;
                case 4:
                    escreverRelatorioEstado(inicioEquips, "Desativado");
                    break;
                case 0:
                    break;
                default:
                    printf("Escolha invalida, tente novamente\n");
                    break;
                }
            } while (escolha != 0);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn HistoricoMenu(ELEM_H *inicioHistorico, ELEM_E *inicioEquip)
 * @brief Escreve o menu que permite listar o historico dos equipamentos.
 * Listagem das movimentacoes e manutencoes
 * @param inicioHistorico
 * @param inicioEquip
 */
void HistoricoMenu(ELEM_H *inicioHistorico, ELEM_E *inicioEquip)
{
    int input, inputID;

    if (inicioHistorico == NULL)
    {
        printf("Historico vazio\n");
        return;
    }

    do
    {
        printf("\n-----------------------------------HISTORICO-----------------------------------\n");
        printf("1 - Completo\n");
        printf("2 - Equipamento\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            printHistoricoMovMan(inicioHistorico);
            break;
        case 2:
            printEquips(inicioEquip);
            printf("Introduza o ID do equipamento\n");
            scanf("%d", &inputID);
            printHistoricoEquipIDMovMan(inicioHistorico, inputID);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/**
 * @fn EquipamentosDeclararUser(ELEM_U *inicioUser, ELEM_E *inicioEquip, ELEM_H **inicioHistorico, char username[])
 * @brief Escreve o menu que permite ao tecnico de declarar um equipamento.
 * Declarar como avaria ou manutencao.
 * @param inicioUser
 * @param inicioEquip
 * @param inicioHistorico
 * @param username
 */
void EquipamentosDeclararUser(ELEM_U *inicioUser, ELEM_E *inicioEquip, ELEM_H **inicioHistorico, char username[])
{
    int inputID, input;
    ELEM_E *equip = NULL;
    HISTORICO historico;
    do
    {
        printf("-----------------------------DECLARAR-----------------------------\n");
        printf("1 - Avaria\n");
        printf("2 - Manutencao\n");
        printf("0 - Voltar\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {

        case 1:

            if (filterEquipsStateUsoDesativado(inicioEquip) != 1)
            {
                break;
            }

            printf("Introduza o ID do equipamento pretendido\n");
            scanf("%d", &inputID);
            getchar();

            equip = procurarEquipUsoDesativado(inicioEquip, inputID);

            if (equip == NULL)
            {
                break;
            }

            strcpy(historico.equipTipo, equip->info.type);
            strcpy(historico.brand, equip->info.brand);
            strcpy(historico.model, equip->info.model);
            historico.id = equip->info.id;

            do
            {
                printf("Introduza o grau de gravidade da avaria (1-5)\n");
                scanf("%d", &historico.desc.avaria.gravidade);
                getchar();
            } while (historico.desc.avaria.gravidade > 0 && historico.desc.avaria.gravidade < 6);

            printf("Introduza a descrição da avaria\n");
            fgets(historico.desc.avaria.descAvaria, sizeof(historico.desc.avaria.descAvaria), stdin);
            historico.desc.avaria.descAvaria[strcspn(historico.desc.avaria.descAvaria, "\n")] = '\0';

            if (verifMesmaAvariaExistente(*inicioHistorico, historico.desc.avaria.descAvaria) == 1)
            {
                historico.desc.avaria.recorrencias += 1;
            }

            strcpy(equip->info.state, "Danificado");
            writeChangesEquips(inicioEquip);
            registrarHistorico(historico, inicioHistorico);
            printf("Atribuicao efetuada com sucesso\n");
            break;
        case 2:

            if (filterEquipsState(inicioEquip, "Danificado") != 1)
            {
                break;
            }

            printf("Introduza o ID do equipamento pretendido\n");
            scanf("%d", &inputID);
            getchar();

            equip = procurarEquipDanificados(inicioEquip, inputID);

            if (equip == NULL)
            {
                break;
            }

            strcpy(historico.equipTipo, equip->info.type);
            strcpy(historico.brand, equip->info.brand);
            strcpy(historico.model, equip->info.model);
            historico.id = equip->info.id;

            strcpy(historico.desc.manutencao.tecnico, username);
            strcpy(equip->info.tecnico, username);
            strcpy(equip->info.state, "Manutencao");

            writeChangesEquips(inicioEquip);
            registrarHistorico(historico, inicioHistorico);
            printf("Atribuicao efetuada com sucesso\n");
            break;
        case 0:
            break;
        default:
            printf("Introduziu um valor inválido, tente novamente\n");
            break;
        }
    } while (input != 0);
}

/**
 * @fn EquipamentosRepararUser(ELEM_U *inicioUser, ELEM_E *inicioEquip, ELEM_H **inicioHistorico, char username[])
 * @brief Escreve o menu que permite ao tecnico a reparacao de equipamentos.
 * Decidir entre declarar o equipamento como em uso ou desativado.
 * @param inicioUser
 * @param inicioEquip
 * @param inicioHistorico
 * @param username
 */
void EquipamentosRepararUser(ELEM_U *inicioUser, ELEM_E *inicioEquip, ELEM_H **inicioHistorico, char username[])
{
    int inputID, input;
    ELEM_E *equip = NULL;
    HISTORICO historico;

    if (inicioEquip == NULL)
    {
        printf("Nenhum equipamento existente\n");
    }

    do
    {
        printf("-----------------------------REPARACAO-----------------------------\n");
        printf("1 - Uso\n");
        printf("2 - Desativacao\n");
        printf("0 - Voltar\n");

        scanf("%d", &input);
        getchar();

        if (filterEquipsState(inicioEquip, "Manutencao") != 0)
        {
            printf("Nenhum equipamento em manutencao encontrado\n");
            return;
        }

        printf("Introduza o ID do equipamento pretendido\n");
        scanf("%d", &inputID);
        getchar();

        equip = procurarEquipManutencaoUser(inicioEquip, inputID, username);

        if (equip == NULL)
        {
            return;
        }

        strcpy(historico.equipTipo, equip->info.type);
        strcpy(historico.brand, equip->info.brand);
        strcpy(historico.model, equip->info.model);
        historico.id = equip->info.id;

        int res;
        do
        {
            printf("\nIntroduza a data de aquisicao no formato DD/MM/YYYY\n");
            char inputStr[11];
            fgets(inputStr, sizeof(inputStr), stdin);
            inputStr[strcspn(inputStr, "\n")] = '\0';
            res = sscanf(inputStr, "%d/%d/%d", &historico.data.day, &historico.data.month, &historico.data.year);
            getchar();
            if (res != 3)
            {
                printf("Erro relativamente ao formato introduzido\n");
                continue;
            }

            if (!HistoricoDateSystem(historico.data))
            {
                continue;
            }

            break;
        } while (1);

        printf("Introduza o custo da reparacao\n");
        scanf("%d", &historico.desc.reparacao.custo);
        getchar();

        strcpy(historico.desc.reparacao.tecnico, equip->info.tecnico);

        printf("Indique as pecas substituidas na reparacao\n");
        fgets(historico.desc.reparacao.pecas_substituidas, sizeof(historico.desc.reparacao.pecas_substituidas), stdin);
        historico.desc.reparacao.pecas_substituidas[strcspn(historico.desc.reparacao.pecas_substituidas, "\n")] = '\0';

        switch (input)
        {
        case 1:
            strcpy(equip->info.tecnico, "Nenhum");
            strcpy(equip->info.state, "Uso");
            break;
        case 2:
            strcpy(equip->info.tecnico, "Nenhum");
            strcpy(equip->info.state, "Desativado");
            break;
        case 0:
            break;
        default:
            printf("Introduziu um valor inválido, tente novamente\n");
            break;
        }
        writeChangesEquips(inicioEquip);
        registrarHistorico(historico, inicioHistorico);
        printf("Atribuicao efetuada com sucesso\n");
    } while (input != 0);
}

/**
 * @fn TecnicoEquipsMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts, char username[])
 * @brief Escreve o menu que permite ao tecnico de gerir os seus equipamentos.
 * Listar seus equipamentos, criar um ficheiro CSV dos seus equipamentos e procurar equipamentos por departamento.
 * @param inicioEquips
 * @param inicioDeparts
 * @param username
 */
void TecnicoEquipsMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts, char username[])
{
    int input, num;
    do
    {

        printf("\n-----------------------------------EQUIPAMENTOS-----------------------------------\n");
        printf("1 - Meus equipamentos\n");
        printf("2 - Criar CSV (meus equimapentos)\n");
        printf("3 - Procurar equipamentos por departamento\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &input);
        getchar();
        switch (input)
        {
        case 1:
            printEquipsTecnico(inicioEquips, username);
            break;
        case 2:
            escreverEquipsCSV(inicioEquips, username);
            break;
        case 3:
            if (inicioDeparts == NULL)
            {
                printf("Nenhum departamento criado\n");
                break;
            }

            printDeparts(inicioDeparts);
            printf("Introduza o numero de um departamento\n");
            scanf("%d", &num);
            getchar();
            filterEquipsDeparts(inicioEquips, num);
            break;
        case 0:
            printf("\nLogout concluido\n\n");
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
            break;
        }
    } while (input != 0);
}

/**
 * @fn handlePermissions(ELEM_U **inicioUser, char username[20], ELEM_D **inicioDepart, ELEM_E **inicioEquip, ELEM_H **inicioHistorico)
 * @brief Sistema de permissões que permite escrever o menu dos tecnicos ou do admin.
 * Admin: Ativar utilizadores, gerir departamentos, gerir equipamentos, criar relatorio, historico, avarias recorrentes, alertas, Reiniciar conta admin
 * Tecnico: Consultar equipamentos, declarar manutencao/avaria, declarar reparacao
 * @param inicioUser
 * @param username
 * @param inicioDepart
 * @param inicioEquip
 * @param inicioHistorico
 * @return int
 */
int handlePermissions(ELEM_U **inicioUser, char username[20], ELEM_D **inicioDepart, ELEM_E **inicioEquip, ELEM_H **inicioHistorico)
{

    if (strcmp(username, "admin") == 0)
    {
        int input;
        do
        {

            printf("\n-----------------------------------MENU-----------------------------------\n");
            printf("1 - Ativar utilizadores\n");
            printf("2 - Gerir departamentos\n");
            printf("3 - Gerir equipamentos\n");
            printf("4 - Criar relatorio\n");
            printf("5 - Historico\n");
            printf("6 - Avarias recorrentes\n");
            printf("7 - Alertas\n");
            printf("8 - Reiniciar conta admin\n");
            printf("0 - logout\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                char inputUsername[20];

                if (verifUsers(*inicioUser) == 0)
                {
                    printf("Nenhum utilizador na lista de ativacao\n");
                    break;
                }

                printUtilizadores(*inicioUser);
                printf("Introduza um nome de utilizador:\n");
                fgets(inputUsername, sizeof(inputUsername), stdin);
                inputUsername[strcspn(inputUsername, "\n")] = '\0';
                ativarUtilizadores(*inicioUser, inputUsername);
                break;
            case 2:
                departsMenu(inicioDepart, inicioEquip);
                break;
            case 3:
                equipsMenu(inicioEquip, *inicioDepart, inicioHistorico);
                break;
            case 4:
                RelatoriosMenu(*inicioEquip, *inicioDepart);
                break;
            case 5:
                HistoricoMenu(*inicioHistorico, *inicioEquip);
                break;
            case 6:

                if (verifAvariasRecorrentes(*inicioHistorico) == 0)
                {
                    printf("Nenhuma avaria recorrente encontrada\n");
                    break;
                }

                printAvariasRecorrencia(*inicioHistorico);
            case 7:

                if (verifAlertasEquipamentos(*inicioEquip) == 0)
                {
                    printf("Nenhuma alerta encontrada\n");
                    break;
                }

                printAlertas(*inicioEquip);
                break;
            case 8:
                resetAdmin(inicioUser);
                break;
            case 0:
                printf("\nLogout concluido\n\n");
                break;
            default:
                printf("\nValor introduzido incorreto, tente novamente\n\n");
                break;
            }
        } while (input != 0);
    }
    else
    {
        int input;
        do
        {

            printf("\n-----------------------------------MENU-----------------------------------\n");
            printf("1 - Consultar equipamentos\n");
            printf("2 - Declarar Manutencao/Avaria\n");
            printf("3 - Reparacao\n");
            printf("0 - logout\n");
            printf("Escolhe uma opcao: ");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                TecnicoEquipsMenu(*inicioEquip, *inicioDepart, username);
                break;
            case 2:
                EquipamentosDeclararUser(*inicioUser, *inicioEquip, inicioHistorico, username);
                break;
            case 3:
                EquipamentosRepararUser(*inicioUser, *inicioEquip, inicioHistorico, username);
                break;
            case 0:
                printf("\nLogout concluido\n\n");
                break;
            default:
                printf("\nValor introduzido incorreto, tente novamente\n\n");
                break;
            }
        } while (input != 0);
    }
}

/**
 * @fn loginMenu(ELEM_U **inicioUser, ELEM_D **inicioDepart, ELEM_E **inicioEquip, ELEM_H **inicioHistorico)
 * @brief Escreve o menu de log in e chama as suas respetivas funcoes.
 * @param inicioUser
 * @param inicioDepart
 * @param inicioEquip
 * @param inicioHistorico
 * @return int
 */
int loginMenu(ELEM_U **inicioUser, ELEM_D **inicioDepart, ELEM_E **inicioEquip, ELEM_H **inicioHistorico)
{
    char inputU[20];
    char inputP[20];

    printf("\n-----------------------------------WELCOME-----------------------------------\n");
    printf("Escreva EXIT se pretender terminar o programa\n");
    printf("\nUsername: ");
    fgets(inputU, sizeof(inputU), stdin);
    inputU[strcspn(inputU, "\n")] = '\0';

    // Verificação para terminar o programa.
    if (strcmp(inputU, "exit") == 0 || strcmp(inputU, "Exit") == 0 || strcmp(inputU, "EXIT") == 0)
    {
        return 0;
    }

    int resU = usernameVerif(inputU, inicioUser);

    if (resU != 0)
    {
        return -1;
    }

    printf("\nPassword: ");
    fgets(inputP, sizeof(inputP), stdin);
    inputP[strcspn(inputP, "\n")] = '\0';

    // Verificação para terminar o programa.
    if (strcmp(inputP, "exit") == 0 || strcmp(inputP, "Exit") == 0 || strcmp(inputP, "EXIT") == 0)
    {
        return 0;
    }

    int resP = passwordVerif(inputU, inputP, **inicioUser);

    if (resP != 0)
    {
        return -1;
    }

    AdminPasswordChange(*inicioUser);
    printf("Bem-vindo %s", inputU);
    handlePermissions(inicioUser, inputU, inicioDepart, inicioEquip, inicioHistorico);
    return -1;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM_E *inicioEquips = NULL;
    ELEM_U *inicioUser = NULL;
    ELEM_D *inicioDepart = NULL;
    ELEM_H *inicioHistorico = NULL;
    inicioEquips = importEquips();
    inicioUser = importUsers();
    inicioDepart = importDeparts();
    inicioHistorico = importHistorico();
    AdminSetup(&inicioUser);
    do
    {
        res = loginMenu(&inicioUser, &inicioDepart, &inicioEquips, &inicioHistorico);
    } while (res != 0);
    equipsRelease(&inicioEquips);
    usersRelease(&inicioUser);
    departsRelease(&inicioDepart);
    historicoRelease(&inicioHistorico);
}
