#include <stdio.h>
#include <string.h>
#include "users.h"
#include "departements.h"
#include "equipements.h"

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

    printf("Introduza a data de aquisicao\n"); // Sistema de data, para mais tarde
    fgets(equip.date, sizeof(equip.date), stdin);
    equip.date[strcspn(equip.date, "\n")] = '\0';

    printf("Introduza o estado do equipamento\n");
    fgets(equip.state, sizeof(equip.state), stdin);
    equip.state[strcspn(equip.state, "\n")] = '\0';

    do
    {
        printDeparts(inicioDeparts);
        printf("Associe o equipamento ao departamento\n");
        scanf("%d", &equip.departement);
        getchar();
    } while (verifDepartNum(inicioDeparts, equip.departement) == 0);

    registrarEquips(equip, inicioEquips);
}

void altEquipMenu(ELEM_E *inicioEquips, ELEM_D *inicioDeparts)
{
    int input, target;
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
            printf("Introduza a nova data de aquisição\n");
            fgets(equip->info.date, sizeof(equip->info.date), stdin);
            equip->info.date[strcspn(equip->info.date, "\n")] = '\0';
            break;
        case 6:
            printf("Introduza o novo estado do equipamento\n");
            fgets(equip->info.state, sizeof(equip->info.state), stdin);
            equip->info.state[strcspn(equip->info.state, "\n")] = '\0';
        case 7:
            do
            {
                printDeparts(inicioDeparts);
                printf("Introduza o novo departamento\n");
                scanf("%d", &equip->info.departement);
                getchar();
            } while (verifDepartNum(inicioDeparts, equip->info.departement) == 0);
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
    writeChangesEquips(inicioEquips);
}

void equipsMenu(ELEM_E **inicioEquips, ELEM_D *inicioDeparts)
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
            printEquips(*inicioEquips);
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

            altEquipMenu(*inicioEquips, inicioDeparts);
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

void departsMenu(ELEM_D **inicioDeparts, ELEM_E *inicioEquips)
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
            if (eliminarDepart(inicioDeparts, num) == 0)
            {
                if (num != num_departs)
                {
                    refreshDepartCodes(*inicioDeparts);
                    refreshEquipCodes(inicioEquips);
                    writeChangesEquips(inicioEquips);
                }
                writeChangesDeparts(*inicioDeparts);
            }
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

int handlePermissions(ELEM_U **inicioUser, char username[20], ELEM_D **inicioDepart, ELEM_E **inicioEquip)
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
            printf("4 - Consultar inventario\n");
            printf("5 - Criar relatorio\n");
            printf("6 - Historico\n");
            printf("7 - Avarias recorrentes\n");
            printf("8 - Equipamentos antigos\n");
            printf("9 - Reiniciar conta admin\n");
            printf("0 - logout\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                ativarUtilizadores(inicioUser);
                break;
            case 2:
                departsMenu(inicioDepart, *inicioEquip);
                break;
            case 3:
                equipsMenu(inicioEquip, *inicioDepart);
                break;
            case 9:
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
            printf("2 - Listar para ficheiro\n");
            printf("3 - Consultar inventario\n");
            printf("4 - Registar uma nova avaria ou manutencao\n");
            printf("5 - Gerir equipamentos\n");
            printf("6 - Registar componentes substituidas\n");
            printf("0 - logout\n");
            printf("Escolhe uma opcao: ");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
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

int loginMenu(ELEM_U **inicioUser, ELEM_D **inicioDepart, ELEM_E **inicioEquip)
{
    char inputU[20];
    char inputP[20];

    printf("\n-----------------------------------WELCOME-----------------------------------\n");
    printf("Escreva EXIT se pretender terminar o programa\n");
    printf("\nUsername: ");
    fgets(inputU, sizeof(inputU), stdin);
    inputU[strcspn(inputU, "\n")] = '\0';

    if (strcmp(inputU, "exit") == 0 || strcmp(inputU, "Exit") == 0 || strcmp(inputU, "EXIT") == 0)
    {
        return 0;
    }

    int resU = usernameVerif(inputU, *inicioUser);

    if (resU != 0)
    {
        return -1;
    }

    printf("\nPassword: ");
    fgets(inputP, sizeof(inputP), stdin);
    inputP[strcspn(inputP, "\n")] = '\0';

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
    handlePermissions(inicioUser, inputU, inicioDepart, inicioEquip);
    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM_E *inicioEquips = NULL;
    ELEM_U *inicioUser = NULL;
    ELEM_D *inicioDepart = NULL;
    inicioEquips = importEquips();
    inicioUser = importUsers();
    inicioDepart = importDeparts();
    AdminSetup(&inicioUser);
    do
    {
        res = loginMenu(&inicioUser, &inicioDepart, &inicioEquips);
    } while (res != 0);
    equipsRelease(&inicioEquips);
    usersRelease(&inicioUser);
    departsRelease(&inicioDepart);
}
