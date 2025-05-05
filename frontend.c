#include <stdio.h>
#include <string.h>
#include "users.h"
#include "departements.h"

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

void departsMenu(ELEM_D **inicioDeparts)
{
    int input;
    do
    {
        printf("\n-----------------------------------DEPARTAMENTOS-----------------------------------\n");
        printf("1 - Adicionar departamento\n");
        printf("2 - Alterar departamento\n");
        printf("3 - Remover departamento\n");
        printf("0 - Return\n");

        scanf("%d", &input);
        getchar();

        switch (input)
        {
        case 1:
            inputDeparts(inicioDeparts);
            printDeparts(*inicioDeparts);
            break;
        case 0:
            break;
        default:
            printf("\nValor introduzido incorreto, tente novamente\n\n");
        }
    } while (input != 0);
}

/*
void registarEquips()
{
    EQUIPE equip;
    int id = getEquipsNumb();
    id++;
    equip.id = id;
    printf("Introduza o tipo de equipamento\n");
    fgets(equip.type, sizeof(equip.type), stdin);
    equip.type[strcspn(equip.type, "\n")] = '\0';

    fgets(equip.brand, sizeof(equip.brand), stdin);
    equip.brand[strcspn(equip.brand, "\n")] = '\0';

    scanf("%d", &equip.num_serie);

    fgets(equip.date, sizeof(equip.date), stdin);
    equip.date[strcspn(equip.date, "\n")] = '\0';

    fgets(equip.state, sizeof(equip.state), stdin);
    equip.state[strcspn(equip.state, "\n")] = '\0';
}*/

int handlePermissions(ELEM_U **inicioUser, char username[20], ELEM_D **inicioDepart)
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
                departsMenu(inicioDepart);
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

int loginMenu(ELEM_U **inicioUser, ELEM_D **inicioDepart)
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
    handlePermissions(inicioUser, inputU, inicioDepart);
    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM_U *inicioUser = NULL;
    ELEM_D *inicioDepart = NULL;
    inicioUser = importUsers();
    inicioDepart = importDeparts();
    AdminSetup(inicioUser);
    do
    {
        res = loginMenu(&inicioUser, &inicioDepart);
    } while (res != 0);
    usersRelease(&inicioUser);
    departsRelease(&inicioDepart);
}
