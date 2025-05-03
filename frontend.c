#include <stdio.h>
#include <string.h>
#include "users.h"
#include "equipements.h"

int handlePermissions(ELEM_U **inicioUser, char username[20], ELEM_E **inicioEquip)
{

    if (strcmp(username, "admin") == 0)
    {
        int input;
        do
        {

            printf("\n-----------------------------------MENU-----------------------------------\n");
            printf("1 - Ativar utilizadores\n");
            printf("2 - Gerir equipamentos\n");
            printf("3 - Consultar inventario\n");
            printf("4 - Criar relatorio\n");
            printf("5 - Historico\n");
            printf("6 - Avarias recorrentes\n");
            printf("7 - Equipamentos antigos\n");
            printf("8 - Reiniciar conta admin\n");
            printf("0 - logout\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &input);
            getchar();

            switch (input)
            {
            case 1:
                ativarUtilizadores(inicioUser);
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

int loginMenu(ELEM_U **inicioUser, ELEM_E **inicioEquip)
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
    handlePermissions(inicioUser, inputU, inicioEquip);
    return 0;
}

int main(int argc, char const *argv[])
{
    int res;
    ELEM_U *inicioUser = NULL;
    ELEM_E *inicioEquip = NULL;
    inicioUser = importUsers();
    inicioEquip = importEquips();
    AdminSetup(inicioUser);
    do
    {
        res = loginMenu(&inicioUser, &inicioEquip);
    } while (res != 0);
    usersRelease(&inicioUser);
    equipsRelease(&inicioEquip);
}
