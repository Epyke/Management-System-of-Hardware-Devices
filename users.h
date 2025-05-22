
typedef struct aluno
{
    char username[20];
    char password[20];
    int state;
} USER;

typedef struct elem_u
{
    USER info;
    struct elem_u *seguinte;
} ELEM_U;

int AdminSetup(ELEM_U **inicio);

int AdminPasswordChange(ELEM_U *inicio);

int resetAdmin(ELEM_U **inicio);

int passwordVerif(char username[20], char passwd[20], ELEM_U inicio);

int usernameVerif(char username[20], ELEM_U **inicio);

int registrar(char username[20], char password[20], ELEM_U **inicio);

int insIniLista(ELEM_U **inicio, USER info);

ELEM_U *importUsers();

int usersRelease(ELEM_U **inicio);

ELEM_U *procurarUser(ELEM_U *inicio, char username[]);

ELEM_U *procurarUserAtivo(ELEM_U *inicio, char username[]);

void printUtilizadores(ELEM_U *inicio);

int ativarUtilizadores(ELEM_U *inicio, char username[]);
